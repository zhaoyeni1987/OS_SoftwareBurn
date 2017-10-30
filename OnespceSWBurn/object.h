#pragma once

#include <QString>
#include <QVector>
#include <QtXml>

class CObject
{
public:
	CObject();
	CObject(QString strName);
	void SetName(QString strName);
	QString GetName();

	static int FindObject(QString strName, QVector<CObject*>& vpObject);
	static int SortObject(QVector<CObject*>& vpObject);
	static int SwapObject(QString strFrom, QString strTo, QVector<CObject*>& vpObject);
	static int SwapObject(int from, int to, QVector<CObject*>& vpObject);

	virtual QDomElement GetObjectXML(QDomDocument* pDoc) { QDomElement aaa; return aaa; }

protected:
	void SetTypeName(QString strTypeName);
	QDomElement GetTypeElementXML(QDomDocument* pDoc);

private:
	QString m_strName;
	QString m_strTypeName;
};
