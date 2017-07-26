// SnakeGameResultDlg.cpp : ���� �����Դϴ�.
//

#include "../stdafx.h"
#include "../Game.h"
#include "SnakeGameResultDlg.h"
#include "afxdialogex.h"


// CSnakeGameResultDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSnakeGameResultDlg, CDialogEx)

CSnakeGameResultDlg::CSnakeGameResultDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_SNAKE_RESULT_DIALOG, pParent)
{
	m_bRestartGame = FALSE;
	m_nScore = 0;
}

CSnakeGameResultDlg::~CSnakeGameResultDlg()
{
}

void CSnakeGameResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSnakeGameResultDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CSnakeGameResultDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CSnakeGameResultDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSnakeGameResultDlg �޽��� ó�����Դϴ�.


void CSnakeGameResultDlg::OnBnClickedButton2()
{
	::SendMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}

void CSnakeGameResultDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_bRestartGame = TRUE;
	CDialog::OnOK();
}

void CSnakeGameResultDlg::SetScore(int a_nScore)
{
	m_nScore = a_nScore;
}

BOOL CSnakeGameResultDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetDlgItemInt(IDC_STATIC_SCORE, m_nScore);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
