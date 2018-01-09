#include "mainframe.h"
#include <QFileDialog>
#include "ProcessEnterBurnSta.h"
#include "ProcessUploadBin.h"
#include "ProcessCheck.h"
#include "ProcessQuitBurnSta.h"
#include "ProcessDownloadBin.h"
#include "logging.h"

#define PROCESS_ENTER_BURN_STA	(0)
#define PROCESS_UPLOAD_BIN		(1)
#define PROCESS_CHECK			(2)
#define PROCESS_DOWNLOAD_BIN	(3)
#define PROCESS_QUIT_BURN_STA	(4)

#define SECOND					(1000)
#define MSECOND					(1)

#define COLOR_RED				(QColor(255, 0, 0))
#define COLOR_BLACK				(QColor(0, 0, 0))
#define COLOR_YELLOW			(QColor(255,128,64))
#define COLOR_GREEN				(QColor(0,198,0))
#define COLOR_GRAY				(QColor(128,128,128))

using namespace google;

mainframe::mainframe(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	GlogInit();

	LOG(INFO) << "系统启动完成";

	QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();

	for (int i = 0; i < list.size(); i++)
	{
		ui.comboBoxSerialPort->addItem(list.at(i).portName());
	}

	ui.comboBoxBaud->setCurrentIndex(8);
	ui.comboBoxDataBit->setCurrentIndex(3);//set data bit 8
	ui.comboBoxCheckBit->setCurrentIndex(1);

	ui.pushButtonBurn->setEnabled(false);
	ui.progressBar->setEnabled(false);

	m_ProcessBurnRunning = false;

	m_bHaveStarted = false;

	PrepareProcess();

	LOG(INFO) << "流程设置完成";
}

mainframe::~mainframe()
{

}

void mainframe::GlogInit()
{
	QDir dir;
	QString path = dir.currentPath();
	path += "/log";
	FLAGS_log_dir = path.toStdString();
	path += "/INFO_";
	InitGoogleLogging("Interface Message Control");
	SetLogDestination(google::GLOG_INFO, path.toLatin1().data());
	SetStderrLogging(google::GLOG_INFO);
	SetLogFilenameExtension("log_");
	FLAGS_colorlogtostderr = true;	// Set log color
	FLAGS_logbufsecs = 0;			// Set log output speed(s)
									//FLAGS_max_log_size = 1024;		// Set max log file size
	FLAGS_stop_logging_if_full_disk = true;  // If disk is full
}

void mainframe::PrepareProcess()
{
	//-------------process: enter burn sta
	CProcess* pEnterBurnSta = new CProcessEnterBurnSta;
	m_vpProcess.append(pEnterBurnSta);

	m_vpProcess[PROCESS_ENTER_BURN_STA]->SetTimeOut(1 * SECOND);
	m_vpProcess[PROCESS_ENTER_BURN_STA]->SetRepeatTime(100 * MSECOND);
	connect(m_vpProcess[PROCESS_ENTER_BURN_STA], SIGNAL(ProcessFinished(QString)), this, SLOT(ProcessEnd(QString)));
	connect(m_vpProcess[PROCESS_ENTER_BURN_STA], SIGNAL(ProcessInfo(QString)), this, SLOT(ProcessInfo(QString)));

	CMessage msg_EnterBurnSta("msg_enter_burn_sta");
	msg_EnterBurnSta.SetMessageType(EN_SERIAL);
	unsigned char enterBurnSta[13] = { 0x55,0xAA,0x05,0x00,0x02,0xF0,0x11,0x00,0x00,0x00,0x00,0x00,0x00 };
	msg_EnterBurnSta.SetBatchData(enterBurnSta, 13);
	m_vpProcess[PROCESS_ENTER_BURN_STA]->BindSendMessage(msg_EnterBurnSta);

	//------------process: update application
	CProcess* pUploadBin = new CProcessUploadBin;
	m_vpProcess.append(pUploadBin);

	m_vpProcess[PROCESS_UPLOAD_BIN]->SetTimeOut(2000 * SECOND);
	m_vpProcess[PROCESS_UPLOAD_BIN]->SetRepeatTime(20 * MSECOND);
	connect(m_vpProcess[PROCESS_UPLOAD_BIN], SIGNAL(ProcessFinished(QString)), this, SLOT(ProcessEnd(QString)));
	connect(m_vpProcess[PROCESS_UPLOAD_BIN], SIGNAL(ProcessInfo(QString)), this, SLOT(ProcessInfo(QString)));
	CProcessUploadBin* pUploadBin1 = (CProcessUploadBin*)m_vpProcess[PROCESS_UPLOAD_BIN];
	connect(pUploadBin1, SIGNAL(Completion(float)), this, SLOT(Completion(float)));

	CMessage msg_UploadBin("msg_upload_bin");
	msg_UploadBin.SetMessageType(EN_SERIAL);
	unsigned char uploadBin[263];
	memset(uploadBin, 0, sizeof(unsigned char) * 263);
	msg_UploadBin.SetBatchData(uploadBin, 263);
	m_vpProcess[PROCESS_UPLOAD_BIN]->BindSendMessage(msg_UploadBin);

	//------------process: check
	CProcess* pCheck = new CProcessCheck;
	m_vpProcess.append(pCheck);

	m_vpProcess[PROCESS_CHECK]->SetTimeOut(200 * SECOND);
	m_vpProcess[PROCESS_CHECK]->SetRepeatTime(1000 * MSECOND);
	connect(m_vpProcess[PROCESS_CHECK], SIGNAL(ProcessFinished(QString)), this, SLOT(ProcessEnd(QString)));
	connect(m_vpProcess[PROCESS_CHECK], SIGNAL(ProcessInfo(QString)), this, SLOT(ProcessInfo(QString)));

	CMessage msg_Check("msg_check_bin");
	msg_Check.SetMessageType(EN_SERIAL);
	unsigned char check[8] = { 0x55,0xAA,0x00,0x00,0x02,0xF6,0x00,0x00 };
	msg_Check.SetBatchData(check, 8);
	m_vpProcess[PROCESS_CHECK]->BindSendMessage(msg_Check);

#if 1
	//------------process: download bin
	CProcess* pDownloadBin = new CProcessDownloadBin;
	m_vpProcess.append(pDownloadBin);

	m_vpProcess[PROCESS_DOWNLOAD_BIN]->SetTimeOut(2000 * SECOND);
	m_vpProcess[PROCESS_DOWNLOAD_BIN]->SetRepeatTime(30 * MSECOND);
	connect(m_vpProcess[PROCESS_DOWNLOAD_BIN], SIGNAL(ProcessFinished(QString)), this, SLOT(ProcessEnd(QString)));
	connect(m_vpProcess[PROCESS_DOWNLOAD_BIN], SIGNAL(ProcessInfo(QString)), this, SLOT(ProcessInfo(QString)));
	CProcessDownloadBin* pDownloadBin1 = (CProcessDownloadBin*)m_vpProcess[PROCESS_DOWNLOAD_BIN];
	connect(pDownloadBin1, SIGNAL(Completion(float)), this, SLOT(Completion(float)));

	CMessage msg_DownloadBin("msg_download_bin");
	msg_DownloadBin.SetMessageType(EN_SERIAL);
	unsigned char downloadBin[10] = { 0x55,0xAA,0x02,0x00,0x02,0xF4,0x00,0x00,0x00,0x00};
	msg_DownloadBin.SetBatchData(downloadBin, 10);
	m_vpProcess[PROCESS_DOWNLOAD_BIN]->BindSendMessage(msg_DownloadBin);

	//------------process: quit burn sta
	CProcess* pQuitBurnSta = new CProcessQuitBurnSta;
	m_vpProcess.append(pQuitBurnSta);

	m_vpProcess[PROCESS_QUIT_BURN_STA]->SetTimeOut(1 * SECOND);
	m_vpProcess[PROCESS_QUIT_BURN_STA]->SetRepeatTime(100 * MSECOND);
	connect(m_vpProcess[PROCESS_QUIT_BURN_STA], SIGNAL(ProcessFinished(QString)), this, SLOT(ProcessEnd(QString)));
	connect(m_vpProcess[PROCESS_QUIT_BURN_STA], SIGNAL(ProcessInfo(QString)), this, SLOT(ProcessInfo(QString)));

	CMessage msg_QuitBurnSta("msg_quit_burn_sta");
	msg_QuitBurnSta.SetMessageType(EN_SERIAL);
	unsigned char quitBurnSta[13] = { 0x55,0xAA,0x05,0x00,0x02,0xF0,0x22,0x00,0x00,0x00,0x00,0x00,0x00 };
	msg_QuitBurnSta.SetBatchData(quitBurnSta, 13);
	m_vpProcess[PROCESS_QUIT_BURN_STA]->BindSendMessage(msg_QuitBurnSta);
#endif
}

void mainframe::PrintInfo(QColor& col, QString strInfo)
{
	QTextCharFormat fmt;
	fmt.setForeground(col);
	QTextCursor cursor = ui.plainTextEditInfo->textCursor();
	cursor.mergeCharFormat(fmt);
	ui.plainTextEditInfo->mergeCurrentCharFormat(fmt);
	ui.plainTextEditInfo->appendPlainText(strInfo);
}

void mainframe::ProcessEnd(QString strProcessName)
{
	int index = 0;
	bool lastProcessComplete = false;
	for (index = 0; index < m_vpProcess.size(); index++)
	{
		if (strProcessName == m_vpProcess[index]->GetName())
		{
			ProcessEnd(index);
			if (index == (m_vpProcess.size() - 1))
				lastProcessComplete = true;
			else
			{
				m_vpProcess[index + 1]->start();
			}
			break;
		}
	}

	if (lastProcessComplete)
	{
		ui.groupBoxSerialSetting->setEnabled(true);
		//ui.pushButtonBurn->setText("Burn");
		ui.pushButtonBurn->setIcon(QIcon(":/mainframe/image/start_burn.png"));
		ui.pushButtonBurn->setToolTip("Start Burn");
		m_bHaveStarted = false;
	}
}

void mainframe::ProcessInfo(QString strInfo)
{
	PrintInfo(COLOR_BLACK, strInfo);
}

void mainframe::ProcessEnd(unsigned int processIndex)
{
	QString strProcessName = m_vpProcess[processIndex]->GetName();

	unsigned result = m_vpProcess[processIndex]->GetRunResult();
	if (result == 0xBB)
		PrintInfo(COLOR_RED, QString("**ERROR**: Process \"%1\" found some error!").arg(strProcessName));
	else if (result == 0xAA)
		PrintInfo(COLOR_GREEN, QString(">>INFO>>: Process \"%1\" complete!").arg(strProcessName));
	else if (result == 0xDD)
		PrintInfo(COLOR_YELLOW, QString("++WARN++: Process \"%1\" overtime or interrupt!").arg(strProcessName));
}

void mainframe::Completion(float value)
{
	ui.progressBar->setValue((int)(value*100));
}

void mainframe::GetSerialPortInfo()
{
	memset(&m_stSerialConfigInfo, 0, sizeof(STRU_SERIAL_CONFIG_INFO));

	QString strPortName = ui.comboBoxSerialPort->currentText();
	strcpy(m_stSerialConfigInfo.strComName, strPortName.toLatin1().data());

	QString strBaudrate = ui.comboBoxBaud->currentText();
	//m_stSerialConfigInfo.baudRate = (QSerialPort::BaudRate)strBaudrate.toInt();
	m_stSerialConfigInfo.baudRate = strBaudrate.toInt();

	m_stSerialConfigInfo.dataBit = (QSerialPort::DataBits)ui.comboBoxDataBit->currentText().toInt();

	m_stSerialConfigInfo.flowControl = QSerialPort::NoFlowControl;

	QString strParity = ui.comboBoxCheckBit->currentText();
	if (strParity == "NONE")
		m_stSerialConfigInfo.parity = QSerialPort::NoParity;
	else if (strParity == "ODD")
		m_stSerialConfigInfo.parity = QSerialPort::OddParity;
	else if (strParity == "EVEN")
		m_stSerialConfigInfo.parity = QSerialPort::EvenParity;
	else if (strParity == "MARK")
		m_stSerialConfigInfo.parity = QSerialPort::MarkParity;
	else if (strParity == "SPACE")
		m_stSerialConfigInfo.parity = QSerialPort::SpaceParity;
	QString strStopBits = ui.comboBoxStopBit->currentText();
	if (strStopBits == "1")
		m_stSerialConfigInfo.stopBits = QSerialPort::OneStop;
	else if (strStopBits == "1.5")
		m_stSerialConfigInfo.stopBits = QSerialPort::OneAndHalfStop;
	else if (strStopBits == "2")
		m_stSerialConfigInfo.stopBits = QSerialPort::TwoStop;
}

void mainframe::OpenBin()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Config"), "", tr("Bin Files (*.bin)"));
	if (!fileName.isNull())
	{
		ui.lineEditBinPath->setText(fileName);
		m_strBinPath = fileName;
		ui.pushButtonBurn->setEnabled(true);
		ui.progressBar->setEnabled(true);
		ui.pushButtonBurn->setToolTip("Start Burn");
	}
}

void mainframe::Burn()
{
	if (m_bHaveStarted == false)		//if the process not started
	{
		GetSerialPortInfo();
		ui.groupBoxSerialSetting->setEnabled(false);
		if (m_vpProcess[PROCESS_ENTER_BURN_STA] != NULL)
		{
#if 0
			m_vpProcess[PROCESS_ENTER_BURN_STA]->BindInterface((void*)&m_stSerialConfigInfo);
			m_vpProcess[PROCESS_UPLOAD_BIN]->BindInterface((void*)&m_stSerialConfigInfo);
			m_vpProcess[PROCESS_CHECK]->BindInterface((void*)&m_stSerialConfigInfo);
			m_vpProcess[PROCESS_QUIT_BURN_STA]->BindInterface((void*)&m_stSerialConfigInfo);
#endif
			for(int i = 0; i<m_vpProcess.size(); i++)
				m_vpProcess[i]->BindInterface((void*)&m_stSerialConfigInfo);
			
			m_vpProcess[PROCESS_ENTER_BURN_STA]->start();
			
			CProcessUploadBin* pUploadBin = (CProcessUploadBin*)m_vpProcess[PROCESS_UPLOAD_BIN];
			pUploadBin->ReadBin(m_strBinPath);

			CProcessCheck* pCheck = (CProcessCheck*)m_vpProcess[PROCESS_CHECK];
			pCheck->SetBinInfo(pUploadBin->GetBinLength(), pUploadBin->GetCrc32());

			CProcessDownloadBin* pDownloadBin = (CProcessDownloadBin*)m_vpProcess[PROCESS_DOWNLOAD_BIN];
			pDownloadBin->SetBinInfo(pUploadBin->GetBinLength());
		}

		//ui.pushButtonBurn->setText("Stop");
		ui.pushButtonBurn->setIcon(QIcon(":/mainframe/image/stop_burn.png"));
		ui.pushButtonBurn->setToolTip("Stop Burn");
		m_bHaveStarted = true;
	}
	else				//if the process have started
	{
		ui.groupBoxSerialSetting->setEnabled(true);
		for (int i = 0; i < m_vpProcess.size(); i++)
		{
			if (m_vpProcess[i]->isRunning())
				m_vpProcess[i]->StopProcess();
		}

		//ui.pushButtonBurn->setText("Burn");
		ui.pushButtonBurn->setIcon(QIcon(":/mainframe/image/start_burn.png"));
		ui.pushButtonBurn->setToolTip("Start Burn");
		m_bHaveStarted = false;
	}
}

