#include "basedef.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	m_syconfigDlgPtr = NULL;
	m_readDataDlgPtr = NULL;
}

MainWindow::~MainWindow()
{
    RELEASE_PNT(ui)
	RELEASE_PNT(m_syconfigDlgPtr)
	RELEASE_PNT(m_readDataDlgPtr)
}

void MainWindow::on_actionConfig_triggered()
{
	if (NULL != m_syconfigDlgPtr)
		delete m_syconfigDlgPtr;

	m_syconfigDlgPtr = new syconfigDlg;
	m_syconfigDlgPtr->show();
}

void MainWindow::on_actionReadData_triggered()
{
	if (NULL == m_readDataDlgPtr)
		delete m_readDataDlgPtr;
	m_readDataDlgPtr = new readDataDlg;
	m_readDataDlgPtr->show();
}

void MainWindow::on_actionExit_triggered()
{
	this->close();
}