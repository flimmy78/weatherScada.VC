#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QThread>
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

public slots :
	void startThread();

	bool readOneNodeData(sysTimePtr timeNode);
	bool readHisData(const QDate &start, const QDate &end);
};

#endif // LOGIC_H
