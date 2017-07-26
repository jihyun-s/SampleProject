#pragma once


// CSnakeGameResultDlg ��ȭ �����Դϴ�.

class CSnakeGameResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSnakeGameResultDlg)

public:
	CSnakeGameResultDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSnakeGameResultDlg();

// ��ȭ ���� �������Դϴ�.
#if 1 //def AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_SNAKE_RESULT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
