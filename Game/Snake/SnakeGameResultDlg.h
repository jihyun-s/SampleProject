#pragma once


// CSnakeGameResultDlg 대화 상자입니다.

class CSnakeGameResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSnakeGameResultDlg)

public:
	CSnakeGameResultDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSnakeGameResultDlg();

// 대화 상자 데이터입니다.
#if 1 //def AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_SNAKE_RESULT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	BOOL m_bRestartGame;
	DECLARE_MESSAGE_MAP()
	int m_nScore;
public:
	afx_msg void OnBnClickedButton2();
	BOOL IsRestartGame() { return m_bRestartGame; }
	afx_msg void OnBnClickedOk();
	void SetScore(int a_nScore);
	virtual BOOL OnInitDialog();
};
