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

uint8 protoR_readHisData(uint8* buf, uint16* bufSize, sysTimePtr timeNode)
{
	sysTimeStr sysTime;
	readSysTime(&sysTime);
	return proto_assembleFrame(buf, bufSize, 0x00, \
		GAT_MT_SVR_HISDATA, sizeof(sysTimeStr), \
		(timeNode == NULL ? (uint8*)&sysTime.u8second : (uint8*)&timeNode->u8second));
}

uint8 readHisData(sysTimePtr timeNode)
{
	uint8 buf[GATEWAY_FRAME_MAX_LEN] = { 0 };
	uint16 bufSize = 0;
	hisdata_head_str BodyHeadStr = { 0 };
	tempControl_messure_hisdata_str hisDataStr[48] = { { 0 } };
	uint16 hisDataCnt = 0;

	protoR_readHisData(buf, &bufSize, timeNode);
	//if (logic_sendAndRead(buf, &bufSize, UART_WAIT_SHORT) == ERR_OVERTIME)
	//	return ERR_OVERTIME;
	//if (protoA_hisData(buf, bufSize, &hisDataCnt, &BodyHeadStr, &hisDataStr[0]) == NO_ERR) {
	//	if (BodyHeadStr.succeed == GAT_EXCEP_FAIL) {
	//		GUI_MessageBox("\n当前时间点无历史数据\n", "失败", GUI_MESSAGEBOX_CF_MODAL);
	//		return ERR_CRITICAL;
	//	}
	//	return ERR_CRITICAL;
	//}

	while (BodyHeadStr.succeed == 0x01) {
		BodyHeadStr.seq++;
		//protoR_readMultiInfo(buf, &bufSize, luint8gatewayId, &(BodyHeadStr.seq));
		//if (logic_sendAndRead(buf, &bufSize, UART_WAIT_SHORT) == ERR_CRITICAL)
		//	goto resultErr;
		//if (protoA_hisData(buf, bufSize, &hisDataCnt, &BodyHeadStr, &hisDataStr[0]) == ERR_CRITICAL)
		//	goto resultErr;
		//if (db_storeTempHisData(&hisDataStr[0], hisDataCnt, sucCnt, failCnt) == ERR_CRITICAL)
		//	goto resultErr;
	}

	return NO_ERR;
resultErr:
	return ERR_CRITICAL;
}
