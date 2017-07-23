#pragma once

#include "afxwin.h"
#include "SnakeGame.h"
#include "../Observer.h"
#include "../DebuggingModule.h"

// CSnakeGameDlg ��ȭ �����Դϴ�.

class CSnakeGameDlg : public CDialogEx, public CObserver, public CDebuggingModule
{
	DECLARE_DYNAMIC(CSnakeGameDlg)

public:
	CSnakeGameDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSnakeGameDlg();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GAME_SNAKE };
private:
	SnakeGame *pSnakeGame;
protected:
	//CListBox m_listmsg;
	BOOL m_bInit;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	virtual void UpdateUI();
	virtual void UpdateScore(int a_nScore);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedBtnRestart();
	CStatic m_Map;
	afx_msg void OnPaint();
};
