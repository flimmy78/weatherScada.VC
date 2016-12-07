#ifndef READDATA_H
#define READDATA_H

#include <QWidget>
#include <QSerialPort>
#include "basedef.h"
#include "ui_readdata.h"

#define	TABLE_DEFAULT_ROWS	10
#define	TABLE_COLS			21

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
	QSerialPort* m_comPort;

	void initWidget();
private slots:
	void readCom();
	void sendCom();
	void on_btnOpenCom_clicked();
	void on_btnReadData_clicked();
};

#endif // READDATA_H
