#include "ProcessCheck.h"
#include "crc.h"

CProcessCheck::CProcessCheck()
{
	SetName("CheckBin");

	m_binLength = 0;
	m_crc32 = 0;
}

void CProcessCheck::SetBinInfo(unsigned int length, unsigned int crc32)
{
	m_crc32 = crc32;
	m_binLength = length;
}

EN_PROCESS_CRITERION CProcessCheck::ReceiveCriterion(unsigned char* pData, unsigned int size)
{
	if (pData[6] == 0x11)
		return EN_PROCESS_CONTINUE;

	if (pData[7] == 0x00)
	{
		unsigned int length = pData[8] + pData[9] * 256 + pData[10] * 65536 + pData[11] * 16777216;
		unsigned int crc32 = pData[12] + pData[13] * 256 + pData[14] * 65536 + pData[15] * 16777216;
		if ((length == m_binLength)
			&&(crc32 == m_crc32))
		{
			return EN_PROCESS_SUCCESS;
		}
		else
			return EN_PROCESS_SUCCESS;
	}
	else
	{
		return EN_PROCESS_FAILURE;
	}
}

void CProcessCheck::ChangeData(unsigned char* pData)
{
	pData[3]++;
	Insert16CRC_U8(pData + 2, 4, (unsigned short*)&pData[6]);
}

void CProcessCheck::FirstData(unsigned char* pData)
{
	Insert16CRC_U8(pData + 2, 4, (unsigned short*)&pData[6]);
}