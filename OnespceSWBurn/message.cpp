#include "message.h"

CMessage::CMessage(QString strName):CObject(strName)
{
	SetTypeName("message");
}

CMessage::CMessage()
{
	SetTypeName("");
}

CMessage::~CMessage()
{
	int size = m_vpSignalList.size();
	for (int i = 0; i < size; i++)
	{
		if (m_vpSignalList[i] != NULL)
		{
			delete m_vpSignalList[i];
			m_vpSignalList[i] = NULL;
		}
	}
}

CMessage::CMessage(CMessage& C)
{
	this->m_enMessageType = C.m_enMessageType;
	this->SetName(C.GetName());
	
	int size = C.m_vpSignalList.size();

	if (size <= 0)
	{
		this->m_vpSignalList.clear();
	}

	for (int i = 0; i < size; i++)
	{
		CSignal* pSignal = new CSignal("");
		*pSignal = *((CSignal*)C.m_vpSignalList[i]);
		m_vpSignalList.append(pSignal);
	}
	
}

CMessage& CMessage::operator=(CMessage& C)
{
	this->m_enMessageType = C.m_enMessageType;
	this->SetName(C.GetName());

	int size = C.m_vpSignalList.size();

	if (size <= 0)
	{
		this->m_vpSignalList.clear();
	}

	for (int i = 0; i < size; i++)
	{
		CSignal* pSignal = new CSignal("");
		*pSignal = *((CSignal*)C.m_vpSignalList[i]);
		m_vpSignalList.append(pSignal);
	}

	return *this;
}

void CMessage::SetMessageType(EN_MESSAGE_TYPE enMessageType)
{
	m_enMessageType = enMessageType;
}

EN_MESSAGE_TYPE CMessage::GetMessageType()
{
	return m_enMessageType;
}

int CMessage::AddSignal(CSignal signal)
{
	if (CObject::FindObject(signal.GetName(), m_vpSignalList) == -1)
	{
		CSignal* newSignal = new CSignal(signal.GetName());
		*newSignal = signal;
		m_vpSignalList.append(newSignal);
		return 0;
	}

	return -1;
}

int CMessage::DeleteSignal(QString strSignalName)
{
	int index = CObject::FindObject(strSignalName, m_vpSignalList);
	if (index == -1)
		return -1;

	CSignal* pSignal = (CSignal*)m_vpSignalList[index];
	delete pSignal;

	m_vpSignalList.takeAt(index);

	return 0;
}

int CMessage::DeleteSignal(CSignal signal)
{
	int index = CObject::FindObject(signal.GetName(), m_vpSignalList);
	if (index == -1)
		return -1;

	CSignal* pSignal = (CSignal*)m_vpSignalList[index];
	delete pSignal;

	m_vpSignalList.takeAt(index);

	return 0;
}

CSignal* CMessage::GetSignal(QString strSignalName)
{
	int index = CObject::FindObject(strSignalName, m_vpSignalList);
	if (index == -1)
		return NULL;

	return (CSignal*)m_vpSignalList[index];
}

CSignal* CMessage::GetSignal(int signalIndex)
{
	if (signalIndex >= m_vpSignalList.size())
		return NULL;

	return (CSignal*)m_vpSignalList[signalIndex];
}

int CMessage::ReplaceSignal(int signalIndex, CSignal signal)
{
	if (signalIndex >= m_vpSignalList.size())
		return -1;

	CSignal* pSignal = new CSignal(signal.GetName());
	*pSignal = signal;

	CSignal* pOld = (CSignal*)m_vpSignalList[signalIndex];
	delete pOld;

	m_vpSignalList[signalIndex] = pSignal;

	return 0;
}

int CMessage::ReplaceSignal(QString oriSignalName, CSignal signal)
{
	int index = CObject::FindObject(oriSignalName, m_vpSignalList);
	if (index == -1)
		return -1;

	CSignal* pSignal = new CSignal(signal.GetName());
	*pSignal = signal;

	CSignal* pOld = (CSignal*)m_vpSignalList[index];
	delete pOld;

	m_vpSignalList[index] = pSignal;

	return 0;
}


int CMessage::SignalListSize()
{
	return m_vpSignalList.size();
}


int CMessage::ClearSignalList()
{
	m_vpSignalList.clear();

	return 0;
}

QDomElement CMessage::GetObjectXML(QDomDocument* pDoc)
{
	QDomElement rootElement = GetTypeElementXML(pDoc);

	QDomElement messageType = pDoc->createElement("message_type");

	if (m_enMessageType == EN_SERIAL)
	{
		messageType.appendChild(pDoc->createTextNode("serial"));
	}
	else if (m_enMessageType == EN_CAN)
	{
		messageType.appendChild(pDoc->createTextNode("can"));
	}
	else if (m_enMessageType == EN_1553B)
	{
		messageType.appendChild(pDoc->createTextNode("1553b"));
	}
	else
	{
		messageType.appendChild(pDoc->createTextNode("serial"));
	}

	rootElement.appendChild(messageType);

	QDomElement _signals = pDoc->createElement("signals");
	rootElement.appendChild(_signals);

	for (int i = 0; i < m_vpSignalList.size(); i++)
	{
		QDomElement signal_element = ((CSignal*)m_vpSignalList[i])->GetObjectXML(pDoc);
		rootElement.appendChild(signal_element);
	}

	return rootElement;
}

void CMessage::SetBatchData(unsigned char* pData, unsigned int size)
{
	if (pData == NULL)
		return;

	int vectorSize = m_vpSignalList.size();
	for (int i = 0; i < vectorSize; i++)
	{
		if (m_vpSignalList[i] != NULL)
			delete (CSignal*)m_vpSignalList[i];
	}

	for (int i = 0; i < size; i++)
	{
		QString str = QString("%1").arg(i);
		CSignal* pSignal = new CSignal(str);
		pSignal->SetDefaultValue(pData[i]);
		AddSignal(*pSignal);
	}
}

void CMessage::SetBatchData(unsigned int* pData, unsigned int size)
{
	if (pData == NULL)
		return;

	int vectorSize = m_vpSignalList.size();
	for (int i = 0; i < vectorSize; i++)
	{
		if (m_vpSignalList[i] != NULL)
			delete (CSignal*)m_vpSignalList[i];
	}

	for (int i = 0; i < size; i++)
	{
		QString str = QString("%1").arg(i);
		CSignal* pSignal = new CSignal(str);
		pSignal->SetDefaultValue(pData[i]);
		AddSignal(*pSignal);
	}
}