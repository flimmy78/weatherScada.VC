#ifndef SYSCONFIG_H
#define SYSCONFIG_H

#include <QRegExp>
#include <QValidator>
#include <QSettings>
#include <QMap>
#include "basedef.h"
#include "ui_sysconfig.h"

class syconfigDlg : public QWidget
{
    Q_OBJECT

public:
	explicit syconfigDlg(QWidget *parent = 0);
    ~syconfigDlg();

private:
    Ui::sysconfigForm *ui;
	QRegExp m_intRX;
	QValidator *m_intValidator;
	QRegExp m_floatRX;
	QValidator *m_floatValidator;

	void loadConfig();
	void saveConfig();

private slots:
	void on_btn_save_clicked();
	void on_btn_exit_clicked();
};

#endif // SYSCONFIG_H
