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
	ON_WM_TIMER()
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
	CDatabase db;
	db.Open(NULL, FALSE, FALSE, _T("ODBC;DSN=RFID;UID=root;PWD=root"));
	if (!db.IsOpen()) {
		MessageBox(_T("连接失败"));
		db.Close();
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
	int status = 0 -write_account(sens, blks, key_type, keyc, times);
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
		CString str,query;
		CTime t;
		t = CTime::GetCurrentTime();
		tmp.Format(_T("%ld"), times);
		str = t.Format("%Y/%m/%d %X");
		str += _T(" UID:") + uid;
		str += _T(" Init:") + tmp + _T(" s\r\n");
		file.Write(CStringA(str), strlen(CStringA(str)));
		file.Close();
		mlhistory.InsertString(mlhistory.GetCount(), str);
		query.Format(_T("REPLACE INTO Money(cid, sen, blk, Money) VALUES('%s', '%s', '%s', '%s')"), uid, sen, blk, tmp);
		try {
			db.ExecuteSQL(query);
		}
		catch (CDBException *e) {
			e->ReportError();  //报告异常原因，如主键异常
			e->Delete();
			db.Close();
			return;
		}
		catch (CMemoryException *e) {
			MessageBox(_T("数据库内存异常!"));
			e->Delete();
			return;
		}
		catch (...) {
			MessageBox(_T("数据库其它异常!"));
			return;
		}
		query.Format(_T("REPLACE INTO Historys(cid, sen, blk, info) VALUES('%s', '%s', '%s', '%s')"), uid, sen, blk, str);
		try {
			db.ExecuteSQL(query);
		}
		catch (CDBException *e) {
			e->ReportError();  //报告异常原因，如主键异常
			e->Delete();
			db.Close();
			return;
		}
		catch (CMemoryException *e) {
			MessageBox(_T("数据库内存异常!"));
			e->Delete();
			return;
		}
		catch (...) {
			MessageBox(_T("数据库其它异常!"));
			return;
		}

		db.Close();
	}
}


void CTimeMeter::OnBnClickedButtonUse()
{
	// TODO: 在此添加控件通知处理程序代码
	if (start) {
		CDatabase db;
		db.Open(NULL, FALSE, FALSE, _T("ODBC;DSN=RFID;UID=root;PWD=root"));
		if (!db.IsOpen()) {
			MessageBox(_T("连接失败"));
			db.Close();
			return;
		}
		start = false;
		mbStart.SetWindowText(_T("开启使用"));
		KillTimer(1);
		CFile file;
		file.Open(_T("history_time.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
		file.SeekToEnd();
		CString str,tmp, qurey;
		CTime t;
		t = CTime::GetCurrentTime();
		tmp.Format(_T("%d"), cnt);
		str = t.Format("%Y/%m/%d %X");
		str += _T(" UID:") + uid;
		str += _T(" Use:") + tmp + _T(" s\r\n");
		file.Write(CStringA(str), strlen(CStringA(str)));
		file.Close();
		mlhistory.InsertString(mlhistory.GetCount(), str);
		cnt = 0;
		qurey.Format(_T("UPDATE Money SET Money = Money - %s WHERE cid = '%s' AND sen ='%s' AND blk ='%s'"),tmp, uid, sen, blk);
		try {
			db.ExecuteSQL(qurey);
		}
		catch (CDBException *e) {
			e->ReportError();  //报告异常原因，如主键异常
			e->Delete();
			db.Close();
			return;
		}
		catch (CMemoryException *e) {
			MessageBox(_T("数据库内存异常!"));
			e->Delete();
			return;
		}
		catch (...) {
			MessageBox(_T("数据库其它异常!"));
			return;
		}
		qurey.Format(_T("REPLACE INTO Historys(cid, sen, blk, info) VALUES('%s', '%s', '%s', '%s')"), uid, sen, blk, str);
		try {
			db.ExecuteSQL(qurey);
		}
		catch (CDBException *e) {
			e->ReportError();  //报告异常原因，如主键异常
			e->Delete();
			db.Close();
			return;
		}
		catch (CMemoryException *e) {
			MessageBox(_T("数据库内存异常!"));
			e->Delete();
			return;
		}
		catch (...) {
			MessageBox(_T("数据库其它异常!"));
			return;
		}
		db.Close();
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
		CDatabase db;
		db.Open(NULL, FALSE, FALSE, _T("ODBC;DSN=RFID;UID=root;PWD=root"));
		if (!db.IsOpen()) {
			MessageBox(_T("连接失败"));
			db.Close();
			return;
		}
		CString qurey;
		CRecordset rs(&db);
		qurey.Format(_T("SELECT * FROM Money WHERE cid = '%s' AND sen ='%s' AND blk ='%s'"), uid, sen, blk);
		rs.Open(CRecordset::forwardOnly, qurey);//接收结果
		if (rs.IsEOF()) {//没有查询到任何信息
			meStatus.SetWindowText(_T("请先初始化"));
			return;
		}
		start = true;
		mbStart.SetWindowText(_T("停止使用"));
		SetTimer(1, 1000,NULL);
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
	CDatabase db;
	db.Open(NULL, FALSE, FALSE, _T("ODBC;DSN=RFID;UID=root;PWD=root"));
	if (!db.IsOpen()) {
		MessageBox(_T("连接失败"));
		db.Close();
		return;
	}
	CString qurey;
	CRecordset rs(&db);
	qurey.Format(_T("SELECT * FROM Money WHERE cid = '%s' AND sen ='%s' AND blk ='%s'"), uid, sen, blk);
	rs.Open(CRecordset::forwardOnly, qurey);//接收结果
	if (rs.IsEOF()) {//没有查询到任何信息
		meStatus.SetWindowText(_T("请先初始化"));
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
	int status = 0 -read_account(sens, blks, key_type, keyc, &t);
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
		status = 0 -write_account(sens, blks, key_type, keyc, times + t);
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
		qurey.Format(_T("UPDATE Money SET Money = Money + %s WHERE cid = '%s' AND sen ='%s' AND blk ='%s'"), tmp, uid, sen, blk);
		try {
			db.ExecuteSQL(qurey);
		}
		catch (CDBException *e) {
			e->ReportError();  //报告异常原因，如主键异常
			e->Delete();
			db.Close();
			return;
		}
		catch (CMemoryException *e) {
			MessageBox(_T("数据库内存异常!"));
			e->Delete();
			return;
		}
		catch (...) {
			MessageBox(_T("数据库其它异常!"));
			return;
		}
		qurey.Format(_T("REPLACE INTO Historys(cid, sen, blk, info) VALUES('%s', '%s', '%s', '%s')"), uid, sen, blk, str);
		try {
			db.ExecuteSQL(qurey);
		}
		catch (CDBException *e) {
			e->ReportError();  //报告异常原因，如主键异常
			e->Delete();
			db.Close();
			return;
		}
		catch (CMemoryException *e) {
			MessageBox(_T("数据库内存异常!"));
			e->Delete();
			return;
		}
		catch (...) {
			MessageBox(_T("数据库其它异常!"));
			return;
		}
		db.Close();
	}
}


void CTimeMeter::OnBnClickedButtonHisClean2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CFile file;
	file.Open(_T("history_time.txt"), CFile::modeCreate | CFile::modeWrite);
	file.Close();
	mlhistory.ResetContent();
}


void CTimeMeter::OnBnClickedButtonHisLoad2()
{
	// TODO: 在此添加控件通知处理程序代码
	CStdioFile  file;
	file.Open(_T("history_time.txt"), CFile::modeRead | CFile::typeText);
	CString his;
	while (file.ReadString(his)) {
		mlhistory.AddString(his);
	}
}


void CTimeMeter::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnTimer(nIDEvent);
	if (nIDEvent == 1) {

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
		LONG times=0;
		int status = 0 -read_account(sens, blks, key_type, keyc, &times);
		if (status) {
			CString hits(hit.error_hit[status].c_str());
			meStatus.SetWindowText(hits);
			OnBnClickedButtonUse();
			return;
		}
		times = times - 1;
		if (times < 0) {
			meStatus.SetWindowText(_T("余时不足"));
			OnBnClickedButtonUse();
			return;
		}
		status = 0 -write_account(sens, blks, key_type, keyc, times);
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
 
/*  //历史记录数据库加载，溯源到 卡的某个扇区的某个块中的历史记录 目前考虑到展示文件读写 暂未合并
void CTimeMeter::OnBnClickedButtonHisLoad2()
{
	// TODO: 在此添加控件通知处理程序代码
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
	CDatabase db;
	db.Open(NULL, FALSE, FALSE, _T("ODBC;DSN=RFID;UID=root;PWD=root"));
	if (!db.IsOpen()) {
		MessageBox(_T("连接失败"));
		db.Close();
		return;
	}
	CString qurey;
	CRecordset rs(&db);
	qurey.Format(_T("SELECT * FROM Historys WHERE cid = '%s' AND sen ='%s' AND blk ='%s'"), uid, sen, blk);
	rs.Open(CRecordset::forwardOnly, qurey);//接收结果
	if (rs.IsEOF()) {//没有查询到任何信息
		meStatus.SetWindowText(_T("请先初始化"));
		return;
	}
	while (rs.IsEOF()) {
		CString his;
		rs.GetFieldValue(_T("hits"), his);
		rs.MoveNext();
		mlhistory.AddString(his);
	}
	rs.Close();
	db.Close();
}

//*/