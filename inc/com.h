#ifndef COM_H
#define COM_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "basedef.h"


typedef struct {
	QString					portName;
	QSerialPort::BaudRate	baudrate;
	QSerialPort::DataBits	databits;
	QSerialPort::Parity		parity;
	QSerialPort::StopBits	stopbits;
} comInfoStr;
typedef comInfoStr* comInfoPtr;


class comObject : public QObject
{
	Q_OBJECT
public:
	comObject(QObject* parent = 0);
	~comObject();
private:
	QSerialPort* m_serialPort;

signals:
	void openComOK();
	void openComFail();
	void finished();
public slots :
	void startThread();

	void openCom(comInfoPtr);
	void closeCom();
};

#endif // COM_H
