#include "signal.h"

CSignal::CSignal(QString strName):CObject(strName)
{
	m_enSignalLength = EN_SIGNAL_8_BIT;

	SetTypeName("signal");
}

CSignal::~CSignal()
{
	
}

void CSignal::SetSignalLength(EN_SIGNAL_LENGTH enSignalLength)
{
	m_enSignalLength = enSignalLength;
}

EN_SIGNAL_LENGTH CSignal::GetSignalLength()
{
	return m_enSignalLength;
}

void CSignal::SetDefaultValue(unsigned int value)
{
	m_defaultValue = value;
}

unsigned int CSignal::GetDefaultValue()
{
	return m_defaultValue;
}

QDomElement CSignal::GetObjectXML(QDomDocument* pDoc)
{
	QDomElement rootElement = GetTypeElementXML(pDoc);
	
	QDomElement length = pDoc->createElement("length");

	if (m_enSignalLength == EN_SIGNAL_8_BIT)
	{
		length.appendChild(pDoc->createTextNode("8"));
	}
	else if (m_enSignalLength == EN_SIGNAL_16_BIT)
	{
		length.appendChild(pDoc->createTextNode("16"));
	}
	else if (m_enSignalLength == EN_SIGNAL_32_BIT)
	{
		length.appendChild(pDoc->createTextNode("32"));
	}
	else
	{
		length.appendChild(pDoc->createTextNode("8"));
	}

	rootElement.appendChild(length);

	QDomElement defaultValue = pDoc->createElement("default_value");
	QString temp = QString("%1").arg(m_defaultValue);
	defaultValue.appendChild(pDoc->createTextNode(temp));

	rootElement.appendChild(defaultValue);

	return rootElement;
}