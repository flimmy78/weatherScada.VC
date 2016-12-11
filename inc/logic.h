#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QThread>
#include <QDate>
#include "basedef.h"

class logicObject : public QObject
{
	Q_OBJECT
public:
	logicObject(QObject* parent = 0);
	~logicObject();

private:

signals:
	void finished();

	void dateError();
	void dataReady(const QList<historyDataStr>&, const int8&);
	void readDbData1Node(sysTimePtr);
public slots :
	void startThread();

	void readOneNodeData(sysTimePtr);
	void readHisData(const QDate &, const QDate &);
};

#endif // LOGIC_H
