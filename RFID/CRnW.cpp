// CRnW.cpp: 实现文件
//

#include "stdafx.h"
#include "RFID.h"
#include "CRnW.h"
#include "afxdialogex.h"


// CRnW 对话框

IMPLEMENT_DYNAMIC(CRnW, CDialog)

CRnW::CRnW(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CRnW, pParent)
{

}

CRnW::~CRnW()
{
}

void CRnW::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BLOCK0, meBlock0);
	DDX_Control(pDX, IDC_EDIT_BLOCK1, meBlock1);
	DDX_Control(pDX, IDC_EDIT_BLOCK2, meBlock2);
	DDX_Control(pDX, IDC_EDIT_BLOCK3_1, meBlock3_1);
	DDX_Control(pDX, IDC_EDIT_BLOCK3_2, meBlock3_2);
	DDX_Control(pDX, IDC_EDIT_BLOCK3_3, meBlock3_3);
	DDX_Control(pDX, IDC_EDIT_RNW_S, meStatus);
	DDX_Control(pDX, IDC_BUTTON_R_SEN, mbRSen);
	DDX_Control(pDX, IDC_BUTTON_R_BLOCK, mbRBlock);
	DDX_Control(pDX, IDC_BUTTON_W_BLOCK, mbWBlock);
	DDX_Control(pDX, IDC_BUTTON_R_CLEAR, mbClean);
}


BEGIN_MESSAGE_MAP(CRnW, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_R_SEN, &CRnW::OnBnClickedButtonRSen)
	ON_BN_CLICKED(IDC_BUTTON_R_BLOCK, &CRnW::OnBnClickedButtonRBlock)
	ON_BN_CLICKED(IDC_BUTTON_W_BLOCK, &CRnW::OnBnClickedButtonWBlock)
	ON_BN_CLICKED(IDC_BUTTON_R_CLEAR, &CRnW::OnBnClickedButtonRClear)
END_MESSAGE_MAP()


// CRnW 消息处理程序


void CRnW::OnBnClickedButtonRSen()
{
	// TODO: 在此添加控件通知处理程序代码
	if (key_type == 0) {
		meStatus.SetWindowText(_T("请选择密钥类型"));
		return;
	}
	if (key.GetLength() == 0) {
		meStatus.SetWindowText(_T("请输入密钥"));
		return;
	}
	if (key.GetLength() != 12) {
		meStatus.SetWindowText(_T("密钥长度不匹配"));
		return;
	}
	if (sen.GetLength() == 0) {
		meStatus.SetWindowText(_T("请选择扇区号"));
		return;
	}
	string keys = CStringA(key);
	transform(keys.begin(), keys.end(), keys.begin(), toupper);
	int sens = strtol(CStringA(sen), NULL, 16);
	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (keys[i * 2] >= 'A' ? (keys[i * 2] - 'A' + 10) : (keys[i * 2] - '0')) * 16 + (keys[i * 2 + 1] >= 'A' ? (keys[i * 2 + 1] - 'A' + 10) : (keys[i * 2 + 1] - '0'));


	for (int i = 0; i < 3; i++) {
		unsigned char data[100];
		int len;
		int status = 0 - read_block(sens, i, key_type, keyc, data, &len);
		if (status) {
			CString hits(hit.error_hit[status].c_str());
			meStatus.SetWindowText(hits);
			return;
		}
		else {
			CString Data, tmp;
			for (int i = 0; i < len; i++) {
				tmp.Format(_T("%02X"), data[i]);
				Data += tmp;
			}
			if (i == 0)meBlock0.SetWindowText(Data);
			if (i == 1)meBlock1.SetWindowText(Data);
			if (i == 2)meBlock2.SetWindowText(Data);
		}
	}
	unsigned char data[100];
	int len;
	int status = 0 - read_block(sens, 3, key_type, keyc, data, &len);
	if (status) {
		CString hits(hit.error_hit[status].c_str());
		meStatus.SetWindowText(hits);
		return;
	}
	else {
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
		meBlock3_1.SetWindowText(Data0);
		meBlock3_2.SetWindowText(Data1);
		meBlock3_3.SetWindowText(Data2);
		meStatus.SetWindowText(_T("读取成功"));
	}

}


void CRnW::OnBnClickedButtonRBlock()
{
	// TODO: 在此添加控件通知处理程序代码
	if (key_type == 0) {
		meStatus.SetWindowText(_T("请选择密钥类型"));
		return;
	}
	if (key.GetLength() == 0) {
		meStatus.SetWindowText(_T("请输入密钥"));
		return;
	}
	if (key.GetLength() != 12) {
		meStatus.SetWindowText(_T("密钥长度不匹配"));
		return;
	}
	if (sen.GetLength() == 0) {
		meStatus.SetWindowText(_T("请选择扇区号"));
		return;
	}
	if (blk.GetLength() == 0) {
		meStatus.SetWindowText(_T("请选择块号"));
		return;
	}
	//参数类型转换
	string keys = CStringA(key); //密钥类型转换
	transform(keys.begin(), keys.end(), keys.begin(), toupper);
	unsigned char keyc[6];
	for (int i = 0; i < 6; i++) //一次转换两个字符
		keyc[i] = (keys[i * 2] >= 'A' ? (keys[i * 2] - 'A' + 10) : (keys[i * 2] - '0')) * 16 + (keys[i * 2 + 1] >= 'A' ? (keys[i * 2 + 1] - 'A' + 10) : (keys[i * 2 + 1] - '0'));
	int sens = strtol(CStringA(sen), NULL, 16);//扇区转换
	int blks = strtol(CStringA(blk), NULL, 16);//块转换

	unsigned char data[100];
	int len;
	int status = 0 - read_block(sens, blks, key_type, keyc, data, &len);
	if (status) { //判断是否读取成功
		CString hits(hit.error_hit[status].c_str());
		meStatus.SetWindowText(hits);
		return;
	}
	else {
		CString Data, tmp;
		if (blks == 3) { //块3单独处理
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
			meBlock3_1.SetWindowText(Data0);
			meBlock3_2.SetWindowText(Data1);
			meBlock3_3.SetWindowText(Data2);
			meStatus.SetWindowText(_T("读取成功"));
		}
		else {
			for (int i = 0; i < len; i++) {
				tmp.Format(_T("%02X"), data[i]);
				Data += tmp;
			}
			if (blks == 0)meBlock0.SetWindowText(Data);
			if (blks == 1)meBlock1.SetWindowText(Data);
			if (blks == 2)meBlock2.SetWindowText(Data);
			meStatus.SetWindowText(_T("读取成功"));
		}
	}
}


void CRnW::OnBnClickedButtonWBlock()
{
	// TODO: 在此添加控件通知处理程序代码
	if (key_type == 0) {
		meStatus.SetWindowText(_T("请选择密钥类型"));
		return;
	}
	if (key.GetLength() == 0) {
		meStatus.SetWindowText(_T("请输入密钥"));
		return;
	}
	if (key.GetLength() != 12) {
		meStatus.SetWindowText(_T("密钥长度不匹配"));
		return;
	}
	if (sen.GetLength() == 0) {
		meStatus.SetWindowText(_T("请选择扇区号"));
		return;
	}
	if (blk.GetLength() == 0) {
		meStatus.SetWindowText(_T("请选择块号"));
		return;
	}


	string keys = CStringA(key);
	transform(keys.begin(), keys.end(), keys.begin(), toupper);
	int sens = strtol(CStringA(sen), NULL, 16);
	int blks = strtol(CStringA(blk), NULL, 16);

	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (keys[i * 2] >= 'A' ? (keys[i * 2] - 'A' + 10) : (keys[i * 2] - '0')) * 16 + (keys[i * 2 + 1] >= 'A' ? (keys[i * 2 + 1] - 'A' + 10) : (keys[i * 2 + 1] - '0'));

	CString data;
	if (blks == 0)meBlock0.GetWindowText(data);
	if (blks == 1)meBlock1.GetWindowText(data);
	if (blks == 2)meBlock2.GetWindowText(data);
	if (blks == 3) {
		CString data1, data2, data3;
		meBlock3_1.GetWindowText(data1);
		meBlock3_2.GetWindowText(data2);
		meBlock3_3.GetWindowText(data3);
		if (data1.GetLength() != 12 && data2.GetLength() != 8 && data3.GetLength() != 12) {
			meStatus.SetWindowText(_T("请检块3查长度是否正确"));
			return;
		}
		data = data1 + data2 + data3;
		string datas = CStringA(data);
		transform(datas.begin(), datas.end(), datas.begin(), toupper);
		unsigned char Data[16] = { 0 };
		for (int i = 0; i < 16; i++) {
			Data[i] = (datas[i * 2] >= 'A' ? (data[i * 2] - 'A' + 10) : (data[i * 2] - '0')) * 16 + (datas[i * 2] >= 'A' ? (data[i * 2 + 1] - 'A' + 10) : (data[i * 2 + 1] - '0'));
		}
		int status = 0 - write_block(blks, sens, key_type, keyc, Data, 8);
		if (status) {
			CString hits(hit.error_hit[status].c_str());
			meStatus.SetWindowText(hits);
			return;
		}
		else {
			meStatus.SetWindowText(_T("写入成功"));
		}
	}
	else {
		string datas = CStringA(data);
		int len = datas.length();
		transform(datas.begin(), datas.end(), datas.begin(), toupper);
		unsigned char Data[16] = { 0 };//设置数据长度默认全部为0
		for (int i = 0; i < 16 && i * 2 < len; i++) { //反向转换 2个一组进行转换 单独处理最后奇数个数据
			if (i * 2 + 1 == len)Data[15 - i] = (datas[len - i * 2 - 1] >= 'A' ? (datas[len - i * 2 - 1] - 'A' + 10) : (datas[len - i * 2 - 1] - '0'));
			else Data[15 - i] = (datas[len - i * 2 - 2] >= 'A' ? (datas[len - i * 2 - 2] - 'A' + 10) : (datas[len - i * 2 - 2] - '0')) * 16 + (datas[len - i * 2 - 1] >= 'A' ? (datas[len - i * 2 - 1] - 'A' + 10) : (datas[len - i * 2 - 1] - '0'));
		}
		int status = 0 - write_block(blks, sens, key_type, keyc, Data, 16);
		if (status) {
			CString hits(hit.error_hit[status].c_str());
			meStatus.SetWindowText(hits);
			return;
		}
		else {
			meStatus.SetWindowText(_T("写入成功"));
		}
	}
}
BOOL CRnW::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (meBlock0.GetFocus()
		|| meBlock1.GetFocus()
		|| meBlock2.GetFocus() 
		|| meBlock3_1.GetFocus()
		|| meBlock3_2.GetFocus()
		|| meBlock3_3.GetFocus()) {
		short nks = GetKeyState(VK_CONTROL);
		if (nks & 0x8000) {
			return CDialog::PreTranslateMessage(pMsg);
		}

		//检查输入的内容
		if ((pMsg->wParam >= 0x30 && pMsg->wParam <= 0x39) ||
			(pMsg->wParam >= 'a' && pMsg->wParam <= 'f') ||
			(pMsg->wParam >= 'A' && pMsg->wParam <= 'F') ||
			(pMsg->wParam <= 0x08) ||
			(pMsg->wParam == 0x20)) {
			return CDialog::PreTranslateMessage(pMsg);
		}
		else {
			MessageBeep(-1);
			pMsg->wParam = NULL;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CRnW::OnBnClickedButtonRClear()
{
	// TODO: 在此添加控件通知处理程序代码
	meBlock0.SetWindowText(_T(""));
	meBlock1.SetWindowText(_T(""));
	meBlock2.SetWindowText(_T(""));
	meBlock3_1.SetWindowText(_T(""));
	meBlock3_2.SetWindowText(_T(""));
	meBlock3_3.SetWindowText(_T(""));
	meStatus.SetWindowText(_T("清除成功"));
}
