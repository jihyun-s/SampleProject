#pragma once

#include "../stdafx.h"
#include "../utils.h"

#define Trace(s, ...) TraceListbox(m_pDebugConsole, s, __VA_ARGS__)
class CSnakeDebuggingModule
{
public:
	CSnakeDebuggingModule();
	virtual ~CSnakeDebuggingModule();

protected:
	void* m_pDebugConsole;
	void SetDebugConsole(void* a_pDebugConsole=nullptr);
};

