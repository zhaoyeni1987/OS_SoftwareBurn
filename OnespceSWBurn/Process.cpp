#include "Process.h"
#include "crc.h"

CProcess::CProcess(int timeOut, int repeatTime):m_TimeOut(timeOut),m_RepeatTime(repeatTime)
{
	m_bFirstSendFlag = false;

	m_bStopFlag = false;

	m_bBindSuccessFlag = false;

	m_pSerial = NULL;
	m_pSerialSendData = NULL;
	m_pSendTimer = NULL;

	m_RunResult = 0xCC;

	m_bFirstRun = false;
}

CProcess::CProcess()
{
	m_bFirstSendFlag = false;

	m_bStopFlag = false;

	m_bBindSuccessFlag = false;

	m_pSerial = NULL;
	m_pSerialSendData = NULL;
	m_pSendTimer = NULL;

	m_RunResult = 0xCC;

	m_bFirstRun = false;
}

CProcess::~CProcess()
{
	if (m_pSerial != NULL)
	{	
		m_pSerial->close();
		delete m_pSerial;
		m_pSerial = NULL;
	}

	if (m_pSendTimer != NULL)
	{
		m_pSendTimer->stop();
		delete m_pSendTimer;
		m_pSendTimer = NULL;
	}

	if (m_pSerialSendData != NULL)
	{
		delete [] m_pSerialSendData;
		m_pSerialSendData = NULL;
	}
}

unsigned int CProcess::GetMsgLength()
{


	return 0;
}

QString CProcess::GetName()
{
	return m_strName;
}

void CProcess::SetName(QString strName)
{
	m_strName = strName;
}

void CProcess::SetTimeOut(int timeOut)
{
	m_TimeOut = timeOut;
}

void CProcess::SetRepeatTime(int repeatTime)
{
	m_RepeatTime = repeatTime;
}

unsigned char CProcess::GetRunResult()
{
	return m_RunResult;
}

void CProcess::BindSendMessage(CMessage& Msg)
{
	m_SendMessage = Msg;

	if (m_pSerialSendData != NULL)
		delete [] m_pSerialSendData;

	int size = m_SendMessage.SignalListSize();
	m_pSerialSendData = new unsigned char[size];
	for (int i = 0; i < size; i++)
	{
		m_pSerialSendData[i] = (unsigned char)m_SendMessage.GetSignal(i)->GetDefaultValue();
	}
}

int CProcess::BindInterface(void* pInterfaceInfo, EN_INTERFACE_TYPE enInterfaceType)
{
	if (pInterfaceInfo == NULL)
		return -1;

	m_InterfaceType = enInterfaceType;

	if (m_InterfaceType == EN_INTERFACE_SERIAL)
	{
		if (m_pSerial == NULL)
		{
			m_pSerial = new QSerialPort(this);
			STRU_SERIAL_CONFIG_INFO serialInfo = *((STRU_SERIAL_CONFIG_INFO*)pInterfaceInfo);
			QString srtPortName(serialInfo.strComName);
			m_pSerial->setPortName(srtPortName);
			m_pSerial->setBaudRate(serialInfo.baudRate, QSerialPort::AllDirections);
			m_pSerial->setDataBits(serialInfo.dataBit);
			m_pSerial->setFlowControl(serialInfo.flowControl);
			m_pSerial->setParity(serialInfo.parity);
			m_pSerial->setStopBits(serialInfo.stopBits);
			m_pSerial->close();
			connect(m_pSerial, SIGNAL(readyRead()), this, SLOT(ReceiveData()));
			return 0;
		}	
	}	

	return -1;
}

void CProcess::SendTimer()
{
	int timeElapse = m_ControlTime.elapsed();
	if (timeElapse >= m_TimeOut)
	{
		m_pSendTimer->stop();
		this->terminate();
		return;
	}

	if (m_InterfaceType == EN_INTERFACE_SERIAL)
	{
		if (m_pSerial != NULL)
		{
			QString strInfo = GetName();
			strInfo += "("; strInfo += m_pSerial->portName(); strInfo += ") send data: ";
			int size = m_SendMessage.SignalListSize();

			for (int i = 0; i < size; i++)
			{
				strInfo += "0x";
				strInfo += QString::number(m_pSerialSendData[i], 16);
				strInfo += " ";
			}
			if (m_bFirstRun == false)
			{
				m_bFirstRun = true;
				FirstData(m_pSerialSendData);
			}
			else
				ChangeData(m_pSerialSendData);
			m_pSerial->write((char*)m_pSerialSendData, m_SendMessage.SignalListSize());
			LOG(INFO) << strInfo.toStdString();

			//ChangeData(m_pSerialSendData);
		}
	}
}

void CProcess::StopProcess()
{
	if (m_pSendTimer != NULL)
		m_pSendTimer->stop();
	if(m_pSerial != NULL)
		m_pSerial->close();

	this->terminate();

	disconnect(m_pSendTimer, SIGNAL(timeout()), this, SLOT(SendTimer()));
	disconnect(this, SIGNAL(finished()), this, SLOT(ProcessEnd()));
}

void CProcess::ReceiveData()
{
	if (m_InterfaceType == EN_INTERFACE_SERIAL)
	{
		QByteArray arr = m_pSerial->readAll();
		QString strInfo = GetName();
		int size = arr.length();
		strInfo += "("; strInfo += m_pSerial->portName(); strInfo += ") recv data: ";
		for (int i = 0; i < size; i++)
		{
			strInfo += "0x";
			strInfo += QString::number(((unsigned char*)arr.data())[i], 16);
			strInfo += " ";
		}
		LOG(INFO) << strInfo.toStdString();
		EN_PROCESS_CRITERION result = ReceiveCriterion((unsigned char*)arr.data(), arr.length());
		if (EN_PROCESS_CONTINUE != result)
		{
			if (result == EN_PROCESS_SUCCESS)
				m_RunResult = 0xAA;
			else if(result == EN_PROCESS_FAILURE)
				m_RunResult = 0xBB;

			StopProcess();
		}
	}
}

void CProcess::ProcessEnd()
{
	if (m_pSerial != NULL)
		m_pSerial->close();
	QString strInfo = QString("Process %1 ended").arg(m_strName);
	emit ProcessInfo(strInfo);
	emit ProcessFinished(m_strName);

	disconnect(m_pSendTimer, SIGNAL(timeout()), this, SLOT(SendTimer()));
	disconnect(this, SIGNAL(finished()), this, SLOT(ProcessEnd()));
}

void CProcess::run()
{
	QString strInfo = QString("Process %1 started").arg(GetName());
	emit ProcessInfo(strInfo);
	LOG(INFO) << strInfo.toStdString();
	m_RunResult = 0xDD;
	if (m_pSendTimer != NULL)
		delete m_pSendTimer;
	if (m_pSerial != NULL)
	{
		m_pSerial->open(QIODevice::ReadWrite);
	}
	m_ControlTime.start();
	m_pSendTimer = new QTimer();
	m_pSendTimer->setInterval(m_RepeatTime);
	connect(m_pSendTimer, SIGNAL(timeout()), this, SLOT(SendTimer()));
	connect(this, SIGNAL(finished()), this, SLOT(ProcessEnd()));
	m_pSendTimer->start();
	exec();
}