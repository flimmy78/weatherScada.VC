#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QtSql>
#include "basedef.h"

#define DB_PATH		"db/hisdata.db"

class sqliteDb : public QObject
{
	Q_OBJECT

public:
	sqliteDb(QObject* parent = 0);
	~sqliteDb();

private:
	QSqlDatabase m_sqlDb;

public slots:
	bool openDB();
	void closeDB();

	bool insertHisData(historyDataPtr pHisData);
signals:
	void insertOK();
	void insertFail();
};

#endif // DB_H
