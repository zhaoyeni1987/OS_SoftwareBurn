#pragma once

#include "Process.h"

class CProcessUploadBin : public CProcess
{
	Q_OBJECT

public:
	CProcessUploadBin();
	void ReadBin(QString strBinPath);
	unsigned short GetPackageNum();
	unsigned short GetCurPackageNum();

	unsigned int GetCrc32();
	unsigned int GetBinLength();

signals:
	void UploadInfo();
	void Completion(float value);

private:
	EN_PROCESS_CRITERION ReceiveCriterion(unsigned char* pData, unsigned int size);
	void ChangeData(unsigned char* pData);
	void FirstData(unsigned char* pData);

	unsigned int m_LengthBin;
	unsigned short m_PackageNum;
	unsigned short m_CurPackageIndex;

	unsigned char m_CurPackageValidDataLength;
	unsigned char m_LessLength;

	bool m_bSmallLessOne;

	QByteArray m_Bin;
	char* m_pBin;

	unsigned char m_errCount;

	bool m_bShouldNext;

	unsigned int m_Crc32;
};