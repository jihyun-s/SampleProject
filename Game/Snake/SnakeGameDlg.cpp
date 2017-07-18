// SnakeGameDlg.cpp : ���� �����Դϴ�.
//

#include "../stdafx.h"
#include "../Game.h"
#include "SnakeGameDlg.h"
#include "afxdialogex.h"
#include "../utils.h"

// CSnakeGameDlg ��ȭ �����Դϴ�.
#define SNAKE_GAME_TIMER 9999
#define SNAKE_GAME_MAKE_APPLE_TIMER 9998

#define SNAKE_GAME_MOVE_PERIOD 1000
#define SNAKE_GAME_MAKE_APPLE_PERIOD 5500

IMPLEMENT_DYNAMIC(CSnakeGameDlg, CDialogEx)

CSnakeGameDlg::CSnakeGameDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CSnakeGameDlg::IDD, pParent)
{
	pSnakeGame = NULL;
	m_bInit = FALSE;
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
	this->SetWindowPos(NULL, r.left, r.top, r.right - r.left, (r.bottom - r.top) - listbottom, 0);
#endif
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Dialog ����", __LINE__);

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
	pSnakeGame = new SnakeGame(this, &m_listmsg);
#else
	pSnakeGame = new SnakeGame(this);
#endif
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CSnakeGameDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}
CRect r;
void CSnakeGameDlg::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case SNAKE_GAME_TIMER:
	{
		TraceListbox(&m_listmsg, L"[%d][DLG] Snake �̵�", __LINE__);
		if (!m_bInit)
		{
			m_bInit = TRUE;
			SetTimer(SNAKE_GAME_MAKE_APPLE_TIMER, SNAKE_GAME_MAKE_APPLE_PERIOD, NULL);
		}

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
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game ����", __LINE__);

	// Snake game start
	SetTimer(SNAKE_GAME_TIMER, SNAKE_GAME_MOVE_PERIOD, NULL); // timer 
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game Ÿ�̸� ����", __LINE__);
}


void CSnakeGameDlg::OnBnClickedExit()
{
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game ���� ����", __LINE__);

	KillTimer(SNAKE_GAME_TIMER);
	KillTimer(SNAKE_GAME_MAKE_APPLE_TIMER);
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game Ÿ�̸� ����", __LINE__);

	CDialogEx::OnCancel();
}


void CSnakeGameDlg::OnBnClickedBtnRestart()
{
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game �����", __LINE__);
	KillTimer(SNAKE_GAME_TIMER);
	KillTimer(SNAKE_GAME_MAKE_APPLE_TIMER);
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game Ÿ�̸� ����", __LINE__);
	if (pSnakeGame)
		delete pSnakeGame;
	pSnakeGame = NULL;
	
#ifdef _DEBUG
	pSnakeGame = new SnakeGame(this, &m_listmsg);
#else
	pSnakeGame = new SnakeGame(this);
#endif

	SetTimer(SNAKE_GAME_TIMER, SNAKE_GAME_MOVE_PERIOD, NULL); // timer 
	TraceListbox(&m_listmsg, L"[%d][DLG] Snake Game Ÿ�̸� ����", __LINE__);
}


void CSnakeGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

	CRect r;
	m_Map.GetWindowRect(r);
	ScreenToClient(r);

	CPen BGPen(PS_NULL, 1, RGB(255, 0, 0));
	CBrush BGBrush(RGB(185, 122, 87));

	dc.SelectObject(&BGPen);
	dc.SelectObject(&BGBrush);
	dc.Rectangle(r);

	int nSize = (r.right - r.left) / 10;

	// draw apple
	CBrush RedAppleBrush(RGB(255, 0, 0));
	CBrush GreenAppleBrush(RGB(34, 177, 76));
	CPen AppleBranch(PS_SOLID, 4, RGB(128, 64, 0));
	
	const vector<Apple>* pApple = pSnakeGame->GetMap()->GetApplePosition();
	vector<Apple>::const_iterator itr_apple = pApple->begin();
	for (itr_apple; itr_apple != pApple->end(); ++itr_apple)
	{
		const int nX = (*itr_apple).GetAppleX();
		const int nY = (*itr_apple).GetAppleY();
		const APPLE_CLR nColor = (*itr_apple).GetAppleColor();

		if (nColor == RED)
			dc.SelectObject(&RedAppleBrush);
		else if (nColor == GREEN)
			dc.SelectObject(&GreenAppleBrush);
		
		int nLeft = r.left + nX*nSize;
		int nTop = r.top + nY*nSize;
		int nRight = r.left + nX*nSize + nSize;
		int nBottom = r.top + nY*nSize + nSize;

		int nCenterX = nLeft + (nSize / 2);
		int nCenterY = nTop + (nSize / 2);

		int nSmallTop = nTop + (nSize / 4);
		int nSmallBottom = nBottom - (nSize / 4);

		dc.BeginPath();
		dc.MoveTo(nLeft, nCenterY);
		dc.ArcTo(nLeft, nTop, nRight, nBottom, nLeft, nCenterY, nRight, nCenterY); //countclockwise
		dc.ArcTo(nCenterX, nSmallTop, nRight, nSmallBottom, nRight, nCenterY, nCenterX, nCenterY); //countclockwise
		dc.ArcTo(nLeft, nSmallTop, nCenterX, nSmallBottom, nCenterX, nCenterY, nLeft, nCenterY); //countclockwise
		dc.EndPath();
		dc.FillPath();

		dc.SelectObject(&AppleBranch);
		dc.MoveTo(nCenterX, nCenterY);
		dc.LineTo(nCenterX + 5, nTop + 5);
		dc.SelectObject(&BGPen);

		CBrush TempBrush(RGB(255, 255, 255));
		dc.SelectObject(&TempBrush);
		dc.Ellipse(nLeft + 2, nCenterY - 4, nLeft + 8, nCenterY + 4);

	}

	// draw snake
	const vector<pair<int, int>>* pSnake = pSnakeGame->GetSnake()->GetSnakePosition();
	vector<pair<int,int>>::const_reverse_iterator itr_snake = pSnake->rbegin();
	
	// draw snake head
	if (itr_snake != pSnake->rend())
	{
		CBrush SnakeHeadBrush(RGB(0, 191, 231));
		dc.SelectObject(&SnakeHeadBrush);
		dc.Ellipse(r.left + (*itr_snake).first*nSize, r.top + (*itr_snake).second*nSize, r.left + (*itr_snake).first*nSize + nSize, r.top + (*itr_snake).second*nSize + nSize);
	
		// draw snake body 
		CBrush SnakeBrush(RGB(200, 191, 231));
		dc.SelectObject(&SnakeBrush);
		for (++itr_snake; itr_snake != pSnake->rend(); ++itr_snake)
		{
			const int nX = (*itr_snake).first;
			const int nY = (*itr_snake).second;

			dc.Ellipse(r.left + nX*nSize, r.top + nY*nSize, r.left + nX*nSize + nSize, r.top + nY*nSize + nSize);
		}
	}
	
#if 0
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
#endif

#if 0
	// ������ ���۷��̼��� R2_XORPEN���� ����
	dc.SetROP2(R2_XORPEN);
	dc.SelectStockObject(GRAY_BRUSH);
	dc.Ellipse(r);
#endif
}

void CSnakeGameDlg::Update()
{
	CRect r;
	m_Map.GetWindowRect(r);
	ScreenToClient(&r);
	InvalidateRect(&r);
}