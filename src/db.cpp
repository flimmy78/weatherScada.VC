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

}

bool sqliteDb::openDB()
{
	return m_sqlDb.open();
}

void sqliteDb::closeDB()
{
	m_sqlDb.close();
}

bool sqliteDb::insertHisData(historyDataPtr pHisData)
{
	return true;
}