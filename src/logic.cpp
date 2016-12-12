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
	QDate hisDate;//读取历史数据的时间点日期
	int year = 0;
	int month = 0;
	int day = 0;
	int dayCnt = startDate.daysTo(endDate);
	uint8 hourNode = 0;//每天固定读取历史数据的时间点

	if (startDate > endDate) {//判断时期区间的合法性
		emit dateError();
		return;
	}

	for (int i = 0;i < dayCnt;i++) {
		hisDate = startDate.addDays(i);
		year = (hisDate.year() - TWO_THOUSAND);//因为给宫主任安装设备的日期是2016年, 所以设备不可能存储早于2000年的数据
		month = hisDate.month();
		day = hisDate.day();
		timeNode.u8year = HEX_TO_BCD(year);
		timeNode.u8month = HEX_TO_BCD(month);
		timeNode.u8day = HEX_TO_BCD(day);
		for (int j = 0;j < 24;j++) {
			timeNode.u8hour = HEX_TO_BCD(j);
			emit readDbData1Node(&timeNode);
			SLEEP_MSEC(200);//防止操作过快, 隔一段时间发送一个信号
		}
	}
}

void logicObject::readFrameFromCom(QByteArray&)
{
	tempControl_messure_hisdata_str hisDataStr[48] = { { 0 } };
	uint16 hisDataCnt = 0;

	//分析后续包标志, 如果无后续包, 则发送信号
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