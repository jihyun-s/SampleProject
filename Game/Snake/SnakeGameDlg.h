#pragma once


// CSnakeGameDlg ��ȭ �����Դϴ�.

class CSnakeGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSnakeGameDlg)

public:
	CSnakeGameDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSnakeGameDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GAME_SNAKE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
