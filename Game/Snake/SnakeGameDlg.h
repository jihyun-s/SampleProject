#pragma once
#include "SnakeGame.h"
//#include "SnakeGameView.h"
//#include "SnakeGameDocument.h"
#include "afxwin.h"

// CSnakeGameDlg ��ȭ �����Դϴ�.

class CSnakeGameDlg : public CDialogEx
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
	//CCreateContext pContext;
	//CSnakeGameView *pMapView;
	//CSnakeGameDocument *pDocument;
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
	CStatic m_Map;
	afx_msg void OnPaint();
};
