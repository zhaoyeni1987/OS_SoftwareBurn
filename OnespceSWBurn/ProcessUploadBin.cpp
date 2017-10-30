#include "ProcessUploadBin.h"
#include "crc.h"

CProcessUploadBin::CProcessUploadBin()
{
	SetName("UploadBin");

	m_CurPackageValidDataLength = 0;
	m_CurPackageIndex = 0;
	m_PackageNum = 0;

	m_bSmallLessOne = false;
	m_bShouldNext = false;
	m_errCount = 0;
	m_Crc32 = 0;
	m_LengthBin = 0;
}

void CProcessUploadBin::FirstData(unsigned char* pData)
{
	memset(pData, 0, sizeof(unsigned char) * 263);
	pData[0] = 0x55;
	pData[1] = 0xAA;
	pData[2] = 0xFF;
	pData[3] = 0x00;
	pData[4] = 0x02;
	pData[5] = 0xF2;
	pData[6] = (unsigned char)(m_PackageNum & 0x00FF);
	pData[7] = (unsigned char)((m_PackageNum >> 8) & 0x00FF);
	pData[8] = (unsigned char)(m_CurPackageIndex & 0x00FF);
	pData[9] = (unsigned char)((m_CurPackageIndex >> 8) & 0x00FF);

	if (m_bSmallLessOne)
	{
		pData[10] = m_LessLength;
		for (int i = 0; i < m_LessLength; i++)
		{
			pData[11 + i] = (unsigned char)*(m_pBin + i);
		}	
	}
	else
	{
		pData[10] = 250;
		for (int i = 0; i < 250; i++)
		{
			pData[11 + i] = (unsigned char)*(m_pBin + i);
		}
	}

	Insert16CRC_U8(pData + 2, 259, (unsigned short*)&pData[261]);
}

void CProcessUploadBin::ChangeData(unsigned char* pData)
{
	if (m_bShouldNext)
	{
		m_bShouldNext = false;
		pData[3]++;

		m_CurPackageIndex++;

		if (m_CurPackageIndex >= (m_PackageNum - 1))				//last
		{
			memset(pData + 6, 0, sizeof(unsigned char) * 255);
			pData[6] = (unsigned char)(m_PackageNum & 0x00FF);
			pData[7] = (unsigned char)((m_PackageNum >> 8) & 0x00FF);
			pData[8] = (unsigned char)(m_CurPackageIndex & 0x00FF);
			pData[9] = (unsigned char)((m_CurPackageIndex >> 8) & 0x00FF);
			pData[10] = m_LessLength;
			memcpy(pData + 11, m_pBin + (m_CurPackageIndex * 250), sizeof(unsigned char) * m_LessLength);
		}
		else
		{
			memset(pData + 6, 0, sizeof(unsigned char) * 255);
			pData[6] = (unsigned char)(m_PackageNum & 0x00FF);
			pData[7] = (unsigned char)((m_PackageNum >> 8) & 0x00FF);
			pData[8] = (unsigned char)(m_CurPackageIndex & 0x00FF);
			pData[9] = (unsigned char)((m_CurPackageIndex >> 8) & 0x00FF);
			pData[10] = 250;
			memcpy(pData + 11, m_pBin + (m_CurPackageIndex * 250), sizeof(unsigned char) * 250);
		}

		emit Completion((float)m_CurPackageIndex / (float)(m_PackageNum - 1));
	}
	else
	{
		pData[3]++;
	}

	Insert16CRC_U8(pData + 2, 259, (unsigned short*)&pData[261]);
}

unsigned short CProcessUploadBin::GetPackageNum()
{
	return m_CurPackageIndex;
}

unsigned short CProcessUploadBin::GetCurPackageNum()
{
	return m_PackageNum;
}

EN_PROCESS_CRITERION CProcessUploadBin::ReceiveCriterion(unsigned char* pData, unsigned int size)
{
	if (pData[6] != 0x22)
		return EN_PROCESS_CONTINUE;

	if (pData[7] == 0x00)
	{
		unsigned short responseSum = pData[9] * 256 + pData[8];
		unsigned short responseCur = pData[11] * 256 + pData[10];
		if ((m_CurPackageIndex == responseCur)
			&& (m_PackageNum == responseSum))
		{
			if (m_CurPackageIndex >= (m_PackageNum - 1))
			{
				m_errCount = 0;
				return EN_PROCESS_SUCCESS;
			}
			else
			{
				m_bShouldNext = true;
				m_errCount = 0;
				return EN_PROCESS_CONTINUE;
			}
		}
		else
		{
			goto ERROR_HERE;
		}
	}
	else
	{
		goto ERROR_HERE;

		return EN_PROCESS_SUCCESS;
	}

ERROR_HERE:
	m_errCount++;
	if (m_errCount > 3)
		return EN_PROCESS_FAILURE;

	return EN_PROCESS_CONTINUE;
}

void CProcessUploadBin::ReadBin(QString strBinPath)
{
	QFile tmpfile(strBinPath);
	if (!tmpfile.open(QIODevice::ReadOnly))
		return;

	m_Bin = tmpfile.readAll();
	tmpfile.close();

	if (m_Bin.length() <= 0)
		return;

	m_LengthBin = m_Bin.length();
	m_PackageNum = m_LengthBin / 250;
	m_LessLength = m_LengthBin % 250;

	m_Crc32 = CalCRC32((unsigned char*)m_Bin.data(), m_LengthBin);

	if (m_LessLength > 0)
		m_PackageNum++;

	m_CurPackageIndex = 0;

	if (m_PackageNum == 1)
	{
		m_bSmallLessOne = true;
	}

	m_pBin = m_Bin.data();
}

unsigned int CProcessUploadBin::GetCrc32()
{
	return m_Crc32;
}

unsigned int CProcessUploadBin::GetBinLength()
{
	return m_LengthBin;
}