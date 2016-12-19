#include "basedef.h"
#include "db.h"


sqliteDb::sqliteDb(QObject* parent) : QObject(parent)
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
	openDB();
}

bool sqliteDb::openDB()
{
	return m_sqlDb.open();
}

void sqliteDb::closeDB()
{
	m_sqlDb.close();
}

void sqliteDb::queryOneRow(sysTimeStr timeNode)
{
	QString sqlStmt;
	QSqlQuery query(m_sqlDb);
	historyDataStr hisData = { 0 };

	sqlStmt.clear();
	sqlStmt.sprintf("select f_id,f_timestamp,f_timenode,f_tIn,f_tOut,f_tAvg,f_flowRate,f_power,f_accumFlow,f_deltaFlow,f_energy,f_deltaEnergy,f_inTemp1,f_inTemp2,f_outTemp1,f_outTemp2,f_windRate,f_weather,f_roomArea from %s where %s = \'20%02X-%02X-%02X %02X:%02X:%02X.000\'", \
		HIS_TABLE, F_TIMENODE, timeNode.u8year, timeNode.u8month, timeNode.u8day, \
		timeNode.u8hour, timeNode.u8minute, timeNode.u8second);
	query.exec(sqlStmt);

	if (!query.first())
	{
		emit oneRowNotExist(timeNode);
		qDebug() << "oneRowNotExist emitted";
		return;
	}
	memcpy(&(hisData.timeNode), &timeNode, sizeof(sysTimeStr));
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
	emit oneRowExist(hisData);
}

int sqliteDb::rowCnt(sysTimeStr timeNode)
{
	QString sqlStmt;
	QSqlQuery query(m_sqlDb);

	sqlStmt.sprintf("select count(*) from %s where f_timenode=\'20%02X-%02X-%02X %02X:%02X:%02X.000\'", \
		HIS_TABLE, timeNode.u8year, timeNode.u8month, timeNode.u8day, timeNode.u8hour, \
		timeNode.u8minute, timeNode.u8second);
	if (!query.exec(sqlStmt))
		return 0;

	if(!query.first())
		return 0;

	return query.value(0).toInt();
}

void sqliteDb::insertOneRow(historyDataStr hisData)
{
	bool result = false;
	if (rowCnt(hisData.timeNode)) {
		result = updateIntoDb(hisData);
	} else {
		result = insertIntoDb(hisData);
	}

	if (result) {
		emit insertOK();
	} else {
		emit insertFail((hisData.timeNode));
	}
}


void sqliteDb::updateOneRow(historyDataStr hisData)
{
	bool result = false;
	if (rowCnt(hisData.timeNode)) {
		result = updateIntoDb(hisData);
	} else {
		result = insertIntoDb(hisData);
	}

	if (result) {
		emit updateOK();
	} else {
		emit updateFail();
	}
}

bool sqliteDb::insertIntoDb(historyDataStr hisData)
{
	QString sqlStmt;
	QSqlQuery query(m_sqlDb);

	sqlStmt.clear();
	sqlStmt.sprintf("insert into %s(f_timenode, f_tIn, f_tOut, f_tAvg, f_flowRate, f_power, f_accumFlow, f_deltaFlow, f_energy, f_deltaEnergy, f_inTemp1, f_inTemp2, f_outTemp1, f_outTemp2, f_windRate, f_weather, f_roomArea)values(\'20%02X-%02X-%02X %02X:%02X:%02X.000\',", HIS_TABLE, hisData.timeNode.u8year, hisData.timeNode.u8month, \
		hisData.timeNode.u8day, hisData.timeNode.u8hour, \
		hisData.timeNode.u8minute, hisData.timeNode.u8second);
	sqlStmt.append(QString("%1,").arg(hisData.tIn, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.tOut, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.tAvg, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.flowRate, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.power, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.accumFlow, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.deltaFlow, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.energy, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.deltaEnergy, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.inTemp1, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.inTemp2, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.outTemp1, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.outTemp2, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg(hisData.windRate, 6, 'g', 6));
	sqlStmt.append(QString("%1,").arg((int)(hisData.weather), 0, 10));
	sqlStmt.append(QString("%1)").arg(hisData.roomArea, 6, 'g', 6));

	return query.exec(sqlStmt);
}

bool sqliteDb::updateIntoDb(historyDataStr hisData)
{
	QString sqlStmt;
	QSqlQuery query(m_sqlDb);

	sqlStmt.clear();
	sqlStmt.sprintf("update %s set f_tIn=%f,f_tOut=%f,f_tAvg=%f,f_flowRate=%f,f_power=%f,f_accumFlow=%f,f_deltaFlow=%f,f_energy=%f,f_deltaEnergy=%f,f_inTemp1=%f,f_inTemp2=%f,f_outTemp1=%f,f_outTemp2=%f,f_windRate=%f,f_weather=%d,f_roomArea=%f where f_timenode=\'20%02X-%02X-%02X %02X:%02X:%02X.000\'", HIS_TABLE, hisData.tIn, hisData.tOut, \
		hisData.tAvg, hisData.flowRate, hisData.power, hisData.accumFlow, hisData.deltaFlow, hisData.energy, \
		hisData.deltaEnergy, hisData.inTemp1, hisData.inTemp2, hisData.outTemp1, hisData.outTemp2, hisData.windRate, \
		(int)hisData.weather, hisData.roomArea, hisData.timeNode.u8year, hisData.timeNode.u8month, \
		hisData.timeNode.u8day, hisData.timeNode.u8hour, hisData.timeNode.u8minute, hisData.timeNode.u8second);

	return query.exec(sqlStmt);
}