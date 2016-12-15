#include <QDate>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QMetaType>
#include <QThread>
#include "readdata.h"

readDataDlg::readDataDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::readDataForm)
{
    ui->setupUi(this);
	m_settings = new QSettings(INI_PATH, QSettings::IniFormat);
	m_seq = 0;
	qRegisterMetaType<comInfoPtr>("comInfoPtr");
	qRegisterMetaType<historyDataStr>("historyDataStr");
	qRegisterMetaType<sysTimeStr>("sysTimeStr");
	initCom();
	initLogic();
	initDb();
	initIntraction();
	initWidget();
}

readDataDlg::~readDataDlg()
{
    RELEASE_PNT(ui)
	RELEASE_PNT(m_settings)
}

void readDataDlg::showEvent(QShowEvent* e)
{
	e = e;
}

void readDataDlg::closeEvent(QCloseEvent* e)
{
	e = e;
	emit signalClosed();
}

void readDataDlg::initCom()
{
	m_comThread = NULL;
	m_comThread = new QThread;
	m_comIsOpen = false;
	m_comPort = NULL;
	m_comPort = new comObject();
	m_comPort->moveToThread(m_comThread);
	
	connect(this, SIGNAL(openCom(comInfoPtr)), m_comPort, SLOT(openCom(comInfoPtr)));
	connect(m_comPort, SIGNAL(openComOK()), this, SLOT(openComOK()));
	connect(m_comPort, SIGNAL(openComFail()), this, SLOT(openComFail()));
	connect(this, SIGNAL(signalClosed()), m_comPort, SIGNAL(finished()));
	CONNECT_THREAD(m_comPort, m_comThread);
	/*初始化combox*/
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
		ui->portNameComboBox->addItem(info.portName());
	}
	ui->portNameComboBox->setCurrentIndex(m_settings->value(STRING_COM).toInt());
	m_baudList << QSerialPort::Baud1200
		<< QSerialPort::Baud2400
		<< QSerialPort::Baud4800
		<< QSerialPort::Baud9600
		<< QSerialPort::Baud19200
		<< QSerialPort::Baud38400
		<< QSerialPort::Baud57600
		<< QSerialPort::Baud115200;

	m_databitList << QSerialPort::Data5
		<< QSerialPort::Data6
		<< QSerialPort::Data7
		<< QSerialPort::Data8;

	m_parityList << QSerialPort::NoParity
		<< QSerialPort::OddParity
		<< QSerialPort::EvenParity;

	m_stopbitList << QSerialPort::OneStop
		<< QSerialPort::OneAndHalfStop
		<< QSerialPort::TwoStop;
}

void readDataDlg::initLogic()
{
	m_logicThread = NULL;
	m_logicThread = new QThread;
	m_logicObj = NULL;
	m_logicObj = new logicObject();
	m_logicObj->moveToThread(m_logicThread);

	connect(this, SIGNAL(queryData(const QDate, const QDate)), \
		m_logicObj, SLOT(readHisData(const QDate, const QDate)));
	connect(m_logicObj, SIGNAL(dataReady(historyDataStr)), \
		this, SLOT(getData(historyDataStr)));
	connect(m_logicObj, SIGNAL(comEmpty(historyDataStr)), \
		this, SLOT(getData(historyDataStr)));
	connect(this, SIGNAL(signalClosed()), m_logicObj, SIGNAL(finished()));
	CONNECT_THREAD(m_logicObj, m_logicThread);
}

void readDataDlg::initDb()
{
	m_dbThread = NULL;
	m_dbObj = NULL;
	m_dbThread = new QThread;
	m_dbObj = new sqliteDb();

	connect(this, SIGNAL(signalClosed()), m_dbObj, SIGNAL(finished()));
	
	CONNECT_THREAD(m_dbObj, m_dbThread);
}

void readDataDlg::initIntraction()
{
	if (NULL == m_dbObj || NULL == m_logicObj|| NULL == m_comPort) {
		return;
	}

	connect(m_logicObj, SIGNAL(readDbData1Node(sysTimeStr)), m_dbObj, SLOT(queryOneRow(sysTimeStr)));
	connect(m_logicObj, SIGNAL(dataReady(historyDataStr)), m_dbObj, SLOT(insertOneRow(historyDataStr)));
	connect(m_dbObj, SIGNAL(oneRowNotExist(sysTimeStr)), m_logicObj, SLOT(send1stFrameToCom(sysTimeStr)));
	connect(m_dbObj, SIGNAL(oneRowExist(historyDataStr)), m_logicObj, SIGNAL(dataReady(historyDataStr)));
	connect(m_logicObj, SIGNAL(readComData(QByteArray)), m_comPort, SLOT(sendBuf(QByteArray)));
	connect(m_comPort, SIGNAL(readBufReady(QByteArray)), m_logicObj, SLOT(readFrameFromCom(QByteArray)));
}

void readDataDlg::initWidget()
{
	/*初始化日期*/
	QDate terday = QDate::currentDate();
	QDate yesterday = terday.addDays(-1);
	ui->dateEditStart->setDate(yesterday);
	ui->dateEditEnd->setDate(terday);

	/*初始化按钮*/
	ui->btnReadData->setEnabled(false);

	/*初始化表格*/
	ui->tableWidget->setRowCount(TABLE_DEFAULT_ROWS);
	ui->tableWidget->setColumnCount(TABLE_COLS);

	QColor color(232, 232, 232);
	for (int i = 0; i < TABLE_DEFAULT_ROWS; i++) {
		for (int j = 0; j < TABLE_COLS; j++) {
			ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString("")));
		}	
	}

	ui->tableWidget->setSpan(0, COL_SEQ, 2, 1);
	ui->tableWidget->item(0, COL_SEQ)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(0, COL_SEQ)->setBackgroundColor(color);
	ui->tableWidget->item(0, COL_SEQ)->setText(QString(tr("seq")));
	ui->tableWidget->item(0, COL_SEQ)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(0, COL_SEQ)->setTextColor(Qt::black);

	ui->tableWidget->setSpan(0, COL_DATE, 2, 1);
	ui->tableWidget->item(0, COL_DATE)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(0, COL_DATE)->setBackgroundColor(color);
	ui->tableWidget->item(0, COL_DATE)->setText(QString(tr("date")));
	ui->tableWidget->item(0, COL_DATE)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(0, COL_DATE)->setTextColor(Qt::black);

	ui->tableWidget->setSpan(0, COL_TIMENODE, 2, 1);
	ui->tableWidget->item(0, COL_TIMENODE)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(0, COL_TIMENODE)->setBackgroundColor(color);
	ui->tableWidget->item(0, COL_TIMENODE)->setText(QString(tr("timenode")));
	ui->tableWidget->item(0, COL_TIMENODE)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(0, COL_TIMENODE)->setTextColor(Qt::black);

	ui->tableWidget->setSpan(0, COL_TEMPIN, 1, 9);
	ui->tableWidget->item(0, COL_TEMPIN)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(0, COL_TEMPIN)->setBackgroundColor(color);
	ui->tableWidget->item(0, COL_TEMPIN)->setText(QString(tr("Heat Meter Param")));
	ui->tableWidget->item(0, COL_TEMPIN)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(0, COL_TEMPIN)->setTextColor(Qt::black);

	ui->tableWidget->item(1, COL_TEMPIN)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_TEMPIN)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_TEMPIN)->setText(QString(tr("temp in")));
	ui->tableWidget->item(1, COL_TEMPIN)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_TEMPIN)->setTextColor(Qt::red);

	ui->tableWidget->item(1, COL_TEMPOUT)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_TEMPOUT)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_TEMPOUT)->setText(QString(tr("temp out")));
	ui->tableWidget->item(1, COL_TEMPOUT)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_TEMPOUT)->setTextColor(Qt::green);

	ui->tableWidget->item(1, COL_TEMPAVG)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_TEMPAVG)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_TEMPAVG)->setText(QString(tr("temp avg")));
	ui->tableWidget->item(1, COL_TEMPAVG)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_TEMPAVG)->setTextColor(Qt::black);

	ui->tableWidget->item(1, COL_FLOWRATE)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_FLOWRATE)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_FLOWRATE)->setText(QString(tr("m3/h")));
	ui->tableWidget->item(1, COL_FLOWRATE)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_FLOWRATE)->setTextColor(Qt::black);

	ui->tableWidget->item(1, COL_POWER)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_POWER)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_POWER)->setText(QString(tr("kW")));
	ui->tableWidget->item(1, COL_POWER)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_POWER)->setTextColor(Qt::black);

	ui->tableWidget->item(1, COL_ACCUMFLOW)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_ACCUMFLOW)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_ACCUMFLOW)->setText(QString(tr("m3")));
	ui->tableWidget->item(1, COL_ACCUMFLOW)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_ACCUMFLOW)->setTextColor(Qt::black);

	ui->tableWidget->item(1, COL_DELTAFLOW)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_DELTAFLOW)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_DELTAFLOW)->setText(QString(tr("delta m3")));
	ui->tableWidget->item(1, COL_DELTAFLOW)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_DELTAFLOW)->setTextColor(Qt::black);

	ui->tableWidget->item(1, COL_ENERGY)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_ENERGY)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_ENERGY)->setText(QString(tr("kWh")));
	ui->tableWidget->item(1, COL_ENERGY)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_ENERGY)->setTextColor(Qt::black);

	ui->tableWidget->item(1, COL_DELTAENERGY)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_DELTAENERGY)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_DELTAENERGY)->setText(QString(tr("delta kWh")));
	ui->tableWidget->item(1, COL_DELTAENERGY)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_DELTAENERGY)->setTextColor(Qt::black);

	ui->tableWidget->setSpan(0, COL_TROOM1, 1, 2);
	ui->tableWidget->item(0, COL_TROOM1)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(0, COL_TROOM1)->setBackgroundColor(color);
	ui->tableWidget->item(0, COL_TROOM1)->setText(QString(tr("roomtemp")));
	ui->tableWidget->item(0, COL_TROOM1)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(0, COL_TROOM1)->setTextColor(Qt::red);

	ui->tableWidget->item(1, COL_TROOM1)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_TROOM1)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_TROOM1)->setText(QString(tr("room1")));
	ui->tableWidget->item(1, COL_TROOM1)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_TROOM1)->setTextColor(Qt::red);

	ui->tableWidget->item(1, COL_TROOM2)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_TROOM2)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_TROOM2)->setText(QString(tr("room2")));
	ui->tableWidget->item(1, COL_TROOM2)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_TROOM2)->setTextColor(Qt::red);

	ui->tableWidget->setSpan(0, COL_TAIR1, 1, 2);
	ui->tableWidget->item(0, COL_TAIR1)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(0, COL_TAIR1)->setBackgroundColor(color);
	ui->tableWidget->item(0, COL_TAIR1)->setText(QString(tr("airtemp")));
	ui->tableWidget->item(0, COL_TAIR1)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(0, COL_TAIR1)->setTextColor(Qt::green);

	ui->tableWidget->item(1, COL_TAIR1)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_TAIR1)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_TAIR1)->setText(QString(tr("airtemp1")));
	ui->tableWidget->item(1, COL_TAIR1)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_TAIR1)->setTextColor(Qt::green);

	ui->tableWidget->item(1, COL_TAIR2)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_TAIR2)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_TAIR2)->setText(QString(tr("airtemp2")));
	ui->tableWidget->item(1, COL_TAIR2)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_TAIR2)->setTextColor(Qt::green);


	ui->tableWidget->item(0, COL_WINDRATE)->setBackgroundColor(color);
	ui->tableWidget->item(0, COL_WINDRATE)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(0, COL_WINDRATE)->setText(QString(tr("windrate")));
	ui->tableWidget->item(0, COL_WINDRATE)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(0, COL_WINDRATE)->setTextColor(Qt::black);
	ui->tableWidget->item(1, COL_WINDRATE)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_WINDRATE)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_WINDRATE)->setText(QString(tr("m/s")));
	ui->tableWidget->item(1, COL_WINDRATE)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_WINDRATE)->setTextColor(Qt::black);

	ui->tableWidget->setSpan(0, COL_WFINE, 1, 3);
	ui->tableWidget->item(0, COL_WFINE)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(0, COL_WFINE)->setBackgroundColor(color);
	ui->tableWidget->item(0, COL_WFINE)->setText(QString(tr("weather")));
	ui->tableWidget->item(0, COL_WFINE)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(0, COL_WFINE)->setTextColor(Qt::black);

	ui->tableWidget->item(1, COL_WFINE)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_WFINE)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_WFINE)->setText(QString(tr("fine")));
	ui->tableWidget->item(1, COL_WFINE)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_WFINE)->setTextColor(Qt::black);

	ui->tableWidget->item(1, COL_WCLOUDY)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_WCLOUDY)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_WCLOUDY)->setText(QString(tr("cloudy")));
	ui->tableWidget->item(1, COL_WCLOUDY)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_WCLOUDY)->setTextColor(Qt::black);

	ui->tableWidget->item(1, COL_WSHADE)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_WSHADE)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_WSHADE)->setText(QString(tr("shade")));
	ui->tableWidget->item(1, COL_WSHADE)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_WSHADE)->setTextColor(Qt::black);

	ui->tableWidget->item(0, COL_ROOMAREA)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(0, COL_ROOMAREA)->setBackgroundColor(color);
	ui->tableWidget->item(0, COL_ROOMAREA)->setText(QString(tr("room area")));
	ui->tableWidget->item(0, COL_ROOMAREA)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(0, COL_ROOMAREA)->setTextColor(Qt::black);

	ui->tableWidget->item(1, COL_ROOMAREA)->setFlags(Qt::NoItemFlags);
	ui->tableWidget->item(1, COL_ROOMAREA)->setBackgroundColor(color);
	ui->tableWidget->item(1, COL_ROOMAREA)->setText(QString(tr("m2")));
	ui->tableWidget->item(1, COL_ROOMAREA)->setTextAlignment(Qt::AlignCenter);
	ui->tableWidget->item(1, COL_ROOMAREA)->setTextColor(Qt::black);
}

void readDataDlg::on_btnOpenCom_clicked()
{
	comInfoStr portInfo;
	
	if (m_settings) {
		portInfo.portName = ui->portNameComboBox->currentText();
		portInfo.baudrate = m_baudList[m_settings->value(STRING_BAUDRATE).toInt()];
		portInfo.databits = m_databitList[m_settings->value(STRING_DATABITS).toInt()];
		portInfo.parity = m_parityList[m_settings->value(STRING_PARITY).toInt()];
		portInfo.stopbits = m_stopbitList[m_settings->value(STRING_STOPBITS).toInt()];
		emit openCom(&portInfo);
	}
}

void readDataDlg::openComOK()
{
	ui->btnReadData->setEnabled(true);
	m_settings->setValue(STRING_COM, ui->portNameComboBox->currentIndex());
	m_comIsOpen = true;
}

void readDataDlg::openComFail()
{
	QMessageBox::critical(this, tr("Error"), tr("can't open this com.\ndevice is occupied or isn't exist!"), QMessageBox::Ok);
}

void readDataDlg::on_btnReadData_clicked()
{
	QDate start = ui->dateEditStart->date();
	QDate end = ui->dateEditEnd->date();

	if (!m_comIsOpen) {
		QMessageBox::warning(this, QObject::tr("warning"),
			QObject::tr("open com first!"));
		return;
	}
	m_seq = 0;
	emit queryData(start, end);
}

void readDataDlg::getData(historyDataStr hisData)
{
	int rowNO = TABLE_DEFAULT_ROWS + m_seq;
	QString text;
	float value;

	ui->tableWidget->setRowCount(rowNO + 1);
	for (int i = 0; i < TABLE_COLS; i++) {
		ui->tableWidget->setItem(rowNO, i, new QTableWidgetItem(QString("")));
	}
	ui->tableWidget->item(rowNO, COL_SEQ)->setText(QString::number(m_seq));
	text.sprintf("20%02x-%02x-%02x", hisData.timeNode.u8year, \
		hisData.timeNode.u8month, hisData.timeNode.u8day);
	ui->tableWidget->item(rowNO, COL_DATE)->setText(text);
	text.sprintf("%02x:%02x:%02x", hisData.timeNode.u8hour, \
		hisData.timeNode.u8minute, hisData.timeNode.u8second);
	ui->tableWidget->item(rowNO, COL_TIMENODE)->setText(text);
	ui->tableWidget->item(rowNO, COL_TEMPIN)->setText(QString::number(hisData.tIn));
	ui->tableWidget->item(rowNO, COL_TEMPOUT)->setText(QString::number(hisData.tOut));
	ui->tableWidget->item(rowNO, COL_TEMPAVG)->setText(QString::number(hisData.tAvg));
	ui->tableWidget->item(rowNO, COL_FLOWRATE)->setText(QString::number(hisData.flowRate));
	ui->tableWidget->item(rowNO, COL_POWER)->setText(QString::number(hisData.power));
	ui->tableWidget->item(rowNO, COL_ACCUMFLOW)->setText(QString::number(hisData.accumFlow));
	ui->tableWidget->item(rowNO, COL_ENERGY)->setText(QString::number(hisData.energy));
	if (m_seq) {
		value = (hisData.accumFlow - ui->tableWidget->item(rowNO - 1, COL_ACCUMFLOW)->text().toFloat());
		ui->tableWidget->item(rowNO, COL_DELTAFLOW)->setText(QString::number(value));
		value = (hisData.energy - ui->tableWidget->item(rowNO - 1, COL_ENERGY)->text().toFloat());
		ui->tableWidget->item(rowNO, COL_DELTAENERGY)->setText(QString::number(value));
	}
	ui->tableWidget->item(rowNO, COL_TROOM1)->setText(QString::number(hisData.inTemp1));
	ui->tableWidget->item(rowNO, COL_TROOM2)->setText(QString::number(hisData.inTemp2));
	ui->tableWidget->item(rowNO, COL_TAIR1)->setText(QString::number(hisData.outTemp1>150.0?(hisData.outTemp1):(150- hisData.outTemp1)));
	ui->tableWidget->item(rowNO, COL_TAIR2)->setText(QString::number(hisData.outTemp2>150.0 ? (hisData.outTemp2) : (150 - hisData.outTemp2)));
	ui->tableWidget->item(rowNO, COL_WINDRATE)->setText(QString::number(hisData.windRate, 'g', 4));
	ui->tableWidget->item(rowNO, COL_ROOMAREA)->setText(QString::number(hisData.roomArea));
	switch (hisData.weather) {
	case weather_fine:
		ui->tableWidget->item(rowNO, COL_WFINE)->setText("1");
		break;
	case weather_cloudy:
		ui->tableWidget->item(rowNO, COL_WCLOUDY)->setText("1");
		break;
	case weather_shade:
		ui->tableWidget->item(rowNO, COL_WSHADE)->setText("1");
		break;
	default:
		break;
	}
	m_seq++;
}