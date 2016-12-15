#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QThread>
#include <QDate>
#include <QTimer>
#include "basedef.h"
#include "protocol.h"
#include <QSettings>
#include <QDebug>
#include "func.h"


/************************************************************************/
/*     logicģ����readData, com, db, ����֮�������.
/*     readDataģ��Ѳ�ѯ�����logic, logic���������ڷ�Χ, �����ÿ����ʷ
/* ����ʱ���, �ַ���dbģ��;
/*     ���dbģ���ѯ����������, �򽫽�����͸�logic, logicֱ�ӽ����ʱ����
/* ���ݽ���readData, ��ʾ��������û��鿴.
/*     ���dbģ��û�в�ѯ����������, ���Ͳ�ѯʧ���źŸ�logic, logic����һ��
/* ��ѯ��ʷ��������֡, ���͸�com, com������һ֡���������ݺ�, ���ϵķ��͸�logic;
/* logic�ӵ�һ�������ĵ�ǰʱ������ʷ���ݺ�, �����ɱ�׼��ʷ���ݸ�ʽ, ���͸�
/* db�������ݿ�, db����ɹ���, ����һ������ɹ��źŸ�logic, logic�ٽ���׼��ʷ
/* ���ݽ���readDataģ��, ��ʾ��������û��鿴.
/************************************************************************/
class logicObject : public QObject
{
	Q_OBJECT
public:
	logicObject(QObject* parent = 0);
	~logicObject();

private:
	QList<tempControl_messure_hisdata_str> m_ctlMessureList;//���ڻ��漯������ȡ������, �¿ؼ���һ�廯��ʽ����ʷ����
	sysTimeStr m_timeNode;
	QList<sysTimeStr> m_timeNodeList;
	QTimer* m_sendSignalTimer;

	void toStdHisData(historyDataPtr);
signals:
	void finished();

	void timeNodeCalcDone(historyDataStr);
	void allDataQueryDone();
	void dateError();
	void dataReady(historyDataStr);

	void readDbData1Node(sysTimeStr);//��ȡ���ݿ��е�һ��ʱ��������, ��this.readHisData����, ��db.queryOneRow����
	void readComData(QByteArray);//�򴮿ڷ�������֡, ��com.sendBuf����
	void comEmpty(historyDataStr);

	void readFirstFrame(QByteArray);
	void readNextFrame(uint8);//��ȡ��һ֡
public slots :
	void startThread();
	void readHisData(const QDate, const QDate);
	void read1NodeData(historyDataStr);
	void readFrameFromCom(QByteArray);//���ڽ������Դ��ڵ�����, ��com.readBufReady����

	/*
	 * ���������ݿ�û�е�ǰʱ�������ʱ, �򴮿ڷ�������.
	 * �������е�һ��ʱ������ʷ����, �п��ֺܷܶ�֡
	 * ���͸���λ��, ����Ҫ�����ǵ�һ֡���Ǻ���֡.
	 */
	void send1stFrameToCom(sysTimeStr);//��һ֡����, ��db.oneRowNotExist(sysTimePtr)����
	void sendMultiFrameToCom(uint8);//����֡����, ��this.readNextFrame(uint8&)����
};

#endif // LOGIC_H
