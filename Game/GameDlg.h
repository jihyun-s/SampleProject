
// GameDlg.h : ��� ����
//

#pragma once

#include "Snake/SnakeGameDlg.h"

// CGameDlg ��ȭ ����
class CGameDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CGameDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	~CGameDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
protected:
	CSnakeGameDlg *m_pSnakeGameDlg;
};
