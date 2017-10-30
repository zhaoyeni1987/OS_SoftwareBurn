#pragma once

#include <QString>
#include <QThread>
#include "Process.h"
#include <QSerialPort>
#include <QList>
#include <QTimer>

class CResponse : public QThread
{
	Q_OBJECT

public:
	CResponse(QString strName);

	void SetName(QString strName);
	QString GetName();

	unsigned char GetRunResult();

	int BindInterface(void* pInterfaceInfo = NULL, EN_INTERFACE_TYPE enInterfaceType = EN_INTERFACE_SERIAL);	//°ó¶¨½Ó¿Ú

protected:
	virtual EN_PROCESS_CRITERION ReceiveCriterion(unsigned char* pData, unsigned int size) { return EN_PROCESS_CONTINUE; };
	void SendData(CMessage& Msg);
	void SendData(unsigned char* pData, unsigned int size);

private slots:
	void ReceiveData();

private:
	void run();
	void StopProcess();

private:
	QString m_strName;
	EN_INTERFACE_TYPE m_enInterfaceType;
	bool m_bBindSuccessFlag;

	QSerialPort* m_pSerial;

	int m_RunResult;//0xAA success 0xBB failure 0xCC ready 0xDD running
};