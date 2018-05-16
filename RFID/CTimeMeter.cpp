// CTimeMeter.cpp: 实现文件
//

#include "stdafx.h"
#include "RFID.h"
#include "CTimeMeter.h"
#include "afxdialogex.h"


// CTimeMeter 对话框

IMPLEMENT_DYNAMIC(CTimeMeter, CDialog)

CTimeMeter::CTimeMeter(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CTimeMeter, pParent)
{
	start = false;
	cnt = 0;
}

CTimeMeter::~CTimeMeter()
{
}

void CTimeMeter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HOUR, meHour1);
	DDX_Control(pDX, IDC_EDIT_HOUR2, meHour2);
	DDX_Control(pDX, IDC_EDIT_MIN, meMin1);
	DDX_Control(pDX, IDC_EDIT_MIN2, meMin2);
	DDX_Control(pDX, IDC_EDIT_SEC, meSec1);
	DDX_Control(pDX, IDC_EDIT_SEC2, meSec2);
	DDX_Control(pDX, IDC_EDIT_TS, meStatus);
	DDX_Control(pDX, IDC_BUTTON_USE, mbStart);
	DDX_Control(pDX, IDC_LIST_HIS2, mlhistory);
	
}


BEGIN_MESSAGE_MAP(CTimeMeter, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TIME, &CTimeMeter::OnBnClickedButtonTime)
	ON_BN_CLICKED(IDC_BUTTON_TIMEINIT, &CTimeMeter::OnBnClickedButtonTimeinit)
	ON_BN_CLICKED(IDC_BUTTON_USE, &CTimeMeter::OnBnClickedButtonUse)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TIME, &CTimeMeter::OnBnClickedButtonAddTime)
	ON_BN_CLICKED(IDC_BUTTON_HIS_CLEAN2, &CTimeMeter::OnBnClickedButtonHisClean2)
	ON_BN_CLICKED(IDC_BUTTON_HIS_LOAD2, &CTimeMeter::OnBnClickedButtonHisLoad2)
END_MESSAGE_MAP()


// CTimeMeter 消息处理程序


void CTimeMeter::OnBnClickedButtonTime()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!key_type) {
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
		meStatus.SetWindowText(_T("请选择扇区"));
		return;
	}
	if (blk.GetLength() == 0) {
		meStatus.SetWindowText(_T("请选择块"));
		return;
	}
	if (uid.GetLength() == 0) {
		meStatus.SetWindowText(_T("请获取UID"));
		return;
	}
	string keys = CStringA(key);
	transform(keys.begin(), keys.end(), keys.begin(), toupper);
	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (keys[i * 2] >= 'A' ? (keys[i * 2] - 'A' + 10) : (keys[i * 2] - '0')) * 16 + (keys[i * 2 + 1] >= 'A' ? (keys[i * 2 + 1] - 'A' + 10) : (keys[i * 2 + 1] - '0'));
	int sens = strtol(CStringA(sen), NULL, 16);
	int blks = strtol(CStringA(blk), NULL, 16);
	LONG times;
	int status = 0 - read_account(sens, blks, key_type, keyc, &times);
	if (status) {
		CString hits(hit.error_hit[status].c_str());
		meStatus.SetWindowText(hits);
		return;
	}
	else {
		CString tmp;
		tmp.Format(_T("%ld"), times/3600);
		meHour1.SetWindowText(tmp);
		tmp.Format(_T("%ld"), (times / 60)%60);
		meMin1.SetWindowText(tmp);
		tmp.Format(_T("%ld"), times  % 60);
		meSec1.SetWindowText(tmp);
	}
}


void CTimeMeter::OnBnClickedButtonTimeinit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!key_type) {
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
		meStatus.SetWindowText(_T("请选择扇区"));
		return;
	}
	if (blk.GetLength() == 0) {
		meStatus.SetWindowText(_T("请选择块"));
		return;
	}
	if (meHour1.GetWindowTextLength() == 0|| meMin1.GetWindowTextLength() == 0|| meSec1.GetWindowTextLength() == 0) {
		meStatus.SetWindowText(_T("请输入时间"));
		return;
	}
	if (uid.GetLength() == 0) {
		meStatus.SetWindowText(_T("请获取UID"));
		return;
	}
	string keys = CStringA(key);
	transform(keys.begin(), keys.end(), keys.begin(), toupper);
	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (keys[i * 2] >= 'A' ? (keys[i * 2] - 'A' + 10) : (keys[i * 2] - '0')) * 16 + (keys[i * 2 + 1] >= 'A' ? (keys[i * 2 + 1] - 'A' + 10) : (keys[i * 2 + 1] - '0'));

	int sens = strtol(CStringA(sen), NULL, 16);
	int blks = strtol(CStringA(blk), NULL, 16);
	CString tmp;
	
	LONG times=0;
	meHour1.GetWindowText(tmp);
	times = _ttol(tmp) * 3600;
	meMin1.GetWindowText(tmp);
	times += _ttol(tmp) * 60;
	meSec1.GetWindowText(tmp);
	times += _ttol(tmp);
	int status = 0 - write_account(sens, blks, key_type, keyc, times);
	if (status) {
		CString hits(hit.error_hit[status].c_str());
		meStatus.SetWindowText(hits);
		return;
	}
	else {
		meStatus.SetWindowText(_T("初始化成功"));
		CFile file;
		file.Open(_T("history_time.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
		file.SeekToEnd();
		CString str;
		CTime t;
		t = CTime::GetCurrentTime();
		tmp.Format(_T("%ld"), times);
		str = t.Format("%Y/%m/%d %X");
		str += _T(" UID:") + uid;
		str += _T(" Init:") + tmp + _T(" s\r\n");
		file.Write(CStringA(str), strlen(CStringA(str)));
		file.Close();
		mlhistory.InsertString(mlhistory.GetCount(), str);
	}
}


void CTimeMeter::OnBnClickedButtonUse()
{
	// TODO: 在此添加控件通知处理程序代码
	if (start) {
		start = false;
		mbStart.SetWindowText(_T("开启使用"));
		cnt = 0;
		KillTimer(1);
		CFile file;
		file.Open(_T("history_time.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
		file.SeekToEnd();
		CString str,tmp;
		CTime t;
		t = CTime::GetCurrentTime();
		tmp.Format(_T("%d"), cnt);
		str = t.Format("%Y/%m/%d %X");
		str += _T(" UID:") + uid;
		str += _T(" Use:") + tmp + _T(" s\r\n");
		file.Write(CStringA(str), strlen(CStringA(str)));
		file.Close();
		mlhistory.InsertString(mlhistory.GetCount(), str);
	}
	else {
		if (!key_type) {
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
			meStatus.SetWindowText(_T("请选择扇区"));
			return;
		}
		if (blk.GetLength() == 0) {
			meStatus.SetWindowText(_T("请选择块"));
			return;
		}
		if (uid.GetLength() == 0) {
			meStatus.SetWindowText(_T("请获取UID"));
			return;
		}
		start = true;
		mbStart.SetWindowText(_T("停止使用"));
		SetTimer(1, 1000, NULL);
	}
}


void CTimeMeter::OnBnClickedButtonAddTime()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!key_type) {
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
		meStatus.SetWindowText(_T("请选择扇区"));
		return;
	}
	if (blk.GetLength() == 0) {
		meStatus.SetWindowText(_T("请选择块"));
		return;
	}
	if (meHour2.GetWindowTextLength() == 0 || meMin2.GetWindowTextLength() == 0 || meSec2.GetWindowTextLength() == 0) {
		meStatus.SetWindowText(_T("请输入时间"));
		return;
	}
	if (uid.GetLength() == 0) {
		meStatus.SetWindowText(_T("请获取UID"));
		return;
	}
	string keys = CStringA(key);
	transform(keys.begin(), keys.end(), keys.begin(), toupper);
	unsigned char keyc[6];
	for (int i = 0; i < 6; i++)
		keyc[i] = (keys[i * 2] >= 'A' ? (keys[i * 2] - 'A' + 10) : (keys[i * 2] - '0')) * 16 + (keys[i * 2 + 1] >= 'A' ? (keys[i * 2 + 1] - 'A' + 10) : (keys[i * 2 + 1] - '0'));

	int sens = strtol(CStringA(sen), NULL, 16);
	int blks = strtol(CStringA(blk), NULL, 16);

	
	LONG t;
	int status = 0 - read_account(sens, blks, key_type, keyc, &t);
	if (status) {
		CString hits(hit.error_hit[status].c_str());
		meStatus.SetWindowText(hits);
		return;
	}
	else {
		CString tmp;
		LONG times = 0;
		meHour2.GetWindowText(tmp);
		times = _ttol(tmp) * 3600;
		meMin2.GetWindowText(tmp);
		times += _ttol(tmp) * 60;
		meSec2.GetWindowText(tmp);
		times += _ttol(tmp);
		status = 0 - write_account(sens, blks, key_type, keyc, times+t);
		if (status) {
			CString hits(hit.error_hit[status].c_str());
			meStatus.SetWindowText(hits);
			return;
		}
		meStatus.SetWindowText(_T("续命成功"));
		CFile file;
		file.Open(_T("history_time.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
		file.SeekToEnd();
		CString str;
		CTime t;
		t = CTime::GetCurrentTime();
		tmp.Format(_T("%ld"), times);
		str = t.Format("%Y/%m/%d %X");
		str += _T(" UID:") + uid;
		str += _T(" Add:") + tmp + _T(" s\r\n");
		file.Write(CStringA(str), strlen(CStringA(str)));
		file.Close();
		mlhistory.InsertString(mlhistory.GetCount(), str);
	}
}


void CTimeMeter::OnBnClickedButtonHisClean2()
{
	// TODO: 在此添加控件通知处理程序代码
	CStdioFile  file;
	file.Open(_T("history_time.txt"), CFile::modeRead | CFile::typeText);
	CString his;
	while (file.ReadString(his)) {
		mlhistory.AddString(his);
	}
}


void CTimeMeter::OnBnClickedButtonHisLoad2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFile file;
	file.Open(_T("history_time.txt"), CFile::modeCreate | CFile::modeWrite);
	file.Close();
	mlhistory.ResetContent();
}
void CTimeMeter::OnTimer(UINT nTimerID) {
	if (nTimerID == 1) {

		if (!key_type) {
			meStatus.SetWindowText(_T("请选择密钥类型"));
			OnBnClickedButtonUse();
			return;
		}
		if (key.GetLength() == 0) {
			meStatus.SetWindowText(_T("请输入密钥"));
			OnBnClickedButtonUse();
			return;
		}
		if (key.GetLength() != 12) {
			meStatus.SetWindowText(_T("密钥长度不匹配"));
			OnBnClickedButtonUse();
			return;
		}
		if (sen.GetLength() == 0) {
			meStatus.SetWindowText(_T("请选择扇区"));
			OnBnClickedButtonUse();
			return;
		}
		if (blk.GetLength() == 0) {
			meStatus.SetWindowText(_T("请选择块"));
			OnBnClickedButtonUse();
			return;
		}
		if (uid.GetLength() == 0) {
			meStatus.SetWindowText(_T("请获取UID"));
			OnBnClickedButtonUse();
			return;
		}
		string keys = CStringA(key);
		transform(keys.begin(), keys.end(), keys.begin(), toupper);
		unsigned char keyc[6];
		for (int i = 0; i < 6; i++)
			keyc[i] = (keys[i * 2] >= 'A' ? (keys[i * 2] - 'A' + 10) : (keys[i * 2] - '0')) * 16 + (keys[i * 2 + 1] >= 'A' ? (keys[i * 2 + 1] - 'A' + 10) : (keys[i * 2 + 1] - '0'));
		int sens = strtol(CStringA(sen), NULL, 16);
		int blks = strtol(CStringA(blk), NULL, 16);
		LONG times;
		int status = 0 - read_account(sens, blks, key_type, keyc, &times);
		if (status) {
			CString hits(hit.error_hit[status].c_str());
			meStatus.SetWindowText(hits);
			OnBnClickedButtonUse();
			return;
		}
		times = times - 1;
		status = 0 - write_account(sens, blks, key_type, keyc, times);
		if (status) {
			CString hits(hit.error_hit[status].c_str());
			meStatus.SetWindowText(hits);
			OnBnClickedButtonUse();
			return;
		}
		CString tmp;
		tmp.Format(_T("%ld"), times / 3600);
		meHour1.SetWindowText(tmp);
		tmp.Format(_T("%ld"), (times / 60) % 60);
		meMin1.SetWindowText(tmp);
		tmp.Format(_T("%ld"), times % 60);
		meSec1.SetWindowText(tmp);
		cnt++;
	}
}