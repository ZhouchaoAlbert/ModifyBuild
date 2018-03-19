#include "stdafx.h"
#include "ModifyVersionApi.h"

#include "UtilString.h"
namespace ModVerAPI
{
	BOOL ReadData(std::string& buf, LPCTSTR szPath)
	{
		HANDLE hFile = ::CreateFile(szPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			return FALSE;
		}

		::SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
		UINT8 buf2[2 * 1024] = { 0 };
		DWORD uOnceRead = 0;
		while (true)
		{
			uOnceRead = 2 * 1024;
			BOOL bResult = ::ReadFile(hFile, buf2, uOnceRead, &uOnceRead, NULL);
			if (bResult)
			{
				if (0 == uOnceRead)
				{
					break;
				}
				buf.append((char*)buf2, uOnceRead);
			}
			else
			{
				break;
			}
		}
		CloseHandle(hFile);
		return TRUE;
	}

	BOOL WriteData(std::string buf, LPCTSTR szPath)
	{
		DeleteFile(szPath);
		HANDLE hFile = ::CreateFile(szPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			return FALSE;
		}
		::SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
		DWORD nWritten = 0;
		BOOL bResult = ::WriteFile(hFile, buf.data(), buf.length(), &nWritten, NULL);
		CloseHandle(hFile);
		return bResult;
	}


	void WriteBuild(CString strBuild)
	{
		std::string buf;
		if (FALSE == ReadData(buf, MIAVERSION_PATH))
		{
			return;
		}
		ATL::CA2W szBuf(buf.c_str(), CP_UTF8);
		CString strDateW(szBuf);
		INT32 nFind = 0;
		nFind = strDateW.Find(_T("#define MIA_VERNUM"));  //2498624
		if (nFind < 0)
		{
			return;
		}
		INT32 nFind2 = 0;
		nFind2 = strDateW.Find(_T("#define VERSION"));
		if (nFind2 < 0)
		{
			return;
		}
		CString strLeft, strRight;
		strLeft = strDateW.Left(nFind + _tcslen(_T("#define MIA_VERNUM")));
		strRight = strDateW.Right(strDateW.GetLength() - nFind2);

		strLeft.AppendFormat(_T("   %s\r\n\r\n"), strBuild);
	
		CString strModDate = strLeft + strRight;
		ATL::CW2A strModDateA(strModDate, CP_UTF8);
	
		if (FALSE == WriteData(strModDateA.m_psz, MIAVERSION_PATH))
		{
			return;
		}
	}

	void WriteMiaVersion(CString strMiaVer)
	{
		std::string buf;
		if (FALSE == ReadData(buf, MIAVERSION_PATH))
		{
			return;
		}
		ATL::CA2W szBuf(buf.c_str(), CP_UTF8);
		CString strDateW(szBuf);
		INT32 nFind = 0;
		nFind = strDateW.Find(_T("#define MIA_VERSION"));  
		if (nFind < 0)
		{
			return;
		}
		INT32 nFind2 = 0;
		nFind2 = strDateW.Find(_T("#define MIA_VERNUM"));
		if (nFind2 < 0)
		{
			return;
		}
		CString strLeft, strRight;
		strLeft = strDateW.Left(nFind + _tcslen(_T("#define MIA_VERSION")));
		strRight = strDateW.Right(strDateW.GetLength() - nFind2);

		strLeft.AppendFormat(_T("   \"%s\"\r\n"), strMiaVer);

		CString strModDate = strLeft + strRight;
		ATL::CW2A strModDateA(strModDate, CP_UTF8);

		if (FALSE == WriteData(strModDateA.m_psz, MIAVERSION_PATH))
		{
			return;
		}
	}
	void WriteVersion(CString strVer)
	{
		std::string buf;
		if (FALSE == ReadData(buf, MIAVERSION_PATH))
		{
			return;
		}
		ATL::CA2W szBuf(buf.c_str(), CP_UTF8);
		CString strDateW(szBuf);
		INT32 nFind = 0;
		nFind = strDateW.Find(_T("#define VERSION"));
		if (nFind < 0)
		{
			return;
		}
		INT32 nFind2 = 0;
		nFind2 = strDateW.Find(_T("#define FILE_VERSION"));
		if (nFind2 < 0)
		{
			return;
		}
		CString strLeft, strRight;
		strLeft = strDateW.Left(nFind + _tcslen(_T("#define VERSION")));
		strRight = strDateW.Right(strDateW.GetLength() - nFind2);

		strLeft.AppendFormat(_T("   %s\r\n"), strVer);

		CString strModDate = strLeft + strRight;
		ATL::CW2A strModDateA(strModDate, CP_UTF8);

		if (FALSE == WriteData(strModDateA.m_psz, MIAVERSION_PATH))
		{
			return;
		}
	}
	void WriteNisiVersion(CString strVer)
	{
		std::string buf;
		if (FALSE == ReadData(buf, NSISVERSION_PATH))
		{
			return;
		}
		ATL::CA2W szBuf(buf.c_str(), CP_UTF8);
		CString strDateW(szBuf);
		INT32 nFind = 0;
		nFind = strDateW.Find(_T("!define PRODUCT_VERSION"));
		if (nFind < 0)
		{
			return;
		}
		INT32 nFind2 = 0;
		nFind2 = strDateW.Find(_T("!define PRODUCT_SHORTCUT_NAME"));
		if (nFind2 < 0)
		{
			return;
		}
		CString strLeft, strRight;
		strLeft = strDateW.Left(nFind + _tcslen(_T("!define PRODUCT_VERSION")));
		strRight = strDateW.Right(strDateW.GetLength() - nFind2);

		strLeft.AppendFormat(_T("   \"%s\"\r\n"), strVer);

		CString strModDate = strLeft + strRight;
		ATL::CW2A strModDateA(strModDate, CP_UTF8);

		if (FALSE == WriteData(strModDateA.m_psz, NSISVERSION_PATH))
		{
			return;
		}
	}
}