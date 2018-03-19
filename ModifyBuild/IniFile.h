#ifndef _INI_FILE_H_
#define _INI_FILE_H_
/*
ini文件操作
*/
#include <Windows.h>
#include <tchar.h>
#include <string>

class CIniFile
{
public:
	CIniFile(void){}
	virtual ~CIniFile(void){}
public:
	/*
	函数描述：写整形数据到ini文件中
	参数：
		szItemName项的名称
		szKeyName项下面的键的名称
		nValues要设置的值
	返回值：成功返回TRUE,失败返回FALSE
	*/
	BOOL  WriteInt(LPCTSTR szItemName, LPCTSTR szKeyName, int nValues)
	{
		BOOL	bRet = FALSE;

		do 
		{
			m_dwLastError = ERROR_INVALID_PARAMETER;

			if (NULL == szItemName)
			{
				break;
			}
			if (NULL == szKeyName)
			{
				break;
			}

			TCHAR	szValues[16] = {0};
			::wsprintf(szValues, _T("%d"), nValues);
			bRet = ::WritePrivateProfileString(szItemName, szKeyName, szValues, m_strFileName.c_str());
			if (!bRet)
			{
				m_dwLastError = ::GetLastError();
			}
		} while (0);

		return bRet;
	}

	/*
	函数描述：写字符串数据到ini文件中
	参数：
		szItemName项的名称
		szKeyName项下面的键的名称
		szValues要设置的值,为NULL则设置空值
	返回值：成功返回TRUE,失败返回FALSE
	*/
	BOOL  WriteStr( LPCTSTR szItemName, LPCTSTR szKeyName, LPCTSTR szValues)
	{
		BOOL	bRet = FALSE;

		do 
		{
			m_dwLastError = ERROR_INVALID_PARAMETER;

			if (NULL == szItemName)
			{
				break;
			}
			if (NULL == szKeyName)
			{
				break;
			}

			bRet = ::WritePrivateProfileString(szItemName, szKeyName, szValues, m_strFileName.c_str());
			if (!bRet)
			{
				m_dwLastError = ::GetLastError();
			}
		} while (0);

		return bRet;
	}

	/*
	函数描述：获取指定项，指定键的数据
	参数：
		szItemName项的名称
		szKeyName项下面的键的名称
		szBuffer 接收的数据存放位置
		nSize szBuffer大小
	返回值：如果键存在则返回键的值，不存则返回空字符串
	*/
	void  GetStr( LPCTSTR szItemName, LPCTSTR szKeyName, LPTSTR szBuffer, int nSize)
	{
		do 
		{
			m_dwLastError = ERROR_INVALID_PARAMETER;
			if (NULL == szBuffer)
			{
				break;
			}
			if (NULL == szItemName)
			{
				break;
			}
			if (NULL == szKeyName)
			{
				break;
			}
			GetPrivateProfileString(szItemName, szKeyName, _T(""), szBuffer, nSize, m_strFileName.c_str());
			m_dwLastError = GetLastError();
		} while (0);
	}

	/*
	函数描述：获取指定项，指定键的数据
	参数：
		szItemName项的名称
		szKeyName项下面的键的名称
	返回值：如果键存在则返回键的值，不存则返回空字符串
	*/
	int  GetInt( LPCTSTR szItemName,  LPCTSTR szKeyName)
	{
		int		nRet = 0;

		do 
		{
			m_dwLastError = ERROR_INVALID_PARAMETER;
			if (NULL == szItemName)
			{
				break;
			}
			if (NULL == szKeyName)
			{
				break;
			}

			nRet = GetPrivateProfileInt(szItemName, szKeyName, 0, m_strFileName.c_str());
			m_dwLastError = GetLastError();
		} while (0);

		return nRet;
	}

	/*
	函数描述：设置INI文件名，该文件名必须是文件的全路径
	参数：szFileName文件名
	返回值：无
	*/
	void  SetFileName( LPCTSTR szFileName)
	{
		if (szFileName)
		{
			m_strFileName = szFileName;
		}
	}

	/*
	函数描述：获取函数出错时候的错误码
	参数：无
	返回值：函数的错误码
	*/
	DWORD  GetLastError()
	{
		return m_dwLastError;
	}
private:
	DWORD						m_dwLastError;//错误码
	std::basic_string<TCHAR>	m_strFileName;//ini文件名称
};

#endif