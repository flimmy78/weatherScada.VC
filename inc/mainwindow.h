#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "basedef.h"
#include "sysconfig.h"
#include "readdata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

	syconfigDlg* m_syconfigDlgPtr;
	readDataDlg* m_readDataDlgPtr;
private slots:
	void on_actionConfig_triggered();
	void on_actionReadData_triggered();
	void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
