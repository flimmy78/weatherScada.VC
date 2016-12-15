#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QThread>
#include <QDate>
#include "basedef.h"
#include "protocol.h"
#include <QSettings>
#include <QDebug>
#include "func.h"


/************************************************************************/
/*     logic模块是readData, com, db, 三者之间的桥梁.
/*     readData模块把查询命令交给logic, logic负责处理日期范围, 计算出每个历史
/* 数据时间点, 分发给db模块;
/*     如果db模块查询到本地数据, 则将结果发送给logic, logic直接将这个时间点的
/* 数据交给readData, 显示到界面给用户查看.
/*     如果db模块没有查询到本地数据, 则发送查询失败信号给logic, logic产生一个
/* 查询历史数据命令帧, 发送给com, com接收完一帧完整的数据后, 不断的发送给logic;
/* logic接到一个完整的当前时间点的历史数据后, 解析成标准历史数据格式, 发送给
/* db插入数据库, db插入成功后, 发送一个插入成功信号给logic, logic再将标准历史
/* 数据交给readData模块, 显示到界面给用户查看.
/************************************************************************/
class logicObject : public QObject
{
	Q_OBJECT
public:
	logicObject(QObject* parent = 0);
	~logicObject();

private:
	QList<tempControl_messure_hisdata_str> m_ctlMessureList;//用于缓存集中器读取上来的, 温控计量一体化格式的历史数据
	int m_readWriteCom;
	sysTimeStr m_timeNode;
	void toStdHisData(historyDataPtr);
signals:
	void finished();

	void dateError();
	void dataReady(historyDataStr);
	void readyInsert(historyDataStr);

	void readDbData1Node(sysTimeStr);//读取数据库中的一个时间点的数据, 由this.readHisData发送, 与db.queryOneRow相连
	void readComData(QByteArray);//向串口发送数据帧, 与com.sendBuf相连

	void readFirstFrame(QByteArray);
	void readNextFrame(uint8);//读取下一帧
public slots :
	void startThread();
	void readHisData(const QDate, const QDate);
	void readFrameFromCom(QByteArray);//用于接收来自串口的数据, 与com.readBufReady相连

	/*
	 * 当本地数据库没有当前时间点数据时, 向串口发送请求.
	 * 集中器中的一个时间点的历史数据, 有可能分很多帧
	 * 发送给上位机, 所以要区分是第一帧还是后续帧.
	 */
	void send1stFrameToCom(sysTimeStr);//第一帧命令, 与db.oneRowNotExist(sysTimePtr)相连
	void sendMultiFrameToCom(uint8);//后续帧命令, 与this.readNextFrame(uint8&)相连
};

#endif // LOGIC_H
