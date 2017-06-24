#pragma once

void _MessageBox(int nMode, void* pCtl, WCHAR* s, ...);
#define TraceListbox(pCtl, s, ...)	_MessageBox(2, pCtl, s, __VA_ARGS__)
char* UnicodeToUTF8(CString str, BOOL bUTF8 = TRUE);