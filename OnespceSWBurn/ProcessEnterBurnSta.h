#pragma once

#include "Process.h"

class CProcessEnterBurnSta : public CProcess
{
	Q_OBJECT

public:
	CProcessEnterBurnSta();

private:
	EN_PROCESS_CRITERION ReceiveCriterion(unsigned char* pData, unsigned int size);
	void ChangeData(unsigned char* pData);
	void FirstData(unsigned char* pData);
};