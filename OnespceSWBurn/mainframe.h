#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QtWidgets/QDialog>
#include "ui_mainframe.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QVector>
#include "Process.h"

class mainframe : public QDialog
{
	Q_OBJECT

public:
	mainframe(QWidget *parent = 0);
	~mainframe();

private:
	Ui::mainframeClass ui;

	void GetSerialPortInfo();
	STRU_SERIAL_CONFIG_INFO m_stSerialConfigInfo;

private slots:
	void Burn();
	void OpenBin();

	void ProcessEnd(QString strProcessName);
	void ProcessEnd(unsigned int processIndex);

	void ProcessInfo(QString strInfo);

	void Completion(float value);
private:
	void PrintInfo(QColor& col, QString strInfo);

	void PrepareProcess();
	QVector<CProcess*> m_vpProcess;

	bool m_ProcessBurnRunning;

	QString m_strBinPath;

	bool m_bHaveStarted;
};

#endif // MAINFRAME_H
