#ifndef COM_H
#define COM_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "basedef.h"

#define TIME_OUT	1500

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
	QByteArray m_readBuf;//Êý¾Ý»º³åÇø
	QTimer m_timer;

signals:
	void openComOK();
	void openComFail();
	void finished();
	void readBufReady(QByteArray);
public slots :
	void startThread();

	void openCom(comInfoPtr);
	void closeCom();

	void sendBuf(QByteArray);
	void readBuf();
	void sendData();
};

#endif // COM_H
