// ModifyBuild.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <atlstr.h>
#include <vector>

using namespace ATL;
#include "IniFile.h"
#include "ModifyVersionApi.h"


#define  MIABUILD_PATH _T("D:\\mia-build\\mia-obs-pc-build\\ResInstall\\miabuild.ini")
INT32 ReadMiaBuid()
{
	CIniFile rIniFile;
	if (FALSE == PathFileExists(MIABUILD_PATH))
	{
		MessageBoxW(NULL, _T("提示"), _T("本地miabuild文件不存在"), MB_OK);
		return -1;
	}
	rIniFile.SetFileName(MIABUILD_PATH);
	return rIniFile.GetInt(_T("MiaBuild"), _T("Build"));
}


void  WriteMiaBuid(INT32 nBuild)
{
	CIniFile rIniFile;
	if (FALSE == PathFileExists(MIABUILD_PATH))
	{
		MessageBoxW(NULL, _T("提示"), _T("本地miabuild文件不存在"), MB_OK);
		return ;
	}
	rIniFile.SetFileName(MIABUILD_PATH);
	rIniFile.WriteInt(_T("MiaBuild"), _T("Build"), nBuild);
}

void  WriteMiaVer(CString strName,INT32 nVer)
{
	CIniFile rIniFile;
	if (FALSE == PathFileExists(MIABUILD_PATH))
	{
		MessageBoxW(NULL, _T("提示"), _T("本地miabuild文件不存在"), MB_OK);
		return;
	}
	rIniFile.SetFileName(MIABUILD_PATH);
	rIniFile.WriteInt(_T("Version"), strName, nVer);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//读本地的build号
	INT32 nBuild = 0;
	nBuild = ReadMiaBuid();

	nBuild++;

	CString strBuild;
	strBuild.Format(_T("%d"), nBuild);

	INT32 nLen = strBuild.GetLength();
	if (nLen < 4)
	{
		MessageBoxW(NULL, _T("提示"), _T("Build号少于4位"), MB_OK);
		return -1;
	}
	std::vector<CString> vecBuild;
	vecBuild.push_back(strBuild.Left(nLen-3));   
	vecBuild.push_back(strBuild.Mid(nLen - 3, 1));
	vecBuild.push_back(strBuild.Mid(nLen - 2, 1));
	vecBuild.push_back(strBuild.Mid(nLen - 1, 1));

	if (FALSE == PathFileExists(MIAVERSION_PATH))
	{
		MessageBoxW(NULL, _T("提示"), _T("本地miaversion文件不存在"), MB_OK);
		return -1;
	}


	WriteMiaBuid(nBuild);
	WriteMiaVer(_T("MajorVersion"), _wtoi(vecBuild[0]));
	WriteMiaVer(_T("MinorVersion"), _wtoi(vecBuild[1]));
	WriteMiaVer(_T("TinyVersion"), _wtoi(vecBuild[2]));
	WriteMiaVer(_T("PersonalVersion"), _wtoi(vecBuild[3]));


	ModVerAPI::WriteBuild(strBuild);

	CString strVer;
	strVer.Format(_T("%s,%s,%s,%s"), vecBuild[0], vecBuild[1], vecBuild[2], vecBuild[3]);
	ModVerAPI::WriteVersion(strVer);

	CString strMiaVer;
	strMiaVer.Format(_T("%s.%s.%s.%s"), vecBuild[0], vecBuild[1], vecBuild[2], vecBuild[3]);
	ModVerAPI::WriteMiaVersion(strMiaVer);
	ModVerAPI::WriteNisiVersion(strMiaVer);

	return 0;
}

