
// GameDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Game.h"
#include "GameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGameDlg 대화 상자


CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{

	m_pSnakeGameDlg = NULL;
}

CGameDlg::~CGameDlg()
{
	if (m_pSnakeGameDlg)
		delete m_pSnakeGameDlg;
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

void CGameDlg::OnBnClickedButton1()
{
	// Snake
	if (!m_pSnakeGameDlg)
	{
		m_pSnakeGameDlg = new CSnakeGameDlg(this);
		m_pSnakeGameDlg->Create(CSnakeGameDlg::IDD, this);
	}
	m_pSnakeGameDlg->ShowWindow(SW_SHOW);
}
