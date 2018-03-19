#include "stdafx.h"
#include "UtilString.h"


//Utf8 Unicode
BOOL Util::String::Utf8_2_W(LPCSTR pszSrc, CString& strDst)
{
	try
	{
		CA2W pszW(pszSrc, CP_UTF8);
		if (NULL == pszW)
		{
			return FALSE;
		}
		strDst = pszW;
	}
	catch (CAtlException &e)
	{
		e;
		return FALSE;
	}

	return TRUE;
}

BOOL Util::String::W_2_Utf8(LPCWSTR pszSrc, CStringA& strDst)
{
	try
	{
		CW2A pszU8(pszSrc, CP_UTF8);
		if (NULL == pszU8)
		{
			return FALSE;
		}
		strDst = pszU8;
	}
	catch (CAtlException &e)
	{
		e;
		return FALSE;
	}

	return TRUE;
}


void Util::String::StringSplit(CString strSource, CString strSplit, vector<CString>& vecSplit)
{
	vecSplit.clear();
	if (strSource.IsEmpty())
		return;
	if (strSplit.IsEmpty())
		vecSplit.push_back(strSource);
	else
	{
		CString strT = L"";
		int nIndex = 0;
		while (!strSource.IsEmpty())
		{
			nIndex = strSource.Find(strSplit);
			if (nIndex >= 0)
			{
				strT = strSource.Left(nIndex);
				strSource.Delete(0, strT.GetLength() + strSplit.GetLength());
			}
			else
			{
				strT = strSource;
				strSource = L"";
			}
			vecSplit.push_back(strT);
		}
	}
}
