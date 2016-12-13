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
	connect(this, SIGNAL(readNextFrame(uint8)), this, SLOT(sendMultiFrameToCom(uint8)));
}

void logicObject::readHisData(const QDate startDate, const QDate endDate)
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

	m_ctlMessureList.clear();
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
			emit readDbData1Node(timeNode);
			SLEEP_MSEC(200);//��ֹ��������, ��һ��ʱ�䷢��һ���ź�
		}
	}
}

void logicObject::readFrameFromCom(QByteArray b)
{
	tempControl_messure_hisdata_str hisDataStr[48] = { { 0 } };//һ֡���ഫ��48����ʷ����
	uint16 hisDataCnt = 0;
	hisdata_head_str BodyHeadStr = { 0 };
	historyDataStr stdHisData = { 0 };
	uint8* pFrame = (uint8*)b.data();

	protoA_hisData(pFrame, b.count(), &hisDataCnt, \
		&BodyHeadStr, hisDataStr);
	for (int i = 0;i < hisDataCnt;i++) {
		m_ctlMessureList << hisDataStr[i];
	}
	if (BodyHeadStr.succeed == 0x01) {//����к���֡, ���������������ʷ����
		BodyHeadStr.seq++;
		emit readNextFrame(BodyHeadStr.seq);
	} else {
		toStdHisData(&stdHisData);
		emit dataReady(stdHisData);
	}
}

void logicObject::toStdHisData(historyDataPtr pHisData)
{
	QSettings settings(INI_PATH, QSettings::IniFormat);
	QString heatMeterNo = settings.value(STRING_HEATMETER_NO).toString();//��������
	QString tempInNo = settings.value(STRING_ROOMTEMP_NO).toString();//�����¶���������
	QString tempOutNo = settings.value(STRING_AIRTEMP_NO).toString();//�����¶���������
	QString windrateNo = settings.value(STRING_WINDRATE_NO).toString();//�����Ǳ��
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
	pHisData->weather = weather_noData;
}

void logicObject::send1stFrameToCom(sysTimeStr timeNode)
{
	uint8 buf[GATEWAY_FRAME_MAX_LEN] = { 0 };
	uint16 bufSize = 0;
	hisdata_head_str BodyHeadStr = { 0 };
	QByteArray b;

	protoR_readHisData(buf, &bufSize, &timeNode);
	b.append((int8*)buf);
	emit readComData(b);
}

void logicObject::sendMultiFrameToCom(uint8 seq)
{
	uint8 buf[GATEWAY_FRAME_MAX_LEN] = { 0 };
	uint16 bufSize = 0;
	QByteArray b;

	protoR_readMultiInfo(buf, &bufSize, &seq);
	b.append((int8*)buf);
	emit readComData(b);
}