#pragma once

#include "object.h"
#include "signal.h"

typedef enum
{
	EN_SERIAL = 0,
	EN_CAN,
	EN_1553B
}EN_MESSAGE_TYPE;

class CMessage : public CObject
{
public:
	CMessage(QString strName);
	CMessage();
	~CMessage();

	CMessage(CMessage& C);

	void SetMessageType(EN_MESSAGE_TYPE enMessageType);
	EN_MESSAGE_TYPE GetMessageType();

	int AddSignal(CSignal signal);

	int DeleteSignal(QString strSignalName);
	int DeleteSignal(CSignal signal);
	
	CSignal* GetSignal(QString strSignalName);
	CSignal* GetSignal(int signalIndex);

	int ReplaceSignal(int signalIndex, CSignal signal);
	int ReplaceSignal(QString oriSignalName, CSignal signal);

	int SignalListSize();
	int ClearSignalList();

	QDomElement GetObjectXML(QDomDocument* pDoc);

	void SetBatchData(unsigned int* pData, unsigned int size);
	void SetBatchData(unsigned char* pData, unsigned int size);

	CMessage& operator=(CMessage& C);
private:
	EN_MESSAGE_TYPE m_enMessageType;

	QVector<CObject*> m_vpSignalList;
};
