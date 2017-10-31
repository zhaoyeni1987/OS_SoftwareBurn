#include "ProcessQuitBurnSta.h"
#include "crc.h"

CProcessQuitBurnSta::CProcessQuitBurnSta()
{
	SetName("QuitBurnSta");
}

EN_PROCESS_CRITERION CProcessQuitBurnSta::ReceiveCriterion(unsigned char* pData, unsigned int size)
{
	if (pData[6] != 0x22)
		return EN_PROCESS_CONTINUE;

	if (pData[7] == 0xAA)
		return EN_PROCESS_SUCCESS;
	else
		return EN_PROCESS_FAILURE;
}
	
void CProcessQuitBurnSta::ChangeData(unsigned char* pData)
{
	pData[3]++;
	Insert16CRC_U8(pData + 2, 9, (unsigned short*)&pData[11]);
}
	
void CProcessQuitBurnSta::FirstData(unsigned char* pData)
{
	Insert16CRC_U8(pData + 2, 9, (unsigned short*)&pData[11]);
}