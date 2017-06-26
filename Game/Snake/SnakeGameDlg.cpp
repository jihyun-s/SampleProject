// SnakeGameDlg.cpp : 구현 파일입니다.
//

#include "../stdafx.h"
#include "../Game.h"
#include "SnakeGameDlg.h"
#include "afxdialogex.h"
#include "../utils.h"

#define HEEYA_DEBUG
#ifdef HEEYA_DEBUG
#include "Snake.h"
#include "Apple.h"
#include "Map.h"
#include "COMMON_TYPES.h"
#endif //HEEYA_DEBUG

// CSnakeGameDlg 대화 상자입니다.

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
END_MESSAGE_MAP()


// CSnakeGameDlg 메시지 처리기입니다.
BOOL CSnakeGameDlg::OnInitDialog()
{	
	CDialogEx::OnInitDialog();
#ifdef _DEBUG
	m_listmsg.ShowWindow(SW_SHOW);

	TraceListbox(&m_listmsg, L"[%d]Snake Dialog 생성", __LINE__);
#else
	CRect r;
	m_listmsg.GetWindowRect(&r);
	int listbottom = r.bottom - r.top;
	this->GetWindowRect(&r);
	this->SetWindowPos(NULL, r.left, r.top, r.right-r.left, (r.bottom - r.top) - listbottom, 0);
#endif

#if 0//def HEEYA_DEBUG
	Snake cSnake;
	Direction D = cSnake.GetDir();
	int nSize = cSnake.GetSize();
	cSnake.SetDir(DOWN);
	D = cSnake.GetDir();

	cSnake.MoveSnake(1, 1);
	cSnake.MoveSnake(1, 2);
	cSnake.MoveSnake(2, 2);
	cSnake.MoveSnake(2, 1);
	cSnake.MoveSnake(1, 1);

	bool bSelfKill = cSnake.SnakeSelfKill();
	nSize = cSnake.GetSize();
#endif //HEEYA_DEBUG

#if 0//def HEEYA_DEBUG
	Apple cRed(RED);
	Apple cGreen(GREEN);

	int nSize = cRed.GetSize();
	APPLE_CLR c = cRed.GetColor();
	c = cGreen.GetColor();
	Point pTEST = cRed.MakeApplePosition(10);
	cRed.MakeApple(pTEST.x, pTEST.y);
	nSize = cRed.GetSize();
	pTEST = cRed.MakeApplePosition(10);
	cRed.MakeApple(pTEST.x, pTEST.y);
	nSize = cRed.GetSize();
	pTEST = cRed.MakeApplePosition(10);
	cRed.MakeApple(pTEST.x, pTEST.y);
	cRed.DeleteApple(5, 5);

#endif //HEEYA_DEBUG

#if 0//def HEEYA_DEBUG
	Map cMap(10, 10);
	cMap.MakeRandomApple(3);
	bool bExistApple = cMap.ExistApple(2, 2);
	if (bExistApple)
		cMap.DeleteApple(2, 2);
#endif //HEEYA_DEBUG

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSnakeGameDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
