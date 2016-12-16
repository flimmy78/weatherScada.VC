#include "logic.h"


logicObject::logicObject(QObject* parent) : QObject(parent)
{
	m_sendSignalTimer = NULL;
}

logicObject::~logicObject()
{

}

void logicObject::startThread()
{
	qDebug() << "logicObject startThread: " << QThread::currentThreadId();
	connect(this, SIGNAL(timeNodeCalcDone(historyDataStr)), this, SLOT(read1NodeData(historyDataStr)));
	connect(this, SIGNAL(dataReady(historyDataStr)), this, SLOT(read1NodeData(historyDataStr)));
	connect(this, SIGNAL(readNextFrame(uint8)), this, SLOT(sendMultiFrameToCom(uint8)));
	connect(this, SIGNAL(comEmpty(historyDataStr)), this, SLOT(read1NodeData(historyDataStr)));
	if (m_sendSignalTimer)
		delete m_sendSignalTimer;
	m_sendSignalTimer = new QTimer;
}

void logicObject::readHisData(const QDate startDate, const QDate endDate)
{
	QDate hisDate;//读取历史数据的时间点日期
	int year = 0;
	int month = 0;
	int day = 0;
	int dayCnt = startDate.daysTo(endDate);
	historyDataStr data = { 0 };

	if (startDate > endDate) {//判断时期区间的合法性
		emit dateError();
		return;
	}

	m_timeNodeList.clear();
	for (int i = 0;i <= dayCnt;i++) {
		hisDate = startDate.addDays(i);
		year = (hisDate.year() - TWO_THOUSAND_YEAR);
		month = hisDate.month();
		day = hisDate.day();
		for (int j = 0;j < 24;j++) {
			sysTimeStr timeNode = { 0 };
			timeNode.u8year = HEX_TO_BCD(year);
			timeNode.u8month = HEX_TO_BCD(month);
			timeNode.u8day = HEX_TO_BCD(day);
			timeNode.u8hour = HEX_TO_BCD(j);
			m_timeNodeList.append(timeNode);
		}
	}
	emit timeNodeCalcDone(data);
}

void logicObject::read1NodeData(historyDataStr)
{
	if (m_timeNodeList.isEmpty()) {
		emit allDataQueryDone();
		return;
	}
	m_ctlMessureList.clear();
	sysTimeStr m_timeNode = m_timeNodeList.first();
	m_timeNodeList.removeFirst();
	emit readDbData1Node(m_timeNode);
}

void logicObject::readFrameFromCom(QByteArray b)
{
	tempControl_messure_hisdata_str hisDataStr[48] = { { 0 } };//一帧顶多传输48个历史数据
	uint16 hisDataCnt = 0;
	hisdata_head_str BodyHeadStr = { 0 };
	historyDataStr stdHisData = { 0 };
	uint8* pFrame = (uint8*)b.data();
	QSettings settings(INI_PATH, QSettings::IniFormat);

	memcpy(&(stdHisData.timeNode), &m_timeNode, sizeof(sysTimeStr));
	stdHisData.roomArea = settings.value(STRING_ROOMAREA).toFloat();//建筑面积
	stdHisData.weather = weather_noData;
	if (b.isEmpty()) {
		emit comEmpty(stdHisData);
		return;
	}

	protoA_hisData(pFrame, b.count(), &hisDataCnt, \
		&BodyHeadStr, hisDataStr);
	for (int i = 0;i < hisDataCnt;i++) {
		m_ctlMessureList << hisDataStr[i];
	}
	if (BodyHeadStr.succeed == 0x01) {//如果有后续帧, 则继续读集中器历史数据
		BodyHeadStr.seq++;
		emit readNextFrame(BodyHeadStr.seq);
	} else {
		toStdHisData(&stdHisData);
		emit dataReady(stdHisData);
	}
	qDebug() << "logicObject::readFrameFromCom";
}

void logicObject::toStdHisData(historyDataPtr pHisData)
{
	QSettings settings(INI_PATH, QSettings::IniFormat);
	QString heatMeterNo = settings.value(STRING_HEATMETER_NO).toString();//热量表表号
	QString tempInNo = settings.value(STRING_ROOMTEMP_NO).toString();//室内温度热量表表号
	QString tempOutNo = settings.value(STRING_AIRTEMP_NO).toString();//室外温度热量表表号
	QString windrateNo = settings.value(STRING_WINDRATE_NO).toString();//风速仪表号
	bool foundHeatMeter = false;
	bool foundroomTempMeter = false;
	bool foundairTempMeter = false;
	bool foundwindrateMeter = false;
	tempControl_messure_hisdata_str ctlMessStr;
	uint32 value;
	QString s;

	for (int i = 0;i < m_ctlMessureList.count();i++) {
		s.clear();
		ctlMessStr = m_ctlMessureList.at(i);
		s.sprintf("%02X%02X%02X%02X%02X%02X%02X", ctlMessStr.fixMeter.meterAddr[6],
			ctlMessStr.fixMeter.meterAddr[5],
			ctlMessStr.fixMeter.meterAddr[4],
			ctlMessStr.fixMeter.meterAddr[3],
			ctlMessStr.fixMeter.meterAddr[2],
			ctlMessStr.fixMeter.meterAddr[1],
			ctlMessStr.fixMeter.meterAddr[0]);
		if (s == heatMeterNo) {
			value = bcdToInt(ctlMessStr.MeterData.WaterInTemp, 3, 1);
			pHisData->tIn = value / 100.0;
			value = bcdToInt(ctlMessStr.MeterData.WaterOutTemp, 3, 1);
			pHisData->tOut = value / 100.0;
			pHisData->tAvg = (pHisData->tIn+ pHisData->tOut) / 2.0;
			value = bcdToInt(ctlMessStr.MeterData.Flow, 4, 1);
			pHisData->flowRate = value / 100.0;
			value = bcdToInt(ctlMessStr.MeterData.HeatPower, 4, 1);
			pHisData->power = value / 100.0;
			value = bcdToInt(ctlMessStr.MeterData.AccumulateFlow, 4, 1);
			pHisData->accumFlow = value / 100.0;
			value = bcdToInt(ctlMessStr.MeterData.CurrentHeat, 4, 1);
			pHisData->energy = value / 100.0;
			foundHeatMeter = true;
		} else if (s == tempInNo) {
			value = bcdToInt(ctlMessStr.MeterData.WaterInTemp, 3, 1);
			pHisData->inTemp1 = value / 100.0;
			value = bcdToInt(ctlMessStr.MeterData.WaterOutTemp, 3, 1);
			pHisData->inTemp2 = value / 100.0;
			foundroomTempMeter = true;
		} else if (s == tempOutNo) {
			value = bcdToInt(ctlMessStr.MeterData.WaterInTemp, 3, 1);
			pHisData->outTemp1 = value / 100.0;
			value = bcdToInt(ctlMessStr.MeterData.WaterOutTemp, 3, 1);
			pHisData->outTemp2 = value / 100.0;
			foundairTempMeter = true;
		} else if (s == windrateNo) {
			value = bcdToInt(ctlMessStr.MeterData.Flow, 4, 1);
			pHisData->windRate = value / 100.0;
			foundwindrateMeter;
		}
		if (foundHeatMeter && foundroomTempMeter && foundairTempMeter && foundwindrateMeter) {
			break;
		}
	}
}

void logicObject::send1stFrameToCom(sysTimeStr timeNode)
{
	uint8 buf[GATEWAY_FRAME_MAX_LEN] = { 0 };
	uint16 bufSize = 0;
	hisdata_head_str BodyHeadStr = { 0 };
	QByteArray b;

	memcpy(&m_timeNode, &timeNode, sizeof(sysTimeStr));

	protoR_readHisData(buf, &bufSize, &timeNode);
	b = QByteArray((char*)buf, bufSize);
	emit readComData(b);
	qDebug() << "readComData emitted";
}

void logicObject::sendMultiFrameToCom(uint8 seq)
{
	uint8 buf[GATEWAY_FRAME_MAX_LEN] = { 0 };
	uint16 bufSize = 0;
	QByteArray b;

	protoR_readMultiInfo(buf, &bufSize, &seq);
	b = QByteArray((char*)buf, bufSize);
	emit readComData(b);
	qDebug() << "readComData emitted";
}