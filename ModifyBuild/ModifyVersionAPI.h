#ifndef  __MODIFY_NSIAPI_H__
#define  __MODIFY_NSIAPI_H__
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h>
using namespace ATL;
#include "Buffer.h"

#define  MIAVERSION_PATH _T("D:\\mia-build\\mia-obs-src-pc-main\\build\\config\\miaversion.h")

#define  NSISVERSION_PATH _T("D:\\mia-build\\mia-obs-pc-build\\ResInstall\\mia-obs-studio.nsi")

#include <string>

namespace ModVerAPI
{

	BOOL ReadData(std::string& buf, LPCTSTR szPath);
	BOOL WriteData(std::string buf, LPCTSTR szPath);

	void WriteBuild(CString strBuild);
	void WriteMiaVersion(CString strMiaVer);
	void WriteVersion(CString strVer);

	void WriteNisiVersion(CString strVer);
}
#endif
