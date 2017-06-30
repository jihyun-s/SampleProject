#pragma once
#include "SnakeGame.h"

// CSnakeGameDlg ��ȭ �����Դϴ�.

class CSnakeGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSnakeGameDlg)

public:
	CSnakeGameDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSnakeGameDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GAME_SNAKE };
private:
	SnakeGame *pSnakeGame;
protected:
	CListBox m_listmsg;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedBtnRestart();
};