#include "SnakeDebuggingModule.h"

CSnakeDebuggingModule::CSnakeDebuggingModule()
{
	m_pDebugConsole = nullptr;
}
CSnakeDebuggingModule::~CSnakeDebuggingModule()
{
}

void CSnakeDebuggingModule::SetDebugConsole(void* a_pDebugConsole)
{
	m_pDebugConsole = a_pDebugConsole;
}

