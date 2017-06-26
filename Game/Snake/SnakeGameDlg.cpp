// SnakeGameDlg.cpp : ���� �����Դϴ�.
//

#include "../stdafx.h"
#include "../Game.h"
#include "SnakeGameDlg.h"
#include "afxdialogex.h"
#include "../utils.h"

// CSnakeGameDlg ��ȭ �����Դϴ�.
#define SNAKE_GAME_TIMER 9999

IMPLEMENT_DYNAMIC(CSnakeGameDlg, CDialogEx)

CSnakeGameDlg::CSnakeGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSnakeGameDlg::IDD, pParent)
{
}

CSnakeGameDlg::~CSnakeGameDlg()
{
}

void CSnakeGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_SNAKE, m_listmsg);
}


BEGIN_MESSAGE_MAP(CSnakeGameDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSnakeGameDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDD_BTN_START, &CSnakeGameDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDEXIT, &CSnakeGameDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDD_BTN_RESTART, &CSnakeGameDlg::OnBnClickedBtnRestart)
END_MESSAGE_MAP()


// CSnakeGameDlg �޽��� ó�����Դϴ�.
BOOL CSnakeGameDlg::OnInitDialog()
{	
	CDialogEx::OnInitDialog();
#ifdef _DEBUG
	m_listmsg.ShowWindow(SW_SHOW);
#else
	CRect r;
	m_listmsg.GetWindowRect(&r);
	int listbottom = r.bottom - r.top;
	this->GetWindowRect(&r);
	this->SetWindowPos(NULL, r.left, r.top, r.right-r.left, (r.bottom - r.top) - listbottom, 0);
#endif
	TraceListbox(&m_listmsg, L"[%d]Snake Dialog ����", __LINE__);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CSnakeGameDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}

void CSnakeGameDlg::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case SNAKE_GAME_TIMER:
	{
		if (pSnakeGame->SnakeCanGo)
			pSnakeGame->MoveStraight;
		//else ���� ����
	}
		break;
	default:
		break;
	}
}

void CSnakeGameDlg::OnBnClickedBtnStart()
{
	TraceListbox(&m_listmsg, L"[%d]Snake Game ����", __LINE__);

	// Snake game start
	SetTimer(SNAKE_GAME_TIMER, 10000, NULL); // timer 
	TraceListbox(&m_listmsg, L"[%d]Snake Game Ÿ�̸� ����", __LINE__);
	
}


void CSnakeGameDlg::OnBnClickedExit()
{
	TraceListbox(&m_listmsg, L"[%d]Snake Game ���� ����", __LINE__);

	KillTimer(SNAKE_GAME_TIMER);

	TraceListbox(&m_listmsg, L"[%d]Snake Game Ÿ�̸� ����", __LINE__);
	// To do : dialog ���� �ڵ�

}


void CSnakeGameDlg::OnBnClickedBtnRestart()
{
	TraceListbox(&m_listmsg, L"[%d]Snake Game �����", __LINE__);
	KillTimer(SNAKE_GAME_TIMER);

	TraceListbox(&m_listmsg, L"[%d]Snake Game Ÿ�̸� ����", __LINE__);


	SetTimer(SNAKE_GAME_TIMER, 10000, NULL); // timer 

	TraceListbox(&m_listmsg, L"[%d]Snake Game Ÿ�̸� ����", __LINE__);


}
