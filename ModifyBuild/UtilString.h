#ifndef  __UTILSTRING_H__
#define  __UTILSTRING_H__

#include <atlstr.h>
#include <vector>
using namespace std;
using namespace ATL;

namespace Util
{
	namespace String
	{
		//Utf8  - Unicode
		 BOOL Utf8_2_W(LPCSTR pszSrc, CString& strDst);
		 BOOL W_2_Utf8(LPCWSTR pszSrc, CStringA& strDst);
		 void StringSplit(CString strSource, CString strSplit, vector<CString>& vecSplit);
	}
}

#endif
