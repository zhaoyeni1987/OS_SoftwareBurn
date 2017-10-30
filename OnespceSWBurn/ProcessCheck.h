#pragma once

#include "Process.h"

class CProcessCheck : public CProcess
{
	Q_OBJECT

public:
	CProcessCheck();

	void SetBinInfo(unsigned int length, unsigned int crc32);
private:
	EN_PROCESS_CRITERION ReceiveCriterion(unsigned char* pData, unsigned int size);
	void ChangeData(unsigned char* pData);
	void FirstData(unsigned char* pData);

	unsigned int m_binLength;
	unsigned int m_crc32;
};