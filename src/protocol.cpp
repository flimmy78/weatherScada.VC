#ifdef WIN32
#include <memory.h>
#else
#include <string.h>
#endif

#include <QSettings>
#include "protocol.h"
#include "func.h"

/*
**	创建集中器发送帧.
**	@buf:	发送缓冲区
**	@bufSize:	发送缓冲区长度
**	@pProto:	发送帧额外信息
*/
static uint8 createFrame(uint8 *buf, uint16 *bufSize, gateway_protocol_ptr pProto)
{
    uint8 *pTemp = buf;

    if (NULL == buf || NULL == bufSize || NULL == pProto)
        return ERR_CRITICAL;

    memcpy(pTemp, &(pProto->head_str.prefix), sizeof(protocol_head_str));//head
    pTemp += sizeof(protocol_head_str);

    memcpy(pTemp, pProto->pMsgBody, pProto->head_str.bodyLen);//body
    pTemp += pProto->head_str.bodyLen;
    *pTemp++ = pProto->bodyChk;//body check
    memset(pTemp, GATEWAY_SUFIX, GATEWAY_SUFIX_CNT);//suffix
    *bufSize = sizeof(protocol_head_str) + pProto->head_str.bodyLen + GATEWAY_EC_LEN + GATEWAY_SUFIX_CNT;
	return NO_ERR;
}

uint8 proto_assembleFrame(uint8* buf, uint16* bufSize, \
	uint8 MsgIndex, uint8 MsgType, uint16 bodyLen, uint8* pMsgBody)
{
	gateway_protocol_str protoStr = { 0 };

	memset(protoStr.head_str.prefix, GATEWAY_PREFIX, GATEWAY_PREFIX_CNT);//前导符
	memset(&(protoStr.head_str.start), GATEWAY_START, GATEWAY_START_CNT);//开始符
	memset(&(protoStr.head_str.protoVer), GATEWAY_PROTOCOL_VER, 1);//协议版本号

	getSvrId(protoStr.head_str.SourceAddr);
	getGatewayId(protoStr.head_str.DestAddr);
	protoStr.head_str.MsgID = MsgIndex;
	protoStr.head_str.bodyLen = bodyLen;
	protoStr.head_str.MsgType = MsgType;
	readSysTime(&(protoStr.head_str.sysTime));
	protoStr.head_str.HeadCheck = countCheck(&(protoStr.head_str.protoVer), \
		(sizeof(protocol_head_str) - GATEWAY_PREFIX_CNT - GATEWAY_START_CNT));
	protoStr.pMsgBody = pMsgBody;
	protoStr.bodyChk = countCheck(protoStr.pMsgBody, bodyLen);
	createFrame(buf, bufSize, &protoStr);
	return NO_ERR;
}

uint8 protoA_retFrameLen(uint8* buf, uint16 bufSize)
{
	uint8	lu8data = 0;
	uint16	lu16Length = 0;
	protocol_head_str protoHeadStr = { 0 };

	//检查消息头部长度
	if (bufSize < sizeof(protocol_head_str)) {
		return ERR_CRITICAL;
	}

	memcpy((uint8*)&(protoHeadStr), buf, sizeof(protocol_head_str));

	//检查整个buf的长度
	lu16Length = sizeof(protocol_head_str) + protoHeadStr.bodyLen + GATEWAY_EC_LEN + GATEWAY_SUFIX_CNT;
	if (bufSize != lu16Length) {
		return ERR_CRITICAL;
	}

	//检查前导符, 开始符和协议版本
	if (protoHeadStr.prefix[0] != GATEWAY_PREFIX || \
		protoHeadStr.prefix[1] != GATEWAY_PREFIX || \
		protoHeadStr.start != GATEWAY_START || \
		protoHeadStr.protoVer != GATEWAY_PROTOCOL_VER) {
		return ERR_CRITICAL;
	}

	//检查结束符
	if (buf[bufSize - 1] != GATEWAY_SUFIX || \
		buf[bufSize - 2] != GATEWAY_SUFIX) {
		return ERR_CRITICAL;
	}

	//检查头部校验
	lu8data = countCheck(&(protoHeadStr.protoVer), \
		(&(protoHeadStr.HeadCheck) - &(protoHeadStr.protoVer)));
	if (lu8data != protoHeadStr.HeadCheck) {
		return ERR_CRITICAL;
	}

	//检查消息体校验
	lu8data = countCheck(buf + sizeof(protocol_head_str), protoHeadStr.bodyLen);
	if (buf[bufSize - 3] != lu8data) {
		return ERR_CRITICAL;
	}

	return NO_ERR;
}

uint8 protoR_readHisData(uint8* buf, uint16* bufSize, sysTimePtr timeNode)
{
	sysTimeStr sysTime;
	readSysTime(&sysTime);
	return proto_assembleFrame(buf, bufSize, 0x00, \
		GAT_MT_SVR_HISDATA, sizeof(sysTimeStr), \
		(timeNode == NULL ? (uint8*)&sysTime.u8second : (uint8*)&timeNode->u8second));
}

uint8 protoR_readMultiInfo(uint8* buf, uint16* bufSize, uint8* seq)
{
	return proto_assembleFrame(buf, bufSize, 0x00, \
		GAT_MT_SVR_1OF_MFRM, 1, seq);
}

//解帧
uint8 protoA_hisData(uint8* buf, const uint16 bufSize, uint16* hisDataCnt, hisdata_head_ptr pBodyHead, tempControl_messure_hisdata_ptr pHisData)
{
	protocol_head_str protoFrameStr = { 0 };
	uint8* pMsgBody = NULL;
	uint8	idx = 0;
	uint16 dataCnt = 0;
	uint16	hisDataLen = 0;//历史数据长度计数(不包括历史信息头部: 后续标记, 序列号, 存储时间)
	const uint16	protoHeadLen = sizeof(protocol_head_str);
	const uint16	hisHeadLen = sizeof(hisdata_head_str);
	const uint16	cj188Len = sizeof(CJ188_Format);
	const uint16	fixMeterLen = sizeof(hisdata_meter_fix_str);
	const uint16	fixValveLen = sizeof(hisdata_valve_fix_str);

	//检查消息合法性
	if (protoA_retFrameLen(buf, bufSize) == ERR_CRITICAL)
		return ERR_CRITICAL;
	memcpy((uint8*)&protoFrameStr, buf, protoHeadLen);//复制消息头
	if (protoFrameStr.bodyLen < fixMeterLen) {
		pBodyHead->succeed = buf[protoHeadLen];
		return ERR_CRITICAL;
	}
	pMsgBody = buf + protoHeadLen;//指向消息体
	memcpy((uint8*)pBodyHead, pMsgBody, hisHeadLen);

	pMsgBody += hisHeadLen;//指向消息体
	hisDataLen = (bufSize - protoHeadLen - hisHeadLen - GATEWAY_SUFIX_CNT - GATEWAY_EC_LEN);
	for (idx = 0, dataCnt = 0; dataCnt < hisDataLen; idx++, pHisData++) {
		memcpy(&(pHisData->fixMeter), pMsgBody, fixMeterLen);
		if (pHisData->fixMeter.meterDataLen == 0) {
			memset(&(pHisData->MeterData), ERR_CRITICAL, cj188Len);
		}
		else {
			memcpy(&(pHisData->MeterData), pMsgBody + fixMeterLen, cj188Len);
		}
		memcpy(&(pHisData->fixValve), pMsgBody + fixMeterLen + pHisData->fixMeter.meterDataLen, fixValveLen);
		pMsgBody += (fixMeterLen + fixValveLen + pHisData->fixMeter.meterDataLen);
		dataCnt += fixMeterLen + fixValveLen + pHisData->fixMeter.meterDataLen;
	}
	*hisDataCnt = idx;
	return NO_ERR;
}
