
// GameDlg.h : ��� ����
//

#pragma once
#include "SnakeGameDlg.h"

// CGameDlg ��ȭ ����
class CGameDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CGameDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	virtual ~CGameDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	CSnakeGameDlg* m_pSnakeGameDlg;
};
