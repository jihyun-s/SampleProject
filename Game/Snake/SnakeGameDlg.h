#pragma once
#include "SnakeGame.h"
#include "SnakeGameView.h"
//#include "SnakeGameDocument.h"
#include "afxwin.h"

// CSnakeGameDlg 대화 상자입니다.

class CSnakeGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSnakeGameDlg)

public:
	CSnakeGameDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSnakeGameDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GAME_SNAKE };
private:
	SnakeGame *pSnakeGame;
	//CCreateContext pContext;
	//CSnakeGameView *pMapView;
	//CSnakeGameDocument *pDocument;
protected:
	CListBox m_listmsg;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
 	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedBtnRestart();
	CStatic m_Map;
};
