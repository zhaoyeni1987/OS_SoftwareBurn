#include "Response.h"

CResponse::CResponse(QString strName)
{
	m_strName = strName;

	m_pSerial = NULL;
}

void CResponse::SetName(QString strName)
{
	m_strName = strName;
}

QString CResponse::GetName()
{
	return m_strName;
}

int CResponse::BindInterface(void* pInterfaceInfo, EN_INTERFACE_TYPE enInterfaceType)
{
	if (pInterfaceInfo == NULL)
		return -1;

	m_enInterfaceType = enInterfaceType;

	if (m_enInterfaceType == EN_INTERFACE_SERIAL)
	{
		if (m_pSerial == NULL)
		{
			m_pSerial = new QSerialPort;
			STRU_SERIAL_CONFIG_INFO serialInfo = *((STRU_SERIAL_CONFIG_INFO*)pInterfaceInfo);
			QString srtPortName(serialInfo.strComName);
			m_pSerial->setPortName(srtPortName);
			m_pSerial->setBaudRate(serialInfo.baudRate, QSerialPort::AllDirections);
			m_pSerial->setDataBits(serialInfo.dataBit);
			m_pSerial->setFlowControl(serialInfo.flowControl);
			m_pSerial->setParity(serialInfo.parity);
			m_pSerial->setStopBits(serialInfo.stopBits);
			m_pSerial->close();
			if (m_pSerial->open(QIODevice::ReadWrite))
			{
				connect(m_pSerial, SIGNAL(readyRead()), this, SLOT(ReceiveData()));
				m_bBindSuccessFlag = true;
				return 0;
			}
			else
			{
				return -1;
			}
		}
	}

	return -1;
}

void CResponse::run()
{
	exec();
}

void CResponse::ReceiveData()
{
	if (m_enInterfaceType == EN_INTERFACE_SERIAL)
	{
		QByteArray arr = m_pSerial->readAll();

		EN_PROCESS_CRITERION result; 
		result = ReceiveCriterion((unsigned char*)arr.data(), arr.length());
		if (result == EN_PROCESS_CONTINUE)
			return;
		else
		{
			if (result == EN_PROCESS_SUCCESS)
				m_RunResult = 0xAA;
			else if (result == EN_PROCESS_FAILURE)
				m_RunResult = 0xBB;

			StopProcess();
		}
	}
}

void CResponse::SendData(CMessage& Msg)
{
	if (m_bBindSuccessFlag == false)
		return;

	int size = Msg.SignalListSize();
	unsigned char* pSerialSendData = new unsigned char(size);
	for (int i = 0; i < size; i++)
	{
		pSerialSendData[i] = (unsigned char)Msg.GetSignal(i)->GetDefaultValue();
	}

	m_pSerial->write((char*)pSerialSendData, size);
}

void CResponse::SendData(unsigned char* pData, unsigned int size)
{
	if (pData == NULL)
		return;

	if (m_bBindSuccessFlag == false)
		return;

	m_pSerial->write((char*)pData, size);
}

void CResponse::StopProcess()
{
	if (m_pSerial != NULL)
		m_pSerial->close();

	this->terminate();
}

unsigned char CResponse::GetRunResult()
{
	return m_RunResult;
}