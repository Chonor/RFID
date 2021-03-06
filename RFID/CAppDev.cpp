// CAppDev.cpp: 实现文件
//
#pragma once
#include "stdafx.h"
#include "RFID.h"
#include "CAppDev.h"
#include "CDebugger.h"
#include "afxdialogex.h"





// CAppDev 对话框

IMPLEMENT_DYNAMIC(CAppDev, CDialog)

CAppDev::CAppDev(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CAppDev, pParent)
{
	key_type = 0;
	error_hit[0] = "IFD_OK 执行成功";
	error_hit[1] = "IFD_ICC_TypeError 卡片类型不对";
	error_hit[2] = "IFD_ICC_NoExist 无卡";
	error_hit[3] = "IFD_ICC_NoPower 有卡未上电";
	error_hit[4] = "IFD_ICC_NoResponse 卡片无应答";
	error_hit[5] = "IFD_ICC_BCCError BCC校验错误";
	error_hit[6] = "IFD_ICC_TimeOut 接收超时";
	error_hit[7] = "IFD_ICC_RunFail 执行失败";
	error_hit[8] = "IFD_ICC_SiteFail 卡片位置错误";
	error_hit[9] = "IFD_ICC_SetFail 设置失败";
	error_hit[10] = "IFD_NoSlot 无卡";
	error_hit[11] = "IFD_ConnectError 读卡器连接错";
	error_hit[12] = "IFD_UnConnected 未建立连接(没有执行打开设备函数)";
	error_hit[13] = "IFD_BadCommand (动态库)不支持该命令";
	error_hit[14] = "IFD_CheckSumError 信息校验和出错";
	error_hit[15] = "IFD_ICC_PowerFail 卡片上电失败";
	error_hit[16] = "IFD_ICC_ResetFail 卡片复位失败";
	error_hit[17] = "IFD_ICC_PowerOffFail 卡片下电失败";
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
	//this->key_type = pDBG->key_type;
	
	
	if(!key_type) {
		m_e_money_s.SetWindowText(_T("请选择密钥类型"));
		return;
	}
	if (keys.GetLength() == 0) {
		m_e_money_s.SetWindowText(_T("请输入密钥"));
		return;
	}
	if (keys.GetLength() != 12) {
		m_e_money_s.SetWindowText(_T("密钥长度不匹配"));
		return;
	}
	std::string key = CStringA(keys);
	transform(key.begin(), key.end(), key.begin(), toupper);
	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (key[i * 2] >= 'A' ? (key[i * 2] - 'A' + 10) : (key[i * 2] - '0')) * 16 + (key[i * 2 + 1] >= 'A' ? (key[i * 2 + 1] - 'A' + 10) : (key[i * 2 + 1] - '0'));


	LONG money;
	int status = 0 - read_account(sen,blk,key_type,keyc,&money);
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

	if (!key_type) {
		m_e_money_s.SetWindowText(_T("请选择密钥类型"));
		return;
		}
	if (keys.GetLength() == 0) {
		m_e_money_s.SetWindowText(_T("请输入密钥"));
		return;
	}
	if (keys.GetLength() != 12) {
		m_e_money_s.SetWindowText(_T("密钥长度不匹配"));
		return;
	}
	
	std::string key = CStringA(keys);
	transform(key.begin(), key.end(), key.begin(), toupper);
	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (key[i * 2] >= 'A' ? (key[i * 2] - 'A' + 10) : (key[i * 2] - '0')) * 16 + (key[i * 2 + 1] >= 'A' ? (key[i * 2 + 1] - 'A' + 10) : (key[i * 2 + 1] - '0'));

	LONG money;
	int status = 0 - read_account(sen, blk, key_type, keyc, &money);
	if (status) {
		CString hits(error_hit[status].c_str());
		m_e_money_s.SetWindowText(hits);

		return;
	}
	else {
		CString Money;
		Money.Format(_T("%ld"), money);
		m_e_money.SetWindowText(Money);
	}
}


void CAppDev::OnBnClickedButtonAddMoney()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!key_type) {
		m_e_money_s.SetWindowText(_T("请选择密钥类型"));
		return;
	}
	if (keys.GetLength() == 0) {
		m_e_money_s.SetWindowText(_T("请输入密钥"));
		return;
	}
	if (keys.GetLength() != 12) {
		m_e_money_s.SetWindowText(_T("密钥长度不匹配"));
		return;
	}

	std::string key = CStringA(keys);
	transform(key.begin(), key.end(), key.begin(), toupper);
	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (key[i * 2] >= 'A' ? (key[i * 2] - 'A' + 10) : (key[i * 2] - '0')) * 16 + (key[i * 2 + 1] >= 'A' ? (key[i * 2 + 1] - 'A' + 10) : (key[i * 2 + 1] - '0'));


	LONG money;
	int status = 0 - read_account(sen, blk, key_type, keyc, &money);
	if (status) {
		CString hits(error_hit[status].c_str());
		m_e_money_s.SetWindowText(hits);
		return;
	}
	else {
		CString Money;
		m_e_money_add.GetWindowText(Money);
		LONG tmp(_ttol(Money));
		money += tmp;
		status = 0 - write_account(sen, blk, key_type, keyc, money);
		if (status) {
			CString hits(error_hit[status].c_str());
			m_e_money_s.SetWindowText(hits);
			return;
		}
		else{
			m_e_money_s.SetWindowText(_T("充值成功"));
		}
	}
}


void CAppDev::OnBnClickedButtonSubMoney()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	if (!key_type) {
		m_e_money_s.SetWindowText(_T("请选择密钥类型"));
		return;
	}
	if (keys.GetLength() == 0) {
		m_e_money_s.SetWindowText(_T("请输入密钥"));
		return;
	}
	if (keys.GetLength() != 12) {
		m_e_money_s.SetWindowText(_T("密钥长度不匹配"));
		return;
	}

	std::string key = CStringA(keys);
	transform(key.begin(), key.end(), key.begin(), toupper);
	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (key[i * 2] >= 'A' ? (key[i * 2] - 'A' + 10) : (key[i * 2] - '0')) * 16 + (key[i * 2 + 1] >= 'A' ? (key[i * 2 + 1] - 'A' + 10) : (key[i * 2 + 1] - '0'));


	LONG money;
	int status = 0 - read_account(sen, blk, key_type, keyc, &money);
	if (status) {
		CString hits(error_hit[status].c_str());
		m_e_money_s.SetWindowText(hits);
		return;
	}
	else {
		CString Money;
		m_e_money_sub.GetWindowText(Money);

		LONG tmp(_ttol(Money));
		money -= tmp;
		if (money < 0) {
			m_e_money_s.SetWindowText(_T("余额不足"));
			return;
		}
		status = 0 - write_account(sen, blk, key_type, keyc, money);
		if (status) {
			CString hits(error_hit[status].c_str());
			m_e_money_s.SetWindowText(hits);
			return;
		}
		else {
			m_e_money_s.SetWindowText(_T("消费成功"));
		}
	}

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
