#include <QMessageBox>
#include "sysconfig.h"

syconfigDlg::syconfigDlg(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::sysconfigForm)
{
	ui->setupUi(this);
	loadConfig();
	m_rx.setPattern("\\d+");
	m_validator = new QRegExpValidator(m_rx);

	ui->lineEdit_gatewayId->setValidator(m_validator);
	ui->lineEdit_svrId->setValidator(m_validator);

	ui->lineEdit_roomTempNo->setValidator(m_validator);
	ui->lineEdit_airTempNo->setValidator(m_validator);
	ui->lineEdit_meterNo->setValidator(m_validator);
	ui->lineEdit_windMeterNo->setValidator(m_validator);
}

syconfigDlg::~syconfigDlg()
{
	RELEASE_PNT(ui)
}

void syconfigDlg::on_btn_save_clicked()
{
	saveConfig();
	QMessageBox::about(this, QObject::tr("success"),
		QObject::tr("save success!"));
}

void syconfigDlg::on_btn_exit_clicked()
{
	this->close();
}


void syconfigDlg::loadConfig()
{
	QSettings dbconfig("ini/sysconfig.ini", QSettings::IniFormat);

	ui->lineEdit_gatewayId->setText(dbconfig.value("gatewayId").toString());
	ui->lineEdit_svrId->setText(dbconfig.value("svrId").toString());

	ui->lineEdit_roomTempNo->setText(dbconfig.value("roomTempNo").toString());
	ui->lineEdit_airTempNo->setText(dbconfig.value("airTempNo").toString());
	ui->lineEdit_meterNo->setText(dbconfig.value("heatMeterNo").toString());
	ui->lineEdit_windMeterNo->setText(dbconfig.value("windMeterNo").toString());
}

void syconfigDlg::saveConfig()
{
	QSettings dbconfig("ini/sysconfig.ini", QSettings::IniFormat);

	dbconfig.setValue("gatewayId", ui->lineEdit_gatewayId->text());
	dbconfig.setValue("svrId", ui->lineEdit_svrId->text());

	dbconfig.setValue("roomTempNo", ui->lineEdit_roomTempNo->text());
	dbconfig.setValue("airTempNo", ui->lineEdit_airTempNo->text());
	dbconfig.setValue("heatMeterNo", ui->lineEdit_meterNo->text());
	dbconfig.setValue("windMeterNo", ui->lineEdit_windMeterNo->text());
}