// SnakeGameDlg.cpp : 구현 파일입니다.
//
#include "../stdafx.h"
#include "../Game.h"
#include "SnakeGameDlg.h"
#include "afxdialogex.h"
#include <gdiplus.h>
using namespace Gdiplus;

//#define NOT_USE_GDIPLUS

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
	m_bInit = FALSE;

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

CSnakeGameDlg::~CSnakeGameDlg()
{
	if (pSnakeGame)
		delete pSnakeGame;

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
	TraceListbox(L"[%d][DLG] Snake Game 시작", __LINE__);
	TraceListbox(L"[%d][DLG] Snake Game 타이머 종료", __LINE__);
	KillTimer(SNAKE_GAME_TIMER);
	KillTimer(SNAKE_GAME_MAKE_APPLE_TIMER);

	if (pSnakeGame)
	{
		delete pSnakeGame;
		pSnakeGame = NULL;
	}
	
#ifdef _DEBUG
	pSnakeGame = new SnakeGame(this, GetDlgItem(IDC_LIST_SNAKE));
#else
	pSnakeGame = new SnakeGame(this);
#endif
	Invalidate();

	// Snake game start
	m_bInit = FALSE;
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

	CPen BGPen(PS_NULL, 1, RGB(255, 0, 0));
	CBrush BGBrush(RGB(185, 122, 87));

	dc.SelectObject(&BGPen);
	dc.SelectObject(&BGBrush);
	dc.Rectangle(r);

	int nSize = (r.right - r.left) / 10;

#ifndef NOT_USE_GDIPLUS
	Gdiplus::Graphics *graphics = new Graphics(dc); // dc.GetSafeHdc());
	graphics->SetSmoothingMode(SmoothingModeAntiAlias);
#endif //NOT_USE_GDIPLUS

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

			int nLeft = r.left + nX*nSize;
			int nTop = r.top + nY*nSize;
			int nRight = r.left + nX*nSize + nSize;
			int nBottom = r.top + nY*nSize + nSize;

			int nCenterX = nLeft + (nSize / 2);
			int nCenterY = nTop + (nSize / 2);

			int nSmallTop = nTop + (nSize / 4);
			int nSmallBottom = nBottom - (nSize / 4);

#ifdef NOT_USE_GDIPLUS

			CBrush RedAppleBrush(RGB(255, 0, 0));
			CBrush GreenAppleBrush(RGB(34, 177, 76));
			CPen AppleBranch(PS_SOLID, 4, RGB(128, 64, 0));

			if (nColor == RED)
				dc.SelectObject(&RedAppleBrush);
			else if (nColor == GREEN)
				dc.SelectObject(&GreenAppleBrush);

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

#else

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
					graphics->FillPath(&GDIBrush_REDAPPLE, myGraphicsPath);
				else if (nColor == GREEN)
					graphics->FillPath(&GDIBrush_GREENAPPLE, myGraphicsPath);

				delete myGraphicsPath;
				myGraphicsPath = NULL;
			}

			Gdiplus::Pen GDIPen_AppleBranch(Color(128, 64, 0), 4);
			GDIPen_AppleBranch.SetLineCap(Gdiplus::LineCapRound, Gdiplus::LineCapRound, Gdiplus::DashCapRound);
			graphics->DrawLine(&GDIPen_AppleBranch, Gdiplus::Point(nCenterX, nCenterY), Gdiplus::Point(nCenterX + 5, nTop + 5));

			Gdiplus::SolidBrush GDIBrush_APPLESHINE(Color(255, 255, 255));
			graphics->FillEllipse(&GDIBrush_APPLESHINE, nLeft + 2, nCenterY - 4, 6, 8);

#endif //NOT_USE_GDIPLUS
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

		// draw snake head
		if (itr_snake != pSnake->rend())
		{

			int nHLeft = r.left + (*itr_snake).first*nSize;
			int nHTop = r.top + (*itr_snake).second*nSize;
			int nHRight = r.left + (*itr_snake).first*nSize + nSize;
			int nHBottom = r.top + (*itr_snake).second*nSize + nSize;
			int nCenterX = nHLeft + (nSize / 2);
			int nCenterY = nHTop + (nSize / 2);

#ifdef NOT_USE_GDIPLUS
			XFORM xOldForm, xNewForm;
			dc.GetWorldTransform(&xOldForm);
			SetGraphicsMode(dc, GM_ADVANCED);
			double radian = (double)degrees / 180. * 3.1415926;
			xNewForm.eM11 = (float)cos(radian);
			xNewForm.eM12 = (float)sin(radian);
			xNewForm.eM21 = (float)-sin(radian);
			xNewForm.eM22 = (float)cos(radian);
			xNewForm.eDx = (float)(nCenterX - cos(radian)*nCenterX + sin(radian)*nCenterY);
			xNewForm.eDy = (float)(nCenterY - cos(radian)*nCenterY - sin(radian)*nCenterX);
			SetWorldTransform(dc, &xNewForm);

			CPen SnakeTongue(PS_SOLID, 2, RGB(255, 128, 128));
			CBrush SnakeHeadBrush(RGB(0, 128, 128));
			CBrush SnakeEye(RGB(0, 0, 0));
			CBrush SnakeEye2(RGB(255, 255, 255));
			CPen EyeBrow(PS_SOLID, 2, RGB(0, 0, 0));

			//혀
			dc.SelectObject(&SnakeTongue);
			dc.MoveTo(nCenterX + 3, nHTop + 3);
			dc.LineTo(nCenterX - 3, nHTop - 3);
			dc.LineTo(nCenterX + 3, nHTop - 5);
			dc.LineTo(nCenterX - 3, nHTop - 7);
			dc.SelectObject(&BGPen);

			//머리
			dc.SelectObject(&SnakeHeadBrush);
			dc.Ellipse(nHLeft, nHTop, nHRight, nHBottom);

			//눈s
			CPoint LeftEyePoint(nCenterX - (nSize / 4), nCenterY - (nSize / 4) + 2);
			CPoint RightEyePoint(nCenterX + (nSize / 4), nCenterY - (nSize / 4) + 2);

			dc.SelectObject(&EyeBrow);
			dc.MoveTo(LeftEyePoint.x - 5, LeftEyePoint.y + 11);
			dc.LineTo(LeftEyePoint.x + 5, LeftEyePoint.y + 8);
			dc.MoveTo(RightEyePoint.x - 5, RightEyePoint.y + 8);
			dc.LineTo(RightEyePoint.x + 5, RightEyePoint.y + 11);
			dc.SelectObject(&BGPen);

			dc.SelectObject(&SnakeEye2);
			dc.Ellipse(LeftEyePoint.x - 5, LeftEyePoint.y - 5, LeftEyePoint.x + 5, LeftEyePoint.y + 5);
			dc.Ellipse(RightEyePoint.x - 5, RightEyePoint.y - 5, RightEyePoint.x + 5, RightEyePoint.y + 5);

			dc.SelectObject(&SnakeEye);
			dc.Ellipse(LeftEyePoint.x - 4, LeftEyePoint.y - 4, LeftEyePoint.x + 4, LeftEyePoint.y + 4);
			dc.Ellipse(RightEyePoint.x - 4, RightEyePoint.y - 4, RightEyePoint.x + 4, RightEyePoint.y + 4);

			//코
			CPoint LeftNosePoint(nCenterX - 2, nCenterY - (nSize / 3));
			CPoint RightNosePoint(nCenterX + 2, nCenterY - (nSize / 3));
			dc.Rectangle(LeftNosePoint.x - 1, LeftNosePoint.y - 1, LeftNosePoint.x + 1, LeftNosePoint.y + 1);
			dc.Rectangle(RightNosePoint.x - 1, RightNosePoint.y - 1, RightNosePoint.x + 1, RightNosePoint.y + 1);

			dc.SelectObject(&BGBrush);
			SetWorldTransform(dc, &xOldForm);
			SetGraphicsMode(dc, GM_COMPATIBLE);
#else

			Gdiplus::Matrix oldMatrix;
			graphics->GetTransform(&oldMatrix);

			Matrix NewMatrix;
			NewMatrix.RotateAt(degrees, Gdiplus::PointF(nCenterX, nCenterY));
			graphics->SetTransform(&NewMatrix);

			Gdiplus::Pen GDIPen_Tongue(Color(255, 128, 128), 2);
			Gdiplus::Pen GDIPen_EyeBrow(Color(0, 0, 0), 2);
			Gdiplus::SolidBrush GDIBrush_Head(Color(0, 128, 128));
			Gdiplus::SolidBrush GDIBrush_Eye1(Color(255, 255, 255));
			Gdiplus::SolidBrush GDIBrush_Eye2(Color(0, 0, 0));

			//혀
			Gdiplus::Point Lines[4];
			Lines[0].X = nCenterX + 3;	Lines[0].Y = nHTop + 3;
			Lines[1].X = nCenterX - 3;	Lines[1].Y = nHTop - 3;
			Lines[2].X = nCenterX + 3;	Lines[2].Y = nHTop - 5;
			Lines[3].X = nCenterX - 3;	Lines[3].Y = nHTop - 7;
			graphics->DrawLines(&GDIPen_Tongue, Lines, 4);

			//머리
			graphics->FillEllipse(&GDIBrush_Head, nHLeft, nHTop, (nHRight - nHLeft), (nHBottom - nHTop));

			//눈s
			CPoint LeftEyePoint(nCenterX - (nSize / 4), nCenterY - (nSize / 4) + 2);
			CPoint RightEyePoint(nCenterX + (nSize / 4), nCenterY - (nSize / 4) + 2);

			graphics->DrawLine(&GDIPen_EyeBrow, LeftEyePoint.x - 5, LeftEyePoint.y + 11, LeftEyePoint.x + 5, LeftEyePoint.y + 8);
			graphics->DrawLine(&GDIPen_EyeBrow, RightEyePoint.x - 5, RightEyePoint.y + 8, RightEyePoint.x + 5, RightEyePoint.y + 11);

			graphics->FillEllipse(&GDIBrush_Eye1, LeftEyePoint.x - 5, LeftEyePoint.y - 5, 10, 10);
			graphics->FillEllipse(&GDIBrush_Eye1, RightEyePoint.x - 5, RightEyePoint.y - 5, 10, 10);

			graphics->FillEllipse(&GDIBrush_Eye2, LeftEyePoint.x - 4, LeftEyePoint.y - 4, 8, 8);
			graphics->FillEllipse(&GDIBrush_Eye2, RightEyePoint.x - 4, RightEyePoint.y - 4, 8, 8);

			//코
			CPoint LeftNosePoint(nCenterX - 2, nCenterY - (nSize / 3));
			CPoint RightNosePoint(nCenterX + 2, nCenterY - (nSize / 3));

			graphics->FillRectangle(&GDIBrush_Eye2, LeftNosePoint.x - 1, LeftNosePoint.y - 1, 2, 2);
			graphics->FillRectangle(&GDIBrush_Eye2, RightNosePoint.x - 1, RightNosePoint.y - 1, 2, 2);

			graphics->SetTransform(&oldMatrix);
#endif//NOT_USE_GDIPLUS


			// draw snake body 
			for (++itr_snake; itr_snake != pSnake->rend(); ++itr_snake)
			{
				const int nX = (*itr_snake).first;
				const int nY = (*itr_snake).second;

				int nLeft = r.left + nX*nSize;// -4;
				int nTop = r.top + nY*nSize;// -4;
				int nRight = r.left + nX*nSize + nSize;// +4;
				int nBottom = r.top + nY*nSize + nSize;// +4;
				int nBODYSIZE_X = nRight - nLeft;
				int nBODYSIZE_Y = nBottom - nTop;

#ifdef NOT_USE_GDIPLUS
				CBrush SnakeBrush(RGB(0, 128, 128));
				CBrush SnakeBrush2(RGB(170, 197, 165));

				dc.SelectObject(&SnakeBrush);
				dc.Ellipse(nLeft, nTop, nRight, nBottom);
				dc.SelectObject(&SnakeBrush2);
				dc.Ellipse(nLeft + 4, nTop + 4, nRight - 4, nBottom - 4);
				dc.SelectObject(&SnakeBrush);
				dc.Ellipse(nLeft + 7, nTop + 7, nRight - 7, nBottom - 7);
				dc.SelectObject(&BGBrush);
#else
				Gdiplus::SolidBrush GDIBrush_SnakeBody1(Color(0, 128, 128));
				Gdiplus::SolidBrush GDIBrush_SnakeBody2(Color(170, 197, 165));

				dc.Ellipse(nLeft, nTop, nRight, nBottom);
				graphics->FillEllipse(&GDIBrush_SnakeBody1, nLeft, nTop, nBODYSIZE_X, nBODYSIZE_Y);
				graphics->FillEllipse(&GDIBrush_SnakeBody2, nLeft + 4, nTop + 4, nBODYSIZE_X - 8, nBODYSIZE_Y - 8);
				graphics->FillEllipse(&GDIBrush_SnakeBody1, nLeft + 7, nTop + 7, nBODYSIZE_X - 14, nBODYSIZE_Y - 14);

#endif//NOT_USE_GDIPLUS

			}
		}
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