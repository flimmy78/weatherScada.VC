#include "basedef.h"
#include "db.h"


sqliteDb::sqliteDb(QObject* parent)
{
	m_sqlDb = QSqlDatabase::addDatabase("QSQLITE");
	m_sqlDb.setDatabaseName(DB_PATH);
}

sqliteDb::~sqliteDb()
{
	closeDB();
}

void sqliteDb::startThread()
{
	qDebug() << "sqliteDb::startThread: " << QThread::currentThreadId();
}

bool sqliteDb::openDB()
{
	return m_sqlDb.open();
}

void sqliteDb::closeDB()
{
	m_sqlDb.close();
}

void sqliteDb::queryOneRow(sysTimePtr pTimeNode)
{
	QString sqlStmt;
	QSqlQuery query(m_sqlDb);
	historyDataStr hisData = { 0 };

	sqlStmt.clear();
	sqlStmt.sprintf("select count(*) from %s where %s = \'20%02X-%02X-%02X %02X:%02X:%02X.000\'", \
		HIS_TABLE, F_TIMENODE, pTimeNode->u8year, pTimeNode->u8month, pTimeNode->u8day, \
		pTimeNode->u8hour, pTimeNode->u8minute, pTimeNode->u8second);
	query.exec(sqlStmt);

	if (!query.first())
	{
		emit oneRowNotExist(pTimeNode);
		return;
	}
	memcpy(&(hisData.timeNode), pTimeNode, sizeof(historyDataStr));
	hisData.tIn = query.value(FIELD_TEMPIN).toFloat();
	hisData.tOut = query.value(FIELD_TEMPOUT).toFloat();
	hisData.tAvg = query.value(FIELD_TEMPAVG).toFloat();
	hisData.flowRate = query.value(FIELD_FLOWRATE).toFloat();
	hisData.power = query.value(FIELD_POWER).toFloat();
	hisData.accumFlow = query.value(FIELD_ACCUMFLOW).toFloat();
	hisData.deltaFlow = query.value(FIELD_DELTAFLOW).toFloat();
	hisData.energy = query.value(FIELD_ENERGY).toFloat();
	hisData.deltaEnergy = query.value(FIELD_DELTAENERGY).toFloat();
	hisData.inTemp1 = query.value(FIELD_TROOM1).toFloat();
	hisData.inTemp2 = query.value(FIELD_TROOM2).toFloat();
	hisData.outTemp1 = query.value(FIELD_TAIR1).toFloat();
	hisData.outTemp2 = query.value(FIELD_TAIR2).toFloat();
	hisData.windRate = query.value(FIELD_WINDRATE).toFloat();
	hisData.weather = (weatherEnum)query.value(FIELD_WEATHER).toInt();
	hisData.roomArea = query.value(FIELD_ROOMAREA).toFloat();
	emit oneRowExist(&hisData);
}

void sqliteDb::insertOneRow(historyDataPtr pHisData)
{
	QString sqlStmt;
	QSqlQuery query(m_sqlDb);

	sqlStmt.clear();
	sqlStmt.sprintf("insert into %s(f_timenode, f_tIn, f_tOut, f_tAvg, f_flowRate, f_power, f_accumFlow, f_deltaFlow, f_energy, f_deltaEnergy, f_inTemp1, f_inTemp2, f_outTemp1, f_outTemp2, f_windRate, f_weather, f_roomArea)values(\'20%02X-%02X-%02X %02X:%02X:%02X.000\',", HIS_TABLE, pHisData->timeNode.u8year, pHisData->timeNode.u8month, \
		pHisData->timeNode.u8day, pHisData->timeNode.u8hour, \
		pHisData->timeNode.u8minute, pHisData->timeNode.u8second);
	sqlStmt.append(QString("%1,").arg(pHisData->tIn, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->tOut, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->tAvg, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->flowRate, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->power, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->accumFlow, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->deltaFlow, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->energy, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->deltaEnergy, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->inTemp1, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->inTemp2, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->outTemp1, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->outTemp2, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(pHisData->windRate, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg((int)(pHisData->weather), 0, 10));
	sqlStmt.append(QString("%1)").arg(pHisData->roomArea, 6, 'g', 6));

	if (query.exec(sqlStmt)) {
		emit insertOK();
	} else {
		emit insertFail(&(pHisData->timeNode));
	}
}