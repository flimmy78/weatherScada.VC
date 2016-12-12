#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QThread>
#include <QDate>
#include "basedef.h"

#define TWO_THOUSAND	2000

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

signals:
	void finished();

	void dateError();
	void dataReady(const QList<historyDataStr>&, const int8&);

	void readDbData1Node(sysTimePtr);//��ȡ���ݿ��е�һ��ʱ��������, ��this.readHisData����, ��db.queryOneRow����
	void readComData(QByteArray);//�򴮿ڷ�������֡, ��this.send1stFrameToCom����, ��com.sendBuf����

	void readNextFrame(uint8&);//��ȡ��һ֡
public slots :
	void startThread();
	void readHisData(const QDate &, const QDate &);
	void readFrameFromCom(QByteArray&);//���ڽ������Դ��ڵ�����, ��com.readBufReady����

	/*
	 * ���������ݿ�û�е�ǰʱ�������ʱ, �򴮿ڷ�������.
	 * �������е�һ��ʱ������ʷ����, �п��ֺܷܶ�֡
	 * ���͸���λ��, ����Ҫ�����ǵ�һ֡���Ǻ���֡.
	 */
	void send1stFrameToCom(sysTimePtr);//��һ֡����, ��db.oneRowNotExist(sysTimePtr)����
	void sendMultiFrameToCom(uint8&);//����֡����, ��this.readNextFrame(uint8&)����
};

#endif // LOGIC_H
