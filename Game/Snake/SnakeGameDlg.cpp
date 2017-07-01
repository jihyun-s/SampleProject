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
	if (pSnakeGame)
		delete pSnakeGame;
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
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Dialog ����", __LINE__);

#if 0 // ViewTest2
	pContext.m_pNewViewClass = RUNTIME_CLASS(CSnakeGameView);
	//pContext.m_pCurrentDoc = new CSnakeGameDocument;
	pMapView = (CSnakeGameView *)(((CFrameWnd*)this)->CreateView(&pContext));
	ASSERT(pMapView);
	pMapView->ShowWindow(SW_NORMAL);
	RECT r;
	m_Map.GetWindowRect(&r);
	pMapView->MoveWindow(&r);
	pMapView->Invalidate();
#endif
#if 0 // View Test2
	CRuntimeClass  *pObject;
	pObject = RUNTIME_CLASS(CSnakeGameView);
	pMapView = (CSnakeGameView*)pObject->CreateObject();
	RECT r;
	m_Map.GetWindowRect(&r);
	if (!pMapView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		r, this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	pMapView->RedrawWindow();
#endif
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
		TraceListbox(&m_listmsg, L"[%d][DLG] Snake �̵�", __LINE__);
		if (!pSnakeGame->MoveStraight())	// die
		{
			KillTimer(SNAKE_GAME_TIMER);
		}
	}
		break;
	default:
		break;
	}
}

void CSnakeGameDlg::OnBnClickedBtnStart()
{
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game ����", __LINE__);

	// Snake game start
	SetTimer(SNAKE_GAME_TIMER, 1000, NULL); // timer 
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game Ÿ�̸� ����", __LINE__);

#ifdef _DEBUG
	pSnakeGame = new SnakeGame(&m_listmsg);
#else
	pSnakeGame = new SnakeGame();
#endif
}


void CSnakeGameDlg::OnBnClickedExit()
{
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game ���� ����", __LINE__);

	KillTimer(SNAKE_GAME_TIMER);
	
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game Ÿ�̸� ����", __LINE__);
	
	CDialogEx::OnCancel();
}


void CSnakeGameDlg::OnBnClickedBtnRestart()
{
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game �����", __LINE__);
	KillTimer(SNAKE_GAME_TIMER);
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game Ÿ�̸� ����", __LINE__);
	if (pSnakeGame)
		delete pSnakeGame;
	pSnakeGame = NULL;

	SetTimer(SNAKE_GAME_TIMER, 1000, NULL); // timer 
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game Ÿ�̸� ����", __LINE__);

#ifdef _DEBUG
	pSnakeGame = new SnakeGame(&m_listmsg);
#else
	pSnakeGame = new SnakeGame();
#endif
}
