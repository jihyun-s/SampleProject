// SnakeGameDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "../Game.h"
#include "SnakeGameDlg.h"
#include "afxdialogex.h"


// CSnakeGameDlg ��ȭ �����Դϴ�.

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
}


BEGIN_MESSAGE_MAP(CSnakeGameDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSnakeGameDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSnakeGameDlg �޽��� ó�����Դϴ�.


void CSnakeGameDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}
