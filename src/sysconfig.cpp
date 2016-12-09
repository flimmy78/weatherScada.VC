#include <QMessageBox>
#include "sysconfig.h"

syconfigDlg::syconfigDlg(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::sysconfigForm)
{
	ui->setupUi(this);
	loadConfig();
	m_intRX.setPattern("\\d+");
	m_intValidator = new QRegExpValidator(m_intRX);
	ui->lineEdit_gatewayId->setValidator(m_intValidator);
	ui->lineEdit_svrId->setValidator(m_intValidator);

	ui->lineEdit_roomTempNo->setValidator(m_intValidator);
	ui->lineEdit_airTempNo->setValidator(m_intValidator);
	ui->lineEdit_meterNo->setValidator(m_intValidator);
	ui->lineEdit_windMeterNo->setValidator(m_intValidator);

	m_floatRX.setPattern("\\d+(\\.\\d+)?");
	m_floatValidator = new QRegExpValidator(m_floatRX);
	ui->lineEdit_roomArea->setValidator(m_floatValidator);
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
	QSettings settings(INI_PATH, QSettings::IniFormat);

	ui->lineEdit_gatewayId->setText(settings.value(STRING_GATEWAYID).toString());
	ui->lineEdit_svrId->setText(settings.value(STRING_SVRID).toString());

	ui->lineEdit_roomTempNo->setText(settings.value(STRING_ROOMTEMP_NO).toString());
	ui->lineEdit_airTempNo->setText(settings.value(STRING_AIRTEMP_NO).toString());
	ui->lineEdit_meterNo->setText(settings.value(STRING_HEATMETER_NO).toString());
	ui->lineEdit_windMeterNo->setText(settings.value(STRING_WINDRATE_NO).toString());

	ui->lineEdit_roomArea->setText(settings.value(STRING_ROOMAREA).toString());

	ui->baudRateComboBox->setCurrentIndex(settings.value(STRING_BAUDRATE).toInt());
	ui->dataBitsComboBox->setCurrentIndex(settings.value(STRING_DATABITS).toInt());
	ui->parityComboBox->setCurrentIndex(settings.value(STRING_PARITY).toInt());
	ui->stopBitsComboBox->setCurrentIndex(settings.value(STRING_STOPBITS).toInt());
}

void syconfigDlg::saveConfig()
{
	QSettings settings(INI_PATH, QSettings::IniFormat);

	settings.setValue(STRING_GATEWAYID, ui->lineEdit_gatewayId->text());
	settings.setValue(STRING_SVRID, ui->lineEdit_svrId->text());

	settings.setValue(STRING_ROOMTEMP_NO, ui->lineEdit_roomTempNo->text());
	settings.setValue(STRING_AIRTEMP_NO, ui->lineEdit_airTempNo->text());
	settings.setValue(STRING_HEATMETER_NO, ui->lineEdit_meterNo->text());
	settings.setValue(STRING_WINDRATE_NO, ui->lineEdit_windMeterNo->text());

	settings.setValue(STRING_ROOMAREA, ui->lineEdit_roomArea->text());

	settings.setValue(STRING_BAUDRATE, ui->baudRateComboBox->currentIndex());
	settings.setValue(STRING_DATABITS, ui->dataBitsComboBox->currentIndex());
	settings.setValue(STRING_PARITY, ui->parityComboBox->currentIndex());
	settings.setValue(STRING_STOPBITS, ui->stopBitsComboBox->currentIndex());
}