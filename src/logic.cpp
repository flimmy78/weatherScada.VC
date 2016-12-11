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

void logicObject::readHisData(const QDate &start, const QDate &end)
{
	sysTimeStr timeNode;
	int year = start.year();
	int day = 0;

	/*���ж�ʱ������ĺϷ���*/
	if (start.year() > end.year()) {//���ж����
		emit dateError();
		return;
	}
	if (start.month() > end.month()) {//�����ݺϷ�, �ж��·�
		emit dateError();
		return;
	}
	if (start.day() > end.day()) {//����ж�����
		emit dateError();
		return;
	}
	year = start.year();
}

void logicObject::readOneNodeData(sysTimePtr timeNode)
{
	uint8 buf[GATEWAY_FRAME_MAX_LEN] = { 0 };
	uint16 bufSize = 0;
	hisdata_head_str BodyHeadStr = { 0 };
	tempControl_messure_hisdata_str hisDataStr[48] = { { 0 } };
	uint16 hisDataCnt = 0;

	protoR_readHisData(buf, &bufSize, timeNode);

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
}

