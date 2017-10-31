#pragma once

#include "Process.h"

class CProcessQuitBurnSta : public CProcess
{
	Q_OBJECT

public:
	CProcessQuitBurnSta();

private:
	EN_PROCESS_CRITERION ReceiveCriterion(unsigned char* pData, unsigned int size);
	void ChangeData(unsigned char* pData);
	void FirstData(unsigned char* pData);
};