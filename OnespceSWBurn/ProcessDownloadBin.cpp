#include "ProcessDownloadBin.h"
#include "crc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CProcessDownloadBin::CProcessDownloadBin()
{
	SetName("DownloadBin");

	m_lengthBin = 0;
	m_packageNum = 0;
	m_lengthLess = 0;
	m_curPackage = 0;

	m_bShoudNext = false;

	m_pBin = NULL;
}

EN_PROCESS_CRITERION CProcessDownloadBin::ReceiveCriterion(unsigned char* pData, unsigned int size)
{
	if (pData[6] != 0x22)
		return EN_PROCESS_CONTINUE;

	unsigned short curPackage = pData[8] + pData[9] * 256;

	if (m_curPackage == curPackage)
	{
		m_bShoudNext = true;

		if (m_curPackage == (m_packageNum - 1))
		{
			memcpy(m_pBin + m_curPackage * 250, pData + 11, m_reminder);
			FILE* pFile = fopen("receive_bin", "wb+");
			fwrite(m_pBin, 1, m_lengthBin, pFile);
			fclose(pFile);
			free(m_pBin);
			m_pBin = NULL;
			return EN_PROCESS_SUCCESS;
		}
		else
		{
			memcpy(m_pBin + m_curPackage * 250, pData + 11, 250);
		}

		return EN_PROCESS_CONTINUE;
	}
	else
	{
		return EN_PROCESS_CONTINUE;
	}
	
}

void CProcessDownloadBin::ChangeData(unsigned char* pData)
{
	if (m_bShoudNext)
	{
		m_bShoudNext = false;

		m_curPackage++;
		pData[3]++;

		pData[6] = (unsigned char)(m_curPackage & 0x00FF);
		pData[7] = (unsigned char)((m_curPackage >> 8) & 0x00FF);
	}
	else
	{
		pData[3]++;
	}

	Insert16CRC_U8(pData + 2, 6, (unsigned short*)&pData[8]);
}

void CProcessDownloadBin::FirstData(unsigned char* pData)
{
	pData[6] = (unsigned char)(m_curPackage & 0x00FF);
	pData[7] = (unsigned char)((m_curPackage >> 8) & 0x00FF);

	Insert16CRC_U8(pData + 2, 6, (unsigned short*)&pData[8]);
}

void CProcessDownloadBin::SetBinInfo(unsigned int lengthBin)
{
	m_lengthBin = lengthBin;

	m_packageNum = m_lengthBin / 250;
	m_reminder = (unsigned char)(m_lengthBin % 250);
	if (m_reminder != 0)
		m_packageNum++;

	m_curPackage = 0;

	m_pBin = (unsigned char*)malloc(sizeof(unsigned char) * m_lengthBin);
	memset(m_pBin, 0, sizeof(unsigned char) * m_lengthBin);
}