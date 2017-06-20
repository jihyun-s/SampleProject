
// GameDlg.h : 헤더 파일
//

#pragma once
#include "SnakeGameDlg.h"

// CGameDlg 대화 상자
class CGameDlg : public CDialogEx
{
// 생성입니다.
public:
	CGameDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	virtual ~CGameDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	CSnakeGameDlg* m_pSnakeGameDlg;
};
