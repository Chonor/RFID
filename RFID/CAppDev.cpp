// CAppDev.cpp: 实现文件
//

#include "stdafx.h"
#include "RFID.h"
#include "CAppDev.h"
#include "afxdialogex.h"


// CAppDev 对话框

IMPLEMENT_DYNAMIC(CAppDev, CDialog)

CAppDev::CAppDev(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CAppDev, pParent)
{

}

CAppDev::~CAppDev()
{
}

void CAppDev::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAppDev, CDialog)
	ON_EN_CHANGE(IDC_EDIT2, &CAppDev::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CAppDev 消息处理程序


void CAppDev::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
