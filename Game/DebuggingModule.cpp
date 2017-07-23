#include "DebuggingModule.h"
#include <string>
#include <Windows.h>

CString GetAppDataPath()
{
	static WCHAR szFileName[MAX_PATH] = { 0, };
	if (_waccess(szFileName, 0))
	{
		WCHAR szAppName[MAX_PATH] = { 0, };
		WCHAR szTitle[MAX_PATH] = { 0, };
		if (::GetModuleFileName(AfxGetInstanceHandle(), szAppName, MAX_PATH))
		{
			_wsplitpath(szAppName, NULL, NULL, szTitle, NULL);
		}

		SHGetSpecialFolderPath(NULL, szFileName, CSIDL_COMMON_APPDATA, FALSE);
		wcscat(szFileName, L"\\");
		wcscat(szFileName, szTitle);
		if (_waccess(szFileName, 0))
			_wmkdir(szFileName);
	}

	return szFileName;
}

CString GetTimeByFormat(CString strFormat)
{
	time_t nTmpTime;
	struct tm *aTime;

	nTmpTime = time(0);
	aTime = localtime(&nTmpTime);

	WCHAR str2[1024] = { 0, };
	wcsftime(str2, 1024, strFormat, aTime);

	return str2;
}

char* UnicodeToUTF8(CString str, BOOL bUTF8=true)
{
	char* pBuffer = NULL;
	if (!str.IsEmpty() && str.GetLength() > 0)
	{
		pBuffer = (char*)malloc(str.GetLength() * 3);
		memset(pBuffer, 0, str.GetLength() * 3);
		int nLen = WideCharToMultiByte(bUTF8 ? CP_UTF8 : CP_ACP, 0, (LPWSTR)(LPCWSTR)str, str.GetLength(), pBuffer, str.GetLength() * 2, 0, 0);
		pBuffer[nLen] = '\0';
	}

	return pBuffer;
}
void SaveToLogFile(CString strMsg)
{
	CString strFile;
	strFile.Format(L"%s\\log_%s.txt", GetAppDataPath(), GetTimeByFormat(L"%Y%m%d"));
	FILE* pf = _wfopen(strFile, L"ab+");
	if (pf)
	{
		char* str = UnicodeToUTF8(strMsg);
		fwrite(str, 1, strlen(str), pf);
		free(str);
		fclose(pf);
	}
}

void CDebuggingModule::TraceListbox(/*int nMode, void* pCtl, */const WCHAR* s, ...) const
{
#ifdef _DEBUG
	int nMode = 2;
	void* pCtl = m_pDebugConsole;

	WCHAR *str = (WCHAR*)malloc(sizeof(WCHAR) * 1024 * 10);
	va_list ap;

	va_start(ap, s);
	if (s)
	{
		wvsprintf(str, s, ap);
		wcscat(str, L"\n");
	}
	va_end(ap);

	time_t nTmpTime;
	struct tm *aTime;

	nTmpTime = time(0);
	aTime = localtime(&nTmpTime);

	WCHAR *str2 = (WCHAR*)malloc(sizeof(WCHAR) * 1024 * 10);
	
	if (nMode != 0)
	{
		wcsftime(str2, 1024 * 10, L"[%x %X]", aTime);

		wcscat(str2, L" ");
		wcscat(str2, str);
	}
	else
		wcscpy(str2, str);
	free(str);

	if (nMode == 1)
		OutputDebugString(str2);
	else if (nMode == 2 && pCtl != NULL)
	{
		CListBox* lstmsg = (CListBox*)pCtl;
		if (lstmsg && lstmsg->GetSafeHwnd())
		{
			lstmsg->AddString(str2);

			lstmsg->SetHorizontalExtent(1500);

			lstmsg->SetCurSel(lstmsg->GetCount() - 1);
		}

	}
	//SaveToLogFile(str2);
	free(str2);
#endif
}

CDebuggingModule::CDebuggingModule()
{
	m_pDebugConsole = nullptr;
}
CDebuggingModule::~CDebuggingModule()
{
}

void CDebuggingModule::SetDebugConsole(void* a_pDebugConsole)
{
	m_pDebugConsole = a_pDebugConsole;
}

