// SnakeGameDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "SnakeGameDlg.h"
#include "afxdialogex.h"


// CSnakeGameDlg ��ȭ �����Դϴ�.

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


// CSnakeGameDlg �޽��� ó�����Դϴ�.
