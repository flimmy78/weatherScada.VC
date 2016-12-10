#include <QSettings>
#include <QDebug>
#include "protocol.h"
#include "func.h"
#include "logic.h"


logicObject::logicObject(QObject* parent) : QObject(parent)
{

}

logicObject::~logicObject()
{

}

void logicObject::startThread()
{
	qDebug() << "logicObject startThread: " << QThread::currentThreadId();
}

bool logicObject::readHisData(const QDate &start, const QDate &end)
{
	return true;
}

bool logicObject::readOneNodeData(sysTimePtr timeNode)
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

