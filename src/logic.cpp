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
	connect(this, SIGNAL(readNextFrame(uint8&)), this, SLOT(sendMultiFrameToCom(uint8&)));
}

void logicObject::readHisData(const QDate &startDate, const QDate &endDate)
{
	sysTimeStr timeNode = { 0 };
	QDate hisDate;//��ȡ��ʷ���ݵ�ʱ�������
	int year = 0;
	int month = 0;
	int day = 0;
	int dayCnt = startDate.daysTo(endDate);
	uint8 hourNode = 0;//ÿ��̶���ȡ��ʷ���ݵ�ʱ���

	if (startDate > endDate) {//�ж�ʱ������ĺϷ���
		emit dateError();
		return;
	}

	for (int i = 0;i < dayCnt;i++) {
		hisDate = startDate.addDays(i);
		year = (hisDate.year() - TWO_THOUSAND);//��Ϊ�������ΰ�װ�豸��������2016��, �����豸�����ܴ洢����2000�������
		month = hisDate.month();
		day = hisDate.day();
		timeNode.u8year = HEX_TO_BCD(year);
		timeNode.u8month = HEX_TO_BCD(month);
		timeNode.u8day = HEX_TO_BCD(day);
		for (int j = 0;j < 24;j++) {
			timeNode.u8hour = HEX_TO_BCD(j);
			emit readDbData1Node(&timeNode);
			SLEEP_MSEC(200);//��ֹ��������, ��һ��ʱ�䷢��һ���ź�
		}
	}
}

void logicObject::readFrameFromCom(QByteArray&)
{
	tempControl_messure_hisdata_str hisDataStr[48] = { { 0 } };
	uint16 hisDataCnt = 0;

	//������������־, ����޺�����, �����ź�
}

void logicObject::send1stFrameToCom(sysTimePtr timeNode)
{
	uint8 buf[GATEWAY_FRAME_MAX_LEN] = { 0 };
	uint16 bufSize = 0;
	hisdata_head_str BodyHeadStr = { 0 };

	protoR_readHisData(buf, &bufSize, timeNode);
}

void logicObject::sendMultiFrameToCom(uint8&)
{
	uint8 buf[GATEWAY_FRAME_MAX_LEN] = { 0 };
	uint16 bufSize = 0;
	hisdata_head_str BodyHeadStr = { 0 };
	while (BodyHeadStr.succeed == 0x01) {
		BodyHeadStr.seq++;
		//protoR_readMultiInfo(buf, &bufSize, luint8gatewayId, &(BodyHeadStr.seq));
	}
}