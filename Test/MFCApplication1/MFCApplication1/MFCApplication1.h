
// MFCApplication1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFCApplication1App:
// �� Ŭ������ ������ ���ؼ��� MFCApplication1.cpp�� �����Ͻʽÿ�.
//

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1App theApp;