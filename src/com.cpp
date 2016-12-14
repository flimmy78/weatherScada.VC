#include <QDebug>
#include "com.h"

comObject::comObject(QObject* parent) : QObject(parent)
{
	m_serialPort = NULL;
	m_timer = NULL;
}

comObject::~comObject()
{
	RELEASE_PNT(m_serialPort)
	RELEASE_PNT(m_timer)
}

void comObject::openCom(comInfoPtr pComInfo)
{
	qDebug() << "comObject::openCom threadId: " << QThread::currentThreadId();
	//comInfoPtr pComInfo = &comInfo;
	if (NULL == m_serialPort) {
#ifdef Q_OS_LINUX
		m_serialPort = new QSerialPort("/dev/" + pComInfo->portName);
#elif defined (Q_OS_WIN)
		m_serialPort = new QSerialPort();
		m_serialPort->setPortName(pComInfo->portName);
#endif
	}

	m_serialPort->setBaudRate(pComInfo->baudrate);
	m_serialPort->setDataBits(pComInfo->databits);
	m_serialPort->setParity(pComInfo->parity);
	m_serialPort->setStopBits(pComInfo->stopbits);
	m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
	if (m_serialPort->open(QSerialPort::ReadWrite))
		emit openComOK();
	else
		emit openComFail();
	connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(readBuf()));
}

void comObject::startThread()
{
	qDebug() << "### comObject::startThread thread:" << QThread::currentThreadId();
	m_readBuf.clear();
	m_timer = new QTimer;
	m_timer->setInterval(TIME_OUT);
	m_timer->stop();
	connect(m_timer, SIGNAL(timeout()), this, SLOT(sendData()));
}

void comObject::closeCom()
{
	m_serialPort->close();
}

void comObject::readBuf()
{
	QByteArray buf = m_serialPort->readAll();
	
	if (!buf.isEmpty())
		m_readBuf.append(buf);
}

void comObject::sendBuf(QByteArray buf)
{
	qDebug() << "sendBuf get signal";
	m_readBuf.clear();

	m_serialPort->write(buf);

	m_timer->start(TIME_OUT);//�ȴ���������ȫ���������
}

void comObject::sendData()
{
	m_timer->stop();
	emit readBufReady(m_readBuf);
}