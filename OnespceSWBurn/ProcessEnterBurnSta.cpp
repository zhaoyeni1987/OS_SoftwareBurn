#include "ProcessEnterBurnSta.h"
#include "crc.h"

CProcessEnterBurnSta::CProcessEnterBurnSta()
{
	SetName("EnterBurnSta");
}

void CProcessEnterBurnSta::ChangeData(unsigned char* pData)
{
	pData[3]++;
	Insert16CRC_U8(pData + 2, 9, (unsigned short*)&pData[11]);
}

void CProcessEnterBurnSta::FirstData(unsigned char* pData)
{
	Insert16CRC_U8(pData + 2, 9, (unsigned short*)&pData[11]);
}

EN_PROCESS_CRITERION CProcessEnterBurnSta::ReceiveCriterion(unsigned char* pData, unsigned int size)
{
	if (pData[6] != 0x22)
		return EN_PROCESS_CONTINUE;

	if (pData[7] == 0xAA)
		return EN_PROCESS_SUCCESS;
	else
		return EN_PROCESS_FAILURE;
}