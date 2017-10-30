#include "object.h"

CObject::CObject()
{

}

CObject::CObject(QString strName)
{
	m_strName = strName;
}

void CObject::SetName(QString strName)
{
	m_strName = strName;
}

QString CObject::GetName()
{
	return m_strName;
}

void CObject::SetTypeName(QString strTypeName)
{
	m_strTypeName = strTypeName;
}

QDomElement CObject::GetTypeElementXML(QDomDocument* pDoc)
{
	QDomElement element = pDoc->createElement(m_strTypeName);
	
	element.setAttribute("name", m_strName);

	pDoc->appendChild(element);

	return element;
}

int CObject::FindObject(QString strName, QVector<CObject*>& vpObject)
{
	int size = vpObject.size();
	for (int i = 0; i < size; i++)
	{
		if (vpObject[i]->GetName() == strName)
		{
			return i;
		}
	}

	return -1;
}

int CObject::SortObject(QVector<CObject*>& vpObject)
{
	

	return 0;
}

int CObject::SwapObject(QString strFrom, QString strTo, QVector<CObject*>& vpObject)
{
	int from = CObject::FindObject(strFrom, vpObject);
	if (from == -1)
		return -1;

	int to = CObject::FindObject(strTo, vpObject);
	if (to == -1)
		return -1;

	vpObject.move(from, to);

	return 0;
}

int CObject::SwapObject(int from, int to, QVector<CObject*>& vpObject)
{
	if ((from >= vpObject.size())
		|| (to >= vpObject.size()))
		return -1;

	vpObject.move(from, to);

	return 0;
}