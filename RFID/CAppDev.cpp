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
	DDX_Control(pDX, IDC_EDIT_MONEY,m_e_money);
	DDX_Control(pDX, IDC_EDIT_ADD_MONEY, m_e_money_add);
	DDX_Control(pDX, IDC_EDIT_SUB_MONEY, m_e_money_sub);
	DDX_Control(pDX, IDC_EDIT_MONEY_S, m_e_money_s);
	DDX_Control(pDX, IDC_BUTTON_INIT, m_b_money_init);
	DDX_Control(pDX, IDC_BUTTON_MONEY, m_b_money_q);
	DDX_Control(pDX, IDC_BUTTON_ADD_MONEY, m_b_money_add);
	DDX_Control(pDX, IDC_BUTTON_SUB_MONEY, m_b_money_sub);
}


BEGIN_MESSAGE_MAP(CAppDev, CDialog)
	ON_EN_CHANGE(IDC_EDIT2, &CAppDev::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CAppDev::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_MONEY, &CAppDev::OnBnClickedButtonMoney)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MONEY, &CAppDev::OnBnClickedButtonAddMoney)
	ON_BN_CLICKED(IDC_BUTTON_SUB_MONEY, &CAppDev::OnBnClickedButtonSubMoney)
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


void CAppDev::OnBnClickedButtonInit()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CAppDev::OnBnClickedButtonMoney()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CAppDev::OnBnClickedButtonAddMoney()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CAppDev::OnBnClickedButtonSubMoney()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CAppDev::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ( m_e_money_add.GetFocus()
		|| m_e_money_sub.GetFocus()) {
		short nks = GetKeyState(VK_CONTROL);
		if (nks & 0x8000) {
			return CDialog::PreTranslateMessage(pMsg);
		}

		//检查输入的内容
		if ((pMsg->wParam >= 0x30 && pMsg->wParam <= 0x39)) {
			return CDialog::PreTranslateMessage(pMsg);
		}
		else {
			MessageBeep(-1);
			pMsg->wParam = NULL;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
