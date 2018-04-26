// CAppDev.cpp: 实现文件
//

#include "stdafx.h"
#include "RFID.h"
#include "CAppDev.h"
#include "afxdialogex.h"
#include "ZM124U.h"
#include "Hit.h"
#include<iostream>
#include <string>
#include <algorithm>

#define SEN 0
#define BLK 0

// CAppDev 对话框

IMPLEMENT_DYNAMIC(CAppDev, CDialog)

CAppDev::CAppDev(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CAppDev, pParent)
{
	key_type = 0;
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

	DDX_Control(pDX, IDC_RADIO_KEYA, m_rba);
	DDX_Control(pDX, IDC_RADIO_KEYB, m_rbb);
	DDX_Control(pDX, IDC_EDIT_KEY, m_e_key);
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
	if (m_rba.GetCheck())key_type = 0x0A;
	if (m_rbb.GetCheck())key_type = 0x0B;
	if(!key_type) {
		m_e_money_s.SetWindowText(_T("请选择密钥类型"));
		return;
	}
	if (m_e_key.GetWindowTextLength() == 0) {
		m_e_money_s.SetWindowText(_T("请输入密钥"));
		return;
	}
	if (m_e_key.GetWindowTextLength() != 12) {
		m_e_money_s.SetWindowText(_T("密钥长度不匹配"));
		return;
	}
	CString key;
	m_e_key.GetWindowText(key);
	std::string keys = CStringA(key);
	transform(keys.begin(), keys.end(), keys.begin(), toupper);
	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (keys[i * 2] >= 'A' ? (keys[i * 2] - 'A' + 10) : (keys[i * 2] - '0')) * 16 + (keys[i * 2 + 1] >= 'A' ? (keys[i * 2 + 1] - 'A' + 10) : (keys[i * 2 + 1] - '0'));


	LONG money;
	int status = 0 - read_account(SEN,BLK,key_type,keyc,&money);
	if (status) {
		CString hits(error_hit[status].c_str());
		m_e_money_s.SetWindowText(hits);
		return;
	}
	else {
		CString Money;
		Money.Format(_T("%ld"),money);
		m_e_money.SetWindowText(Money);
	}
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
