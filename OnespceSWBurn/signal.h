#pragma once

#include "object.h"

typedef enum
{
	EN_SIGNAL_8_BIT = 0,
	EN_SIGNAL_16_BIT,
	EN_SIGNAL_32_BIT
}EN_SIGNAL_LENGTH;

class CSignal : public CObject
{
public:
	CSignal(QString strName);
	~CSignal();

	void SetSignalLength(EN_SIGNAL_LENGTH enSignalLength);
	EN_SIGNAL_LENGTH GetSignalLength();

	QDomElement GetObjectXML(QDomDocument* pDoc);

#if 0
	void SetOffset(double offset);
	double GetOffset();

	void SetFactor(double factor);
	double GetFactor();
#endif

	void SetDefaultValue(unsigned int value);
	unsigned int GetDefaultValue();
	
private:
	EN_SIGNAL_LENGTH m_enSignalLength;
	unsigned int m_defaultValue;
	

};