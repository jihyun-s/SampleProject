#pragma once

#include "afxwin.h"
#include "SnakeGame.h"
#include "../Observer.h"
#include "../DebuggingModule.h"

// CSnakeGameDlg 대화 상자입니다.

class CSnakeGameDlg : public CDialogEx, public CObserver, public CDebuggingModule
{
	DECLARE_DYNAMIC(CSnakeGameDlg)

public:
	CSnakeGameDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSnakeGameDlg();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_GAME_SNAKE };
private:
	SnakeGame *pSnakeGame;
protected:
	//CListBox m_listmsg;
	BOOL m_bInit;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
