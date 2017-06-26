// SnakeGameDlg.cpp : 구현 파일입니다.
//

#include "../stdafx.h"
#include "../Game.h"
#include "SnakeGameDlg.h"
#include "afxdialogex.h"
#include "../utils.h"

// CSnakeGameDlg 대화 상자입니다.
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


// CSnakeGameDlg 메시지 처리기입니다.
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
	TraceListbox(&m_listmsg, L"[%d]Snake Dialog 생성", __LINE__);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSnakeGameDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		//else 게임 종료
	}
		break;
	default:
		break;
	}
}

void CSnakeGameDlg::OnBnClickedBtnStart()
{
	TraceListbox(&m_listmsg, L"[%d]Snake Game 시작", __LINE__);

	// Snake game start
	SetTimer(SNAKE_GAME_TIMER, 10000, NULL); // timer 
	TraceListbox(&m_listmsg, L"[%d]Snake Game 타이머 생성", __LINE__);
	
}


void CSnakeGameDlg::OnBnClickedExit()
{
	TraceListbox(&m_listmsg, L"[%d]Snake Game 종료 시작", __LINE__);

	KillTimer(SNAKE_GAME_TIMER);

	TraceListbox(&m_listmsg, L"[%d]Snake Game 타이머 종료", __LINE__);
	// To do : dialog 종료 코드

}


void CSnakeGameDlg::OnBnClickedBtnRestart()
{
	TraceListbox(&m_listmsg, L"[%d]Snake Game 재시작", __LINE__);
	KillTimer(SNAKE_GAME_TIMER);

	TraceListbox(&m_listmsg, L"[%d]Snake Game 타이머 종료", __LINE__);


	SetTimer(SNAKE_GAME_TIMER, 10000, NULL); // timer 

	TraceListbox(&m_listmsg, L"[%d]Snake Game 타이머 생성", __LINE__);


}
