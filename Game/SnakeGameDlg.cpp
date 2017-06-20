// SnakeGameDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Game.h"
#include "SnakeGameDlg.h"
#include "afxdialogex.h"


// CSnakeGameDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSnakeGameDlg, CDialogEx)

CSnakeGameDlg::CSnakeGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_SNAKE, pParent)
{
	//[2017.06.20][kysha91]Test
}

CSnakeGameDlg::~CSnakeGameDlg()
{
}

void CSnakeGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSnakeGameDlg, CDialogEx)
END_MESSAGE_MAP()


// CSnakeGameDlg 메시지 처리기입니다.
