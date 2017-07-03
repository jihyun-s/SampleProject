// SnakeGameDlg.cpp : 구현 파일입니다.
//

#include "../stdafx.h"
#include "../Game.h"
#include "SnakeGameDlg.h"
#include "afxdialogex.h"
#include "../utils.h"

// CSnakeGameDlg 대화 상자입니다.
#define SNAKE_GAME_TIMER 9999
#define SNAKE_GAME_MAKE_APPLE_TIMER 9998

IMPLEMENT_DYNAMIC(CSnakeGameDlg, CDialogEx)

CSnakeGameDlg::CSnakeGameDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CSnakeGameDlg::IDD, pParent)
{
	pSnakeGame = NULL;
}

CSnakeGameDlg::~CSnakeGameDlg()
{
	if (pSnakeGame)
		delete pSnakeGame;
}

BOOL CSnakeGameDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pSnakeGame)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
		{
			pSnakeGame->ChangDirection(LEFT);
			return TRUE;
		}
		case VK_RIGHT:
		{
			pSnakeGame->ChangDirection(RIGHT);
			return TRUE;
		}
		case VK_UP:
		{
			pSnakeGame->ChangDirection(UP);
			return TRUE;
		}
		case VK_DOWN:
		{
			pSnakeGame->ChangDirection(DOWN);
			return TRUE;
		}
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSnakeGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MAP, m_Map);
	DDX_Control(pDX, IDC_LIST_SNAKE, m_listmsg);
}


BEGIN_MESSAGE_MAP(CSnakeGameDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSnakeGameDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDD_BTN_START, &CSnakeGameDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDEXIT, &CSnakeGameDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDD_BTN_RESTART, &CSnakeGameDlg::OnBnClickedBtnRestart)
	ON_WM_PAINT()
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
	this->SetWindowPos(NULL, r.left, r.top, r.right - r.left, (r.bottom - r.top) - listbottom, 0);
#endif
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Dialog 생성", __LINE__);

#if 0 // View Test2
	pContext.m_pNewViewClass = RUNTIME_CLASS(CSnakeGameView);
	//pContext.m_pCurrentDoc = new CSnakeGameDocument;
	pMapView = (CSnakeGameView *)(((CFrameWnd*)this)->CreateView(&pContext));
	ASSERT(pMapView);
	pMapView->ShowWindow(SW_NORMAL);
	RECT r;
	m_Map.GetWindowRect(&r);
	pMapView->MoveWindow(&r);

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

#ifdef _DEBUG
	pSnakeGame = new SnakeGame(&m_listmsg);
#else
	pSnakeGame = new SnakeGame();
#endif
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSnakeGameDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
CRect r;
void CSnakeGameDlg::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case SNAKE_GAME_TIMER:
	{
		TraceListbox(&m_listmsg, L"[%d][DLG] Snake 이동", __LINE__);
		SetTimer(SNAKE_GAME_MAKE_APPLE_TIMER, 5000, NULL);
		if (!pSnakeGame->MoveStraight())	// die
		{
				KillTimer(SNAKE_GAME_TIMER);
				KillTimer(SNAKE_GAME_MAKE_APPLE_TIMER);
		 }
	}
		break;
	case SNAKE_GAME_MAKE_APPLE_TIMER:
	{
		if (pSnakeGame)
			pSnakeGame->MakeApple();
		break;
	}
	default:
		break;
	}
}

void CSnakeGameDlg::OnBnClickedBtnStart()
{
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game 시작", __LINE__);

	// Snake game start
	SetTimer(SNAKE_GAME_TIMER, 1000, NULL); // timer 
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game 타이머 생성", __LINE__);

	SetTimer(SNAKE_GAME_MAKE_APPLE_TIMER, 5000, NULL);
}


void CSnakeGameDlg::OnBnClickedExit()
{
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game 종료 시작", __LINE__);

	KillTimer(SNAKE_GAME_TIMER);
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game 타이머 종료", __LINE__);

	CDialogEx::OnCancel();
}


void CSnakeGameDlg::OnBnClickedBtnRestart()
{
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game 재시작", __LINE__);
	KillTimer(SNAKE_GAME_TIMER);
	KillTimer(SNAKE_GAME_MAKE_APPLE_TIMER);
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game 타이머 종료", __LINE__);
	if (pSnakeGame)
		delete pSnakeGame;
	pSnakeGame = NULL;

	SetTimer(SNAKE_GAME_TIMER, 1000, NULL); // timer 
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game 타이머 생성", __LINE__);

	
#ifdef _DEBUG
	pSnakeGame = new SnakeGame(&m_listmsg);
#else
	pSnakeGame = new SnakeGame();
#endif

}


void CSnakeGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect r;
	m_Map.GetWindowRect(r);
	ScreenToClient(r);
	CPen BGPen(PS_NULL, 1, RGB(255, 0, 0));
	CBrush BGBrush(RGB(185, 122, 87));

	dc.SelectObject(&BGPen);
	dc.SelectObject(&BGBrush);
	dc.Rectangle(r);

	int nLEFT = r.left+4;
	int nTOP = r.top+4;

	int nSize = (r.right - r.left)/10;
	CBrush SnakeBrush(RGB(200,191,231));
	dc.SelectObject(&SnakeBrush);

	int nTmp = 0;
	for (int i = 0; i < 10; i++)
	{
		dc.Ellipse(nLEFT + nTmp, nTOP, nLEFT + (nSize*(i + 1)), nTOP + nSize);
		nTmp += nSize;
	}

#if 0
	// 레스터 오퍼레이션을 R2_XORPEN으로 설정
	dc.SetROP2(R2_XORPEN);
	dc.SelectStockObject(GRAY_BRUSH);
	dc.Ellipse(r);
#endif
}
