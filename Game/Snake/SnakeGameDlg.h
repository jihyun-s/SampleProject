#pragma once


// CSnakeGameDlg 대화 상자입니다.

class CSnakeGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSnakeGameDlg)

public:
	CSnakeGameDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSnakeGameDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GAME_SNAKE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
