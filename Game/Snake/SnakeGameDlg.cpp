// SnakeGameDlg.cpp : 구현 파일입니다.
//
#include "../stdafx.h"
#include "../Game.h"
#include "SnakeGameDlg.h"
#include "afxdialogex.h"
#include <gdiplus.h>
using namespace Gdiplus;

// CSnakeGameDlg 대화 상자입니다.
#define SNAKE_GAME_TIMER 9999
#define SNAKE_GAME_MAKE_APPLE_TIMER 9998

#define SNAKE_GAME_MOVE_PERIOD 1000
#define SNAKE_GAME_MAKE_APPLE_PERIOD 5500

IMPLEMENT_DYNAMIC(CSnakeGameDlg, CDialogEx)
ULONG_PTR           gdiplusToken;

CSnakeGameDlg::CSnakeGameDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CSnakeGameDlg::IDD, pParent)
{
	pSnakeGame = NULL;
	m_pSnakeGameResultDlg = NULL;
	m_bInit = FALSE;

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

CSnakeGameDlg::~CSnakeGameDlg()
{
	if (pSnakeGame)
		delete pSnakeGame;
	if (m_pSnakeGameResultDlg)
		delete m_pSnakeGameResultDlg;

	GdiplusShutdown(gdiplusToken);
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
	//DDX_Control(pDX, IDC_LIST_SNAKE, m_listmsg);
}


BEGIN_MESSAGE_MAP(CSnakeGameDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSnakeGameDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDD_BTN_START, &CSnakeGameDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDEXIT, &CSnakeGameDlg::OnBnClickedExit)
	ON_WM_PAINT()
//	ON_WM_ERASEBKGND()
ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CSnakeGameDlg 메시지 처리기입니다.
BOOL CSnakeGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
#ifdef _DEBUG
	GetDlgItem(IDC_LIST_SNAKE)->ShowWindow(SW_SHOW);
	SetDebugConsole(GetDlgItem(IDC_LIST_SNAKE));
#else
	CRect r;
	m_listmsg.GetWindowRect(&r);
	int listbottom = r.bottom - r.top;
	this->GetWindowRect(&r);
	this->SetWindowPos(NULL, r.left, r.top, r.right - r.left, (r.bottom - r.top) - listbottom, 0);
#endif
	TraceListbox(L"[%d][DLG] Snake Dialog 생성", __LINE__);

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
/*
#ifdef _DEBUG
	pSnakeGame = new SnakeGame(this, GetDlgItem(IDC_LIST_SNAKE));
#else
	pSnakeGame = new SnakeGame(this);
#endif*/
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
		TraceListbox(L"[%d][DLG] Snake 이동", __LINE__);
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
	CleanGameData();
	StartGame();
}

void CSnakeGameDlg::CleanGameData()
{
	TraceListbox(L"[%d][DLG] Snake Game 시작", __LINE__);
	TraceListbox(L"[%d][DLG] Snake Game 타이머 종료", __LINE__);
	KillTimer(SNAKE_GAME_TIMER);
	KillTimer(SNAKE_GAME_MAKE_APPLE_TIMER);

	if (pSnakeGame)
	{
		delete pSnakeGame;
		pSnakeGame = NULL;
	}
	m_bInit = FALSE;
}

void CSnakeGameDlg::StartGame()
{
#ifdef _DEBUG
	pSnakeGame = new SnakeGame(this, GetDlgItem(IDC_LIST_SNAKE));
#else
	pSnakeGame = new SnakeGame(this);
#endif
	Invalidate();

	// Snake game start
	SetTimer(SNAKE_GAME_TIMER, SNAKE_GAME_MOVE_PERIOD, NULL); // timer 
	TraceListbox(L"[%d][DLG] Snake Game 타이머 생성", __LINE__);
}

void CSnakeGameDlg::OnBnClickedExit()
{
	TraceListbox(L"[%d][DLG] Snake Game 종료 시작", __LINE__);

	KillTimer(SNAKE_GAME_TIMER);
	KillTimer(SNAKE_GAME_MAKE_APPLE_TIMER);
	TraceListbox(L"[%d][DLG] Snake Game 타이머 종료", __LINE__);

	CDialogEx::OnCancel();
}

void CSnakeGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CRect r;
	m_Map.GetWindowRect(r);
	ScreenToClient(r);

	Gdiplus::Graphics *graphics = new Gdiplus::Graphics(dc); // dc.GetSafeHdc());
	
	// 한번에 그리기 위한 buffer역할을 하는 bitmap을 생성한다.(깜빡임은 한번에 그리지 않고 여러번 그리기 때문에 발생함)
	Gdiplus::Bitmap bitmap(r.Width(), r.Height());
	Gdiplus::Graphics memDC(&bitmap);
	memDC.SetSmoothingMode(SmoothingModeAntiAlias);

	// 그리기 전 bitmap 바탕을 그려준다. (이 부분이 없으면 잔상이 남게 된다)
	Gdiplus::SolidBrush GDIBrush_BG(Color(185, 122, 87));
	memDC.FillRectangle(&GDIBrush_BG, 0, 0, r.Width(), r.Height());


	//잔디
	Gdiplus::SolidBrush GDIBrush_Grass(Color(0, 128, 0));
	Gdiplus::Point pGrass[7];
	pGrass[0] = Gdiplus::Point(0, 12);
	pGrass[1] = Gdiplus::Point(5, 0);
	pGrass[2] = Gdiplus::Point(10, 6);
	pGrass[3] = Gdiplus::Point(15, 0);
	pGrass[4] = Gdiplus::Point(20, 6);
	pGrass[5] = Gdiplus::Point(25, 0);
	pGrass[6] = Gdiplus::Point(30, 12);

	int nGrassPos = r.Width() / 5;
	Gdiplus::Point pGrassPos[7];
	pGrassPos[0] = Gdiplus::Point(nGrassPos, nGrassPos);
	pGrassPos[1] = Gdiplus::Point(nGrassPos * 4, nGrassPos);
	pGrassPos[2] = Gdiplus::Point(nGrassPos, nGrassPos * 4);
	pGrassPos[3] = Gdiplus::Point(nGrassPos * 3, nGrassPos * 4);
	pGrassPos[4] = Gdiplus::Point(nGrassPos * 4, nGrassPos * 2);
	pGrassPos[5] = Gdiplus::Point(nGrassPos, nGrassPos * 3);
	pGrassPos[6] = Gdiplus::Point(nGrassPos * 3, nGrassPos * 2);

	for (int i = 0; i < 7; i++)
	{
		Gdiplus::Point pNewGrass[7];
		for (int j = 0; j < 7; j++)
			pNewGrass[j] = pGrass[j] + pGrassPos[i];
		memDC.FillPolygon(&GDIBrush_Grass, pNewGrass, 7);
	}

	int nSize = (r.right - r.left) / 10;

	if (pSnakeGame)
	{
		// draw apple
		const vector<Apple>* pApple = pSnakeGame->GetMap()->GetApplePosition();
		vector<Apple>::const_iterator itr_apple = pApple->begin();
		for (itr_apple; itr_apple != pApple->end(); ++itr_apple)
		{
			const int nX = (*itr_apple).GetAppleX();
			const int nY = (*itr_apple).GetAppleY();
			const APPLE_CLR nColor = (*itr_apple).GetAppleColor();

			int nLeft = nX*nSize;
			int nTop = nY*nSize;
			int nRight = nX*nSize + nSize;
			int nBottom = nY*nSize + nSize;

			int nCenterX = nLeft + (nSize / 2);
			int nCenterY = nTop + (nSize / 2);

			int nSmallTop = nTop + (nSize / 4);
			int nSmallBottom = nBottom - (nSize / 4);

			Gdiplus::SolidBrush GDIBrush_REDAPPLE(Color(255, 0, 0));
			Gdiplus::SolidBrush GDIBrush_GREENAPPLE(Color(34, 177, 76));
			GraphicsPath* myGraphicsPath = new GraphicsPath();
			if (myGraphicsPath)
			{
				//clockwise
				myGraphicsPath->AddArc(nLeft, nTop, (nRight - nLeft), (nBottom - nTop), 0, 180);
				myGraphicsPath->AddArc(nLeft, nSmallTop, (nCenterX - nLeft), (nSmallBottom - nSmallTop), 180, 180);
				myGraphicsPath->AddArc(nCenterX, nSmallTop, (nRight - nCenterX), (nSmallBottom - nSmallTop), 180, 180); //sweepangle

				if (nColor == RED)
					memDC.FillPath(&GDIBrush_REDAPPLE, myGraphicsPath);
				else if (nColor == GREEN)
					memDC.FillPath(&GDIBrush_GREENAPPLE, myGraphicsPath);

				delete myGraphicsPath;
				myGraphicsPath = NULL;
			}

			Gdiplus::Pen GDIPen_AppleBranch(Color(128, 64, 0), 4);
			GDIPen_AppleBranch.SetLineCap(Gdiplus::LineCapRound, Gdiplus::LineCapRound, Gdiplus::DashCapRound);
			memDC.DrawLine(&GDIPen_AppleBranch, Gdiplus::Point(nCenterX, nCenterY), Gdiplus::Point(nCenterX + 5, nTop + 5));

			Gdiplus::SolidBrush GDIBrush_APPLESHINE(Color(255, 255, 255));
			memDC.FillEllipse(&GDIBrush_APPLESHINE, nLeft + 2, nCenterY - 4, 6, 8);

		}

		// draw snake
		const vector<pair<int, int>>* pSnake = pSnakeGame->GetSnake()->GetSnakePosition();
		vector<pair<int, int>>::const_reverse_iterator itr_snake = pSnake->rbegin();
		
		const Direction CurrentDir = pSnakeGame->GetSnake()->GetDir();
		double degrees = 0;
		if (CurrentDir == RIGHT)
			degrees = 90;
		if (CurrentDir == DOWN)
			degrees = 180;
		if (CurrentDir == LEFT)
			degrees = 270;

		if (itr_snake != pSnake->rend())
		{
			const pair<int, int> pSnakeHead = *itr_snake;

			// draw snake body 
			for (++itr_snake; itr_snake != pSnake->rend(); ++itr_snake)
			{
				const int nX = (*itr_snake).first;
				const int nY = (*itr_snake).second;

				int nLeft = nX*nSize;
				int nTop = nY*nSize;
				int nRight = nX*nSize + nSize;
				int nBottom = nY*nSize + nSize;
				int nBODYSIZE_X = nRight - nLeft;
				int nBODYSIZE_Y = nBottom - nTop;

				Gdiplus::SolidBrush GDIBrush_SnakeBody1(Color(0, 128, 128));
				Gdiplus::SolidBrush GDIBrush_SnakeBody2(Color(170, 197, 165));

				//dc.Ellipse(nLeft, nTop, nRight, nBottom);
				memDC.FillEllipse(&GDIBrush_SnakeBody1, nLeft, nTop, nBODYSIZE_X, nBODYSIZE_Y);
				memDC.FillEllipse(&GDIBrush_SnakeBody2, nLeft + 4, nTop + 4, nBODYSIZE_X - 8, nBODYSIZE_Y - 8);
				memDC.FillEllipse(&GDIBrush_SnakeBody1, nLeft + 7, nTop + 7, nBODYSIZE_X - 14, nBODYSIZE_Y - 14);


			}

			// draw snake head

			int nHLeft = (pSnakeHead).first*nSize;
			int nHTop = (pSnakeHead).second*nSize;
			int nHRight = (pSnakeHead).first*nSize + nSize;
			int nHBottom = (pSnakeHead).second*nSize + nSize;
			int nCenterX = nHLeft + (nSize / 2);
			int nCenterY = nHTop + (nSize / 2);

			Gdiplus::Matrix oldMatrix;
			memDC.GetTransform(&oldMatrix);

			Matrix NewMatrix;
			NewMatrix.RotateAt(degrees, Gdiplus::PointF(nCenterX, nCenterY));
			memDC.SetTransform(&NewMatrix);

			Gdiplus::Pen GDIPen_Tongue(Color(255, 128, 128), 2);
			Gdiplus::Pen GDIPen_EyeBrow(Color(0, 0, 0), 2);
			Gdiplus::Pen GDIPen_EyeDied(Color(0, 0, 0), 1.5);
			Gdiplus::SolidBrush GDIBrush_Head(Color(0, 128, 128));
			Gdiplus::SolidBrush GDIBrush_Eye1(Color(255, 255, 255));
			Gdiplus::SolidBrush GDIBrush_Eye2(Color(0, 0, 0));

			//혀
			Gdiplus::Point Lines[4];
			Lines[0].X = nCenterX + 3;	Lines[0].Y = nHTop + 3;
			Lines[1].X = nCenterX - 3;	Lines[1].Y = nHTop - 3;
			Lines[2].X = nCenterX + 3;	Lines[2].Y = nHTop - 5;
			Lines[3].X = nCenterX - 3;	Lines[3].Y = nHTop - 7;
			memDC.DrawLines(&GDIPen_Tongue, Lines, 4);

			//머리
			memDC.FillEllipse(&GDIBrush_Head, nHLeft, nHTop, (nHRight - nHLeft), (nHBottom - nHTop));
			
			//코
			CPoint LeftNosePoint(nCenterX - 2, nCenterY - (nSize / 3));
			CPoint RightNosePoint(nCenterX + 2, nCenterY - (nSize / 3));

			memDC.FillRectangle(&GDIBrush_Eye2, LeftNosePoint.x - 1, LeftNosePoint.y - 2, 2, 2);
			memDC.FillRectangle(&GDIBrush_Eye2, RightNosePoint.x - 1, RightNosePoint.y - 2, 2, 2);

			//눈s
			CPoint LeftEyePoint(nCenterX - (nSize / 4), nCenterY - (nSize / 4) + 2);
			CPoint RightEyePoint(nCenterX + (nSize / 4), nCenterY - (nSize / 4) + 2);

			// 눈동자 흰색
			memDC.FillEllipse(&GDIBrush_Eye1, LeftEyePoint.x - 5, LeftEyePoint.y - 5, 10, 10);
			memDC.FillEllipse(&GDIBrush_Eye1, RightEyePoint.x - 5, RightEyePoint.y - 5, 10, 10);

			if (pSnakeGame->IsSnakeGameOver()) // died : @_@
			{
				// 눈썹
				memDC.DrawLine(&GDIPen_EyeBrow, LeftEyePoint.x - 5, LeftEyePoint.y + 8, LeftEyePoint.x + 5, LeftEyePoint.y + 11);
				memDC.DrawLine(&GDIPen_EyeBrow, RightEyePoint.x - 5, RightEyePoint.y + 11, RightEyePoint.x + 5, RightEyePoint.y + 8);

				// 눈동자
				Gdiplus::GraphicsPath eyePath;
				
				eyePath.AddEllipse(LeftEyePoint.x - 1, LeftEyePoint.y - 1, 2, 2);
				eyePath.AddEllipse(LeftEyePoint.x - 3, LeftEyePoint.y - 3, 6, 6);
				eyePath.AddEllipse(LeftEyePoint.x-5, LeftEyePoint.y-5, 10, 10);

				eyePath.AddEllipse(RightEyePoint.x - 1, RightEyePoint.y - 1, 2, 2);
				eyePath.AddEllipse(RightEyePoint.x - 3, RightEyePoint.y - 3, 6, 6);
				eyePath.AddEllipse(RightEyePoint.x - 5, RightEyePoint.y - 5, 10, 10);

				memDC.DrawPath(&GDIPen_EyeDied, &eyePath);
			}
			else // alive
			{
				// 눈썹
				memDC.DrawLine(&GDIPen_EyeBrow, LeftEyePoint.x - 5, LeftEyePoint.y + 11, LeftEyePoint.x + 5, LeftEyePoint.y + 8);
				memDC.DrawLine(&GDIPen_EyeBrow, RightEyePoint.x - 5, RightEyePoint.y + 8, RightEyePoint.x + 5, RightEyePoint.y + 11);

				// 눈동자 검정색
				memDC.FillEllipse(&GDIBrush_Eye2, LeftEyePoint.x - 4, LeftEyePoint.y - 4, 8, 8);
				memDC.FillEllipse(&GDIBrush_Eye2, RightEyePoint.x - 4, RightEyePoint.y - 4, 8, 8);
			}
			memDC.SetTransform(&oldMatrix);
		}
	}

	// 완성된 bitmap은 한번에 화면에 그린다.
	graphics->DrawImage(&bitmap, r.left, r.top);

	if (pSnakeGame && pSnakeGame->IsSnakeGameOver())
	{
		//#21 게임 종료 시 뱀 폭발 렌더링
		Sleep(500);
		CImage image;
		CPngImage* boomImg = new CPngImage();
		boomImg->Load(IDB_BOOM);
		CBitmap bitmap;
		bitmap.Attach(boomImg->Detach());
		BITMAP bm;
		bitmap.GetObject(sizeof(BITMAP), &bm);

		CDC MemoryDC;
		MemoryDC.CreateCompatibleDC(&dc);
		MemoryDC.SelectObject(&bitmap);

		BLENDFUNCTION m_bf;
		m_bf.BlendOp = AC_SRC_OVER;
		m_bf.BlendFlags = 0;
		m_bf.SourceConstantAlpha = 255;
		m_bf.AlphaFormat = AC_SRC_ALPHA;
		AlphaBlend(dc, 30, 30, r.Width()-30, r.Height()-30, MemoryDC, 0, 0, bm.bmWidth, bm.bmHeight, m_bf);

		DeleteObject(bitmap);
		DeleteDC(MemoryDC);

		delete boomImg;

		ShowResultDialog();
	}


}

void CSnakeGameDlg::UpdateUI()
{
	CRect r;
	m_Map.GetWindowRect(r);
	ScreenToClient(&r);
	InvalidateRect(&r);
}

void CSnakeGameDlg::UpdateScore(int a_nScore)
{
	SetDlgItemInt(IDC_EDIT1, a_nScore);
}

BOOL CSnakeGameDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bInit)	// 최초 한 번만 배경 그리기
		return FALSE;

	return __super::OnEraseBkgnd(pDC);
}

void CSnakeGameDlg::ShowResultDialog()
{
	if (!m_pSnakeGameResultDlg)
		m_pSnakeGameResultDlg = new CSnakeGameResultDlg(this);
	
	assert(m_pSnakeGameResultDlg);

	if (m_pSnakeGameResultDlg)
	{
		m_pSnakeGameResultDlg->SetScore(GetDlgItemInt(IDC_EDIT1));

		if (IDOK == m_pSnakeGameResultDlg->DoModal()) {

			if (m_pSnakeGameResultDlg->IsRestartGame())
			{
				CleanGameData();
				StartGame();
			}
		}
	}
}