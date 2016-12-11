#ifndef READDATA_H
#define READDATA_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSettings>
#include <QMap>
#include "basedef.h"
#include "com.h"
#include "logic.h"
#include "db.h"
#include "ui_readdata.h"

#define	TABLE_DEFAULT_ROWS	10
#define	TABLE_COLS			21

#define WEATHER_FINE	tr("weather_fine")
#define WEATHER_CLOUDY	tr("weather_cloudy")
#define WEATHER_SHADE	tr("weather_shade")

typedef enum {
	COL_SEQ = 0		,//���к�
	COL_DATE		,//����
	COL_TIMENODE	,//ʱ���
	COL_TEMPIN		,//��ˮ�¶�
	COL_TEMPOUT		,//��ˮ�¶�
	COL_TEMPAVG		,//ƽ���¶�
	COL_FLOWRATE	,//����
	COL_POWER		,//����
	COL_ACCUMFLOW	,//�ۼ�����
	COL_DELTAFLOW	,//��������
	COL_ENERGY		,//�ۻ�����
	COL_DELTAENERGY	,//��������
	COL_TROOM1		,//�����¶�1
	COL_TROOM2		,//�����¶�2
	COL_TAIR1		,//�����¶�1
	COL_TAIR2		,//�����¶�2
	COL_WINDRATE	,//����
	COL_WFINE		,//��
	COL_WCLOUDY		,//����
	COL_WSHADE		,//��
	COL_ROOMAREA	//���ݽ������
} colIdx;

class readDataDlg : public QWidget
{
    Q_OBJECT

public:
    explicit readDataDlg(QWidget *parent = 0);
    ~readDataDlg();


private:
    Ui::readDataForm *ui;

	bool m_comIsOpen;
	QSettings* m_settings;

	QThread* m_comThread;
	comObject* m_comPort;

	QThread* m_logicThread;
	logicObject* m_logicObj;

	QThread* m_dbThread;
	sqliteDb* m_dbObj;

	QList<QSerialPort::BaudRate>	m_baudList;//��˳����sysconfig�е�comboxһ��, ��ͬ
	QList<QSerialPort::DataBits>	m_databitList;
	QList<QSerialPort::Parity>		m_parityList;
	QList<QSerialPort::StopBits>	m_stopbitList;
	QList<QString>					m_weatherList;
private slots:
	void initWidget();
	void initCom();
	void initLogic();
	void initDb();

	void on_btnOpenCom_clicked();
	void on_btnReadData_clicked();

public slots:
	void showEvent(QShowEvent* e);
	void closeEvent(QCloseEvent* e);
	void getData(const QList<historyDataStr>& hisList, const int8& err);

	void openComOK();
	void openComFail();
signals:
	void signalClosed();
	void queryData(const QDate &start, const QDate &end);
	void openCom(comInfoPtr);
};

#endif // READDATA_H
