#pragma once

#include "Process.h"

class CProcessDownloadBin : public CProcess
{
	Q_OBJECT

public:
	CProcessDownloadBin();

	void SetBinInfo(unsigned int lengthBin);

signals:
	void Completion(float value);

private:
	EN_PROCESS_CRITERION ReceiveCriterion(unsigned char* pData, unsigned int size);
	void ChangeData(unsigned char* pData);
	void FirstData(unsigned char* pData);

	bool m_bShoudNext;

	unsigned int m_lengthBin;
	unsigned int m_lengthLess;
	unsigned int m_packageNum;

	unsigned short m_curPackage;
	unsigned char m_reminder;

	unsigned char* m_pBin;
};