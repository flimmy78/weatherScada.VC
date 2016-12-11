#ifndef DB_H
#define DB_H

#include <QObject>
#include <QSqlDatabase>
#include <QtSql>
#include "basedef.h"

#define DB_PATH		"db/hisdata.db"
#define HIS_TABLE	"t_history_data"
#define F_TIMENODE	"f_timenode"



typedef enum {
	FIELD_SEQ = 0,	//���к�
	FIELD_DATE,		//����ʱ��
	FIELD_TIMENODE,	//ʱ���
	FIELD_TEMPIN,	//��ˮ�¶�
	FIELD_TEMPOUT,	//��ˮ�¶�
	FIELD_TEMPAVG,	//ƽ���¶�
	FIELD_FLOWRATE,	//����
	FIELD_POWER,	//����
	FIELD_ACCUMFLOW,//�ۼ�����
	FIELD_DELTAFLOW,//��������
	FIELD_ENERGY,	//�ۻ�����
	FIELD_DELTAENERGY,//��������
	FIELD_TROOM1,	//�����¶�1
	FIELD_TROOM2,	//�����¶�2
	FIELD_TAIR1,	//�����¶�1
	FIELD_TAIR2,	//�����¶�2
	FIELD_WINDRATE,	//����
	FIELD_WEATHER,	//��
	FIELD_ROOMAREA	//���ݽ������
} fieldIdx;

class sqliteDb : public QObject
{
	Q_OBJECT

public:
	sqliteDb(QObject* parent = 0);
	~sqliteDb();

private:
	QSqlDatabase m_sqlDb;

public slots:
	void startThread();
	bool openDB();
	void closeDB();

	void queryOneRow(sysTimePtr);
	void insertOneRow(historyDataPtr);
signals:
	void finished();
	void oneRowExist(historyDataPtr);
	void oneRowNotExist(sysTimePtr);
	void insertOK();
	void insertFail(sysTimePtr);
};

#endif // DB_H
