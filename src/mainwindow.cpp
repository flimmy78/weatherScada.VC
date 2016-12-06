#include "basedef.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	m_syconfigDlgPtr = NULL;
	
}

MainWindow::~MainWindow()
{
    RELEASE_PNT(ui)
	RELEASE_PNT(m_syconfigDlgPtr)
}

void MainWindow::on_actionConfig_triggered()
{
	if (NULL == m_syconfigDlgPtr)
		m_syconfigDlgPtr = new syconfigDlg;
	m_syconfigDlgPtr->show();
}