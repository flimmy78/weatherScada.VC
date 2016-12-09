#include <QDate>
#include <QMessageBox>
#include <QSerialPortInfo>
#include "readdata.h"


readDataDlg::readDataDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::readDataForm)
{
    ui->setupUi(this);
	initWidget();
	m_comIsOpen = false;
	m_comPort = NULL;
}

readDataDlg::~readDataDlg()
{
    RELEASE_PNT(ui)
	RELEASE_PNT(m_comPort)
}

void readDataDlg::initWidget()
{
	QSettings settings(INI_PATH, QSettings::IniFormat);

	/*初始化日期*/
	QDate terday = QDate::currentDate();
	QDate yesterday = terday.addDays(-1);
	ui->dateEditStart->setDate(yesterday);
	ui->dateEditEnd->setDate(terday);

	/*初始化按钮*/
	ui->btnReadData->setEnabled(false);

	/*初始化com口*/
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
		ui->portNameComboBox->addItem(info.portName());
	}
	ui->portNameComboBox->setCurrentIndex(settings.value(STRING_COM).toInt());
	m_baudList << QSerialPort::Baud1200
				<< QSerialPort::Baud2400
				<< QSerialPort::Baud4800
				<< QSerialPort::Baud9600
				<< QSerialPort::Baud19200
				<< QSerialPort::Baud38400
				<< QSerialPort::Baud57600
				<< QSerialPort::Baud115200;

	m_databitList <<QSerialPort::Data5
					<< QSerialPort::Data6
					<< QSerialPort::Data7
					<< QSerialPort::Data8;

	m_parityList << QSerialPort::NoParity
				 << QSerialPort::OddParity
				 << QSerialPort::EvenParity;

	m_stopbitList << QSerialPort::OneStop
					 << QSerialPort::OneAndHalfStop
					 << QSerialPort::TwoStop;

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
	QString portName = ui->portNameComboBox->currentText();   //获取串口名
	QSettings settings(INI_PATH, QSettings::IniFormat);

#ifdef Q_OS_LINUX
	m_comPort = new QSerialPort("/dev/" + portName);
#elif defined (Q_OS_WIN)
	m_comPort = new QSerialPort();
	m_comPort->setPortName(portName);
#endif
	connect(m_comPort, SIGNAL(readyRead()), this, SLOT(readCom()));

	m_comPort->setBaudRate(m_baudList[settings.value(STRING_BAUDRATE).toInt()]);
	m_comPort->setDataBits(m_databitList[settings.value(STRING_DATABITS).toInt()]);
	m_comPort->setParity(m_parityList[settings.value(STRING_PARITY).toInt()]);
	m_comPort->setStopBits(m_stopbitList[settings.value(STRING_STOPBITS).toInt()]);
	m_comPort->setFlowControl(QSerialPort::NoFlowControl);

	if (m_comPort->open(QIODevice::ReadWrite)) {
		ui->btnReadData->setEnabled(true);
	}
	else {
		QMessageBox::critical(this, tr("Error"), tr("can't open ") + portName + tr("\ndevice is occupied or isn't exist!"), QMessageBox::Ok);
		return;
	}
	settings.setValue(STRING_COM, ui->portNameComboBox->currentIndex());
	m_comIsOpen = true;
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
	emit queryData(start, end);
}

void readDataDlg::getData(const QList<historyDataStr> hisList, const int8 &err)
{

}