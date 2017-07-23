#pragma once

#include "stdafx.h"

class CDebuggingModule
{
public:
	CDebuggingModule();
	virtual ~CDebuggingModule();

protected:
	void* m_pDebugConsole;
	void SetDebugConsole(void* a_pDebugConsole=nullptr);
	void TraceListbox(/*int nMode, void* pCtl, */const WCHAR* s, ...) const;
};

