#pragma once

#include <QThread>
#include <QTimer>
#include <QTime>
#include <QSerialPort>
#include "message.h"
#include "glog/logging.h"

typedef struct
{
	char strComName[50];
	//QSerialPort::BaudRate baudRate;
	int baudRate;
	QSerialPort::DataBits dataBit;
	QSerialPort::Parity parity;
	QSerialPort::FlowControl flowControl;
	QSerialPort::StopBits stopBits;
}STRU_SERIAL_CONFIG_INFO;

typedef enum
{
	EN_INTERFACE_SERIAL = 0,
	EN_INTERFACE_CAN,
	EN_INTERFACE_1553B
}EN_INTERFACE_TYPE;

typedef enum
{
	EN_PROCESS_CONTINUE = 0,
	EN_PROCESS_SUCCESS,
	EN_PROCESS_FAILURE
}EN_PROCESS_CRITERION;

class CProcess :public QThread
{
	Q_OBJECT

public:
	CProcess(int timeOut, int repeatTime);	//设置流程超时时间和重发时间
	CProcess();
	~CProcess();
	int BindInterface(void* pInterfaceInfo = NULL, EN_INTERFACE_TYPE enInterfaceType = EN_INTERFACE_SERIAL);	//绑定接口
	void BindSendMessage(CMessage& Msg);
	unsigned char GetRunResult();
	void SetTimeOut(int timeOut);
	void SetRepeatTime(int repeatTime);
	void SetName(QString strName);
	QString GetName();
	void StopProcess();		//停止流程
	unsigned int GetMsgLength();

signals:
	void ProcessFinished(QString strProcessName); 
	void ProcessInfo(QString strProcessInfo);

protected:
	void run();				//运行流程，判断超时时间是否满足，满足退出
	virtual void FirstData(unsigned char* pData) { return; }
	virtual void ChangeData(unsigned char* pData) { return; }
	virtual EN_PROCESS_CRITERION ReceiveCriterion(unsigned char* pData, unsigned int size) { return EN_PROCESS_CONTINUE; };
	

private slots:
	void SendTimer();		//重发流程
	void ReceiveData();
	void ProcessEnd();

private:
	void ReadCom();
	QSerialPort* m_pSerial;

	CMessage m_SendMessage;

	QTimer* m_pSendTimer;
	QTime m_ControlTime;
	bool m_bFirstSendFlag;
	int m_TimeOut;
	int m_RepeatTime;
	bool m_bStopFlag;
	
	unsigned char* m_pSerialSendData;

	EN_INTERFACE_TYPE m_InterfaceType;

	bool m_bBindSuccessFlag;

	int m_RunResult;//0xAA success 0xBB failure 0xCC ready 0xDD running

	QString m_strName;

	bool m_bFirstRun;
};