// CDebugger.cpp: 实现文件
//

#include "stdafx.h"
#include "RFID.h"
#include "CDebugger.h"
#include "afxdialogex.h"
#include "Hit.h"
#include "ZM124U.h"
#include<string>
#include<iostream>
#include<algorithm>
// CDebugger 对话框

IMPLEMENT_DYNAMIC(CDebugger, CDialog)

CDebugger::CDebugger(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CDebugger, pParent)
{
	key_type = 0 ;
	power = false;
}

CDebugger::~CDebugger()
{
}

void CDebugger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_START, m_e_start);
	DDX_Control(pDX, IDC_EDIT_VERSION, m_e_version);
	DDX_Control(pDX, IDC_EDIT_UID, m_e_uid);
	DDX_Control(pDX, IDC_EDIT_INFO, m_e_info);
	DDX_Control(pDX, IDC_EDIT_LED_INFO, m_e_led_info);
	DDX_Control(pDX, IDC_EDIT_DIG, m_e_led_dig);
	DDX_Control(pDX, IDC_EDIT_LED_S, m_e_led_s);
	DDX_Control(pDX, IDC_EDIT_KEY, m_e_key);
	DDX_Control(pDX, IDC_EDIT_BLOCK0, m_e_block0);
	DDX_Control(pDX, IDC_EDIT_BLOCK1, m_e_block1);
	DDX_Control(pDX, IDC_EDIT_BLOCK2, m_e_block2);
	DDX_Control(pDX, IDC_EDIT_BLOCK3_1, m_e_block3_1);
	DDX_Control(pDX, IDC_EDIT_BLOCK3_2, m_e_block3_2);
	DDX_Control(pDX, IDC_EDIT_BLOCK3_3, m_e_block3_3);
	DDX_Control(pDX, IDC_EDIT_RNW_S, m_e_rnw_s);
	DDX_Control(pDX, IDC_BUTTON_START, m_b_start);
	DDX_Control(pDX, IDC_BUTTON_VERSION, m_b_version);
	DDX_Control(pDX, IDC_BUTTON_UID, m_b_uid);
	DDX_Control(pDX, IDC_BUTTON_LED_SET, m_b_set);
	DDX_Control(pDX, IDC_BUTTON_KEY, m_b_key);
	DDX_Control(pDX, IDC_BUTTON_R_SEN, m_b_r_sen);
	DDX_Control(pDX, IDC_BUTTON_R_BLOCK, m_b_r_block);
	DDX_Control(pDX, IDC_BUTTON_W_BLOCK, m_b_w_block);
	DDX_Control(pDX, IDC_RADIO_KEYA, m_rba);
	DDX_Control(pDX, IDC_RADIO_KEYB, m_rbb);
	DDX_Control(pDX, IDC_COMBO_SEN, m_cb_sen);
	DDX_Control(pDX, IDC_COMBO_BLOCK, m_cb_block);
}


BEGIN_MESSAGE_MAP(CDebugger, CDialog)
	ON_BN_CLICKED(IDC_RADIO_KEYA, &CDebugger::OnBnClickedRadioKey)
	ON_BN_CLICKED(IDC_RADIO_KEYB, &CDebugger::OnBnClickedRadioKey)
	ON_BN_CLICKED(IDC_BUTTON_START, &CDebugger::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_UID, &CDebugger::OnBnClickedButtonUid)
	ON_BN_CLICKED(IDC_BUTTON_VERSION, &CDebugger::OnBnClickedButtonVersion)
	ON_BN_CLICKED(IDC_BUTTON_KEY, &CDebugger::OnBnClickedButtonKey)
	ON_BN_CLICKED(IDC_BUTTON_R_CLEAR, &CDebugger::OnBnClickedButtonRClear)
	ON_BN_CLICKED(IDC_BUTTON_R_SEN, &CDebugger::OnBnClickedButtonRSen)
	ON_BN_CLICKED(IDC_BUTTON_R_BLOCK, &CDebugger::OnBnClickedButtonRBlock)
	ON_BN_CLICKED(IDC_BUTTON_W_BLOCK, &CDebugger::OnBnClickedButtonWBlock)
END_MESSAGE_MAP()


// CDebugger 消息处理程序


void CDebugger::OnBnClickedRadioKey()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int flag = m_rba.GetCheck();
	switch (flag)
	{
	case 0:
		key_type = 0x0A;
		
		break;
	case 1:
		key_type = 0x0B;
		
		break;
	default:
		break;
	}
}


void CDebugger::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if(power){
		int start = 0 - IDD_PowerOff();
		CString hits(error_hit[start].c_str());
		m_e_start.SetWindowText(hits);
		if (!start) {
			m_b_start.SetWindowText(_T("开启设备")); 
			power = false;
		}
	}
	else {
		int start = 0 - IDD_PowerOn();
		CString hits(error_hit[start].c_str());
		m_e_start.SetWindowText(hits);
		if (!start) {
			m_b_start.SetWindowText(_T("关闭设备"));
			power = true;
		}
	}
	//if (start) IDD_PowerOff();
}


void CDebugger::OnBnClickedButtonUid()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char uid[50];
	int uid_len;
	int start = 0 - find_14443(uid, &uid_len);
	if (start) {
		CString hits(error_hit[start].c_str());
		m_e_info.SetWindowText(hits);
	}
	else {
		CString Uid,tmp;
		for (int i = 0; i < uid_len; i++) {
			tmp.Format(_T("%02X"), uid[i]);
			Uid += tmp;
		}
		m_e_uid.SetWindowText(Uid);
		m_e_info.SetWindowText(_T("查询成功"));
	}
}


void CDebugger::OnBnClickedButtonVersion()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDebugger::OnBnClickedButtonKey()
{
	m_e_key.SetWindowText(_T("FFFFFFFFFFFF"));
	m_rba.SetCheck(0);
	m_rbb.SetCheck(1);
	key_type = 0x0B;
	// TODO: 在此添加控件通知处理程序代码
}


void CDebugger::OnBnClickedButtonRClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_e_key.SetWindowText(_T(""));
	m_rba.SetCheck(0);
	m_rbb.SetCheck(0);
	key_type = 0;
	m_cb_sen.SetWindowText(_T(""));
	m_cb_block.SetWindowText(_T(""));
	m_e_block0.SetWindowText(_T(""));
	m_e_block1.SetWindowText(_T(""));
	m_e_block2.SetWindowText(_T(""));
	m_e_block3_1.SetWindowText(_T(""));
	m_e_block3_2.SetWindowText(_T(""));
	m_e_block3_3.SetWindowText(_T(""));
	m_e_rnw_s.SetWindowText(_T("初始化成功"));
}


void CDebugger::OnBnClickedButtonRSen()
{
	// TODO: 在此添加控件通知处理程序代码
	if (key_type == 0) {
		m_e_rnw_s.SetWindowText(_T("请选择密钥类型"));
		return;
	}
	if (m_e_key.GetWindowTextLength() == 0) {
		m_e_rnw_s.SetWindowText(_T("请输入密钥"));
		return;
	}
	if (m_e_key.GetWindowTextLength() != 12) {
		m_e_rnw_s.SetWindowText(_T("密钥长度不匹配"));
		return;
	}
	if (m_cb_sen.GetWindowTextLength() == 0) {
		m_e_rnw_s.SetWindowText(_T("请选择扇区号"));
		return;
	}
	CString key, sen;
	m_e_key.GetWindowText(key);
	m_cb_sen.GetWindowText(sen);

	string keys = CStringA(key);
	transform(keys.begin(), keys.end(), keys.begin(), toupper);
	int sens = strtol(CStringA(sen), NULL, 16);
	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (keys[i * 2] >= 'A' ? (keys[i * 2] - 'A' + 10) : (keys[i * 2] - '0'))*16 + (keys[i * 2 + 1] >= 'A' ? (keys[i * 2 + 1] - 'A' + 10) : (keys[i * 2 + 1] - '0'));

	
	for (int i = 0; i < 3; i++) {
		unsigned char data[100];
		int len;
		int status = 0-read_block(sens, i, key_type, keyc, data, &len);
		if (status) {
			CString hits(error_hit[status].c_str());
			m_e_rnw_s.SetWindowText(hits);
			return;
		}
		else {
			CString Data, tmp;
			for (int i = 0; i < len; i++) {
				tmp.Format(_T("%02X"),data[i]);
				Data += tmp;
			}
			if(i==0)m_e_block0.SetWindowText(Data);
			if(i==1)m_e_block1.SetWindowText(Data);
			if(i==2)m_e_block2.SetWindowText(Data);
		}
	}
	unsigned char data[100];
	int len;
	int status = 0 - read_block(sens, 3, key_type, keyc, data, &len);
	if (status) {
		CString hits(error_hit[status].c_str());
		m_e_rnw_s.SetWindowText(hits);
		return;
	}
	else {
		CString Data0,Data1,Data2, tmp;
		for (int i = 0; i < 6; i++) {
			tmp.Format(_T("%02X"), data[i]);
			Data0 += tmp;
		}
		for (int i = 6; i < 10; i++) {
			tmp.Format(_T("%02X"), data[i]);
			Data1 += tmp;
		}
		for (int i = 10; i < 16; i++) {
			tmp.Format(_T("%02X"), data[i]);
			Data2 += tmp;
		}
		m_e_block3_1.SetWindowText(Data0);
		m_e_block3_2.SetWindowText(Data1);
		m_e_block3_3.SetWindowText(Data2);
		m_e_rnw_s.SetWindowText(_T("读取成功"));
	}

}


void CDebugger::OnBnClickedButtonRBlock()
{
	// TODO: 在此添加控件通知处理程序代码
	if (key_type == 0) {
		m_e_rnw_s.SetWindowText(_T("请选择密钥类型"));
		return;
	}
	if (m_e_key.GetWindowTextLength() == 0) {
		m_e_rnw_s.SetWindowText(_T("请输入密钥"));
		return;
	}
	if (m_e_key.GetWindowTextLength() != 12) {
		m_e_rnw_s.SetWindowText(_T("密钥长度不匹配"));
		return;
	}
	if (m_cb_sen.GetWindowTextLength() == 0) {
		m_e_rnw_s.SetWindowText(_T("请选择扇区号"));
		return;
	}
	if (m_cb_block.GetWindowTextLength() == 0) {
		m_e_rnw_s.SetWindowText(_T("请选择块号"));
		return;
	}

	CString key, sen,blk;
	m_e_key.GetWindowText(key);
	m_cb_sen.GetWindowText(sen);
	m_cb_block.GetWindowText(blk);

	string keys = CStringA(key);
	transform(keys.begin(), keys.end(), keys.begin(), toupper);
	int sens = strtol(CStringA(sen), NULL, 16);
	int blks = strtol(CStringA(blk), NULL, 16);

	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (keys[i * 2] >= 'A' ? (keys[i * 2] - 'A' + 10) : (keys[i * 2] - '0')) * 16 + (keys[i * 2 + 1] >= 'A' ? (keys[i * 2 + 1] - 'A' + 10) : (keys[i * 2 + 1] - '0'));

	unsigned char data[100];
	int len;
	int status = 0 - read_block(sens, blks, key_type, keyc, data, &len);
	if (status) {
		CString hits(error_hit[status].c_str());
		m_e_rnw_s.SetWindowText(hits);
		return;
	}
	else {
		CString Data, tmp;
		if (blks == 3) {
			CString Data0, Data1, Data2, tmp;
			for (int i = 0; i < 6; i++) {
				tmp.Format(_T("%02X"), data[i]);
				Data0 += tmp;
			}
			for (int i = 6; i < 10; i++) {
				tmp.Format(_T("%02X"), data[i]);
				Data1 += tmp;
			}
			for (int i = 10; i < 16; i++) {
				tmp.Format(_T("%02X"), data[i]);
				Data2 += tmp;
			}
			m_e_block3_1.SetWindowText(Data0);
			m_e_block3_2.SetWindowText(Data1);
			m_e_block3_3.SetWindowText(Data2);
			m_e_rnw_s.SetWindowText(_T("读取成功"));
		}
		else {
			for (int i = 0; i < len; i++) {
				tmp.Format(_T("%02X"), data[i]);
				Data += tmp;
			}
			if (blks == 0)m_e_block0.SetWindowText(Data);
			if (blks == 1)m_e_block1.SetWindowText(Data);
			if (blks == 2)m_e_block2.SetWindowText(Data);
			m_e_rnw_s.SetWindowText(_T("读取成功"));
		}
	}
}


void CDebugger::OnBnClickedButtonWBlock()
{
	// TODO: 在此添加控件通知处理程序代码
	if (key_type == 0) {
		m_e_rnw_s.SetWindowText(_T("请选择密钥类型"));
		return;
	}
	if (m_e_key.GetWindowTextLength() == 0) {
		m_e_rnw_s.SetWindowText(_T("请输入密钥"));
		return;
	}
	if (m_e_key.GetWindowTextLength() != 12) {
		m_e_rnw_s.SetWindowText(_T("密钥长度不匹配"));
		return;
	}
	if (m_cb_sen.GetWindowTextLength() == 0) {
		m_e_rnw_s.SetWindowText(_T("请选择扇区号"));
		return;
	}
	if (m_cb_block.GetWindowTextLength() == 0) {
		m_e_rnw_s.SetWindowText(_T("请选择块号"));
		return;
	}

	CString key, sen, blk;
	m_e_key.GetWindowText(key);
	m_cb_sen.GetWindowText(sen);
	m_cb_block.GetWindowText(blk);

	string keys = CStringA(key);
	transform(keys.begin(), keys.end(), keys.begin(), toupper);
	int sens = strtol(CStringA(sen), NULL, 16);
	int blks = strtol(CStringA(blk), NULL, 16);

	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (keys[i * 2] >= 'A' ? (keys[i * 2] - 'A' + 10) : (keys[i * 2] - '0')) * 16 + (keys[i * 2 + 1] >= 'A' ? (keys[i * 2 + 1] - 'A' + 10) : (keys[i * 2 + 1] - '0'));

	CString data;
	if (blks == 0)m_e_block0.GetWindowText(data);
	if (blks == 1)m_e_block1.GetWindowText(data);
	if (blks == 2)m_e_block2.GetWindowText(data);

	string datas = CStringA(data);
	int len = datas.length();
	transform(datas.begin(), datas.end(), datas.begin(), toupper);
	unsigned char Data[8] = { 0 };
	for (int i = 0; i < 8&&i*2<len; i++)
		if(i*2+1==len)Data[7 - i] = (datas[len - i * 2 - 1] >= 'A' ? (datas[len - i * 2 - 1] - 'A' + 10) : (datas[len - i * 2 - 1] - '0'));
		else Data[7-i] = (datas[len - i * 2 - 2] >= 'A' ? (datas[len - i * 2 - 2] - 'A' + 10) : (datas[len - i * 2 - 2] - '0')) * 16 + (datas[len-i * 2 - 1] >= 'A' ? (datas[len - i * 2 - 1] - 'A' + 10) : (datas[len - i * 2 - 1] - '0'));
	
	int status = 0 - write_block(blks,sens,key_type,keyc,Data,8);
	if (status) {
		CString hits(error_hit[status].c_str());
		m_e_rnw_s.SetWindowText(hits);
		return;
	}
	else {
		m_e_rnw_s.SetWindowText(_T("写入成功"));
	}

}
