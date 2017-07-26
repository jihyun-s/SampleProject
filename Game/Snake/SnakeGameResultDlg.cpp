// SnakeGameResultDlg.cpp : 구현 파일입니다.
//

#include "../stdafx.h"
#include "../Game.h"
#include "SnakeGameResultDlg.h"
#include "afxdialogex.h"


// CSnakeGameResultDlg 대화 상자입니다.

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


// CSnakeGameResultDlg 메시지 처리기입니다.


void CSnakeGameResultDlg::OnBnClickedButton2()
{
	::SendMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}

void CSnakeGameResultDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemInt(IDC_STATIC_SCORE, m_nScore);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
