// CMoney.cpp: 实现文件
//

#include "stdafx.h"
#include "RFID.h"
#include "CMoney.h"
#include "afxdialogex.h"


// CMoney 对话框

IMPLEMENT_DYNAMIC(CMoney, CDialog)

CMoney::CMoney(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CMoney, pParent)
{

}

CMoney::~CMoney()
{
}

void CMoney::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MONEY, meMoney);
	DDX_Control(pDX, IDC_EDIT_ADD_MONEY, meAdd);
	DDX_Control(pDX, IDC_EDIT_SUB_MONEY, meSub);
	DDX_Control(pDX, IDC_EDIT_MONEY_S, meStatus);
	DDX_Control(pDX, IDC_BUTTON_INIT, mbInit);
	DDX_Control(pDX, IDC_BUTTON_MONEY, mbQuery);
	DDX_Control(pDX, IDC_BUTTON_ADD_MONEY, mbAdd);
	DDX_Control(pDX, IDC_BUTTON_SUB_MONEY, mbSub);
	DDX_Control(pDX, IDC_BUTTON_HIS_CLEAN, mbClean);
	DDX_Control(pDX, IDC_BUTTON_HIS_LOAD, mbLoad);
	DDX_Control(pDX,IDC_LIST_HIS,mlhistory);
	mlhistory.SetHorizontalExtent(80);
}


BEGIN_MESSAGE_MAP(CMoney, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MONEY, &CMoney::OnBnClickedButtonMoney)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MONEY, &CMoney::OnBnClickedButtonAddMoney)
	ON_BN_CLICKED(IDC_BUTTON_SUB_MONEY, &CMoney::OnBnClickedButtonSubMoney)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CMoney::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_HIS_LOAD, &CMoney::OnBnClickedButtonHisLoad)
	ON_BN_CLICKED(IDC_BUTTON_HIS_CLEAN, &CMoney::OnBnClickedButtonHisClean)
END_MESSAGE_MAP()


// CMoney 消息处理程序


void CMoney::OnBnClickedButtonMoney()
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
	//读取余额
	LONG money;
	int status = 0 - read_account(sens, blks, key_type, keyc, &money);
	if (status) {
		CString hits(hit.error_hit[status].c_str());
		meStatus.SetWindowText(hits);
	}
	else {
		CString Money;
		Money.Format(_T("%ld"), money);
		meMoney.SetWindowText(Money);
	}
}


void CMoney::OnBnClickedButtonAddMoney()
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
	if (meAdd.GetWindowTextLength() == 0) {
		meStatus.SetWindowText(_T("请输入金额"));
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

	LONG money=0;
	int status = 0 -read_account(sens, blks, key_type, keyc, &money);
	if (status) {
		CString hits(hit.error_hit[status].c_str());
		meStatus.SetWindowText(hits);
		return;
	}
	else {
		CString Money;
		meAdd.GetWindowText(Money);
		LONG tmp(_ttol(Money));
		money += tmp;
		status = 0 -write_account(sens, blks, key_type, keyc, money);
		if (status) {
			CString hits(hit.error_hit[status].c_str());
			meStatus.SetWindowText(hits);
			return;
		}
		else {
			meStatus.SetWindowText(_T("充值成功"));
			CFile file;
			file.Open(_T("history.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
			file.SeekToEnd();
			CString str, MoneyT;
			CTime t;
			MoneyT.Format(_T("%ld"), money);
			t = CTime::GetCurrentTime();
			str = t.Format("%Y/%m/%d %X");
			str += _T(" UID:") + uid;
			str += _T(" add: ") + Money;
			str += _T(" total: ") + MoneyT + _T("\r\n");
			file.Write(CStringA(str), strlen(CStringA(str)));
			file.Close();
			mlhistory.InsertString(mlhistory.GetCount(), str);
			qurey.Format(_T("UPDATE Money SET Money = Money + %s WHERE cid = '%s' AND sen ='%s' AND blk ='%s'"), Money,uid, sen, blk);
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
}


void CMoney::OnBnClickedButtonSubMoney()
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
	if (meSub.GetWindowTextLength() == 0) {
		meStatus.SetWindowText(_T("请输入金额"));
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
	qurey.Format(_T("SELECT * FROM Money WHERE cid = '%s' AND sen ='%s' AND blk ='%s'"), uid,sen,blk);
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

	LONG money=0;//读取余额
	int status = 0 -read_account(sens, blks, key_type, keyc, &money);
	if (status) {
		CString hits(hit.error_hit[status].c_str());
		meStatus.SetWindowText(hits);
		return;
	}
	else {
		CString Money;
		meSub.GetWindowText(Money);
		LONG tmp(_ttol(Money));
		money -= tmp; //充值时此处为+
		if (money < 0) {
			meStatus.SetWindowText(_T("余额不足"));
			return;
		}
		status = 0-write_account(sens, blks, key_type, keyc, money);//消费
		if (status) {
			CString hits(hit.error_hit[status].c_str());
			meStatus.SetWindowText(hits);
			return;
		}
		else {
			meStatus.SetWindowText(_T("消费成功"));
			CFile file;
			file.Open(_T("history.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate); 
			file.SeekToEnd();
			CString str,MoneyT;
			CTime t;
			MoneyT.Format(_T("%ld"), money);
			t = CTime::GetCurrentTime();
			str = t.Format("%Y/%m/%d %X");
			str += _T(" UID:") + uid;
			str += _T(" use:") + Money;
			str += _T(" total:") + MoneyT + _T("\r\n");
			file.Write(CStringA(str), strlen(CStringA(str)));
			file.Close();
			mlhistory.InsertString(mlhistory.GetCount(), str);
			qurey.Format(_T("UPDATE Money SET Money = Money - %s WHERE cid = '%s' AND sen ='%s' AND blk ='%s'"), Money, uid, sen, blk);
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

}


void CMoney::OnBnClickedButtonInit()
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
	if (meMoney.GetWindowTextLength() == 0) {
		meStatus.SetWindowText(_T("请输入金额"));
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
	meMoney.GetWindowText(tmp); //读取输入金额
	LONG money(_ttol(tmp));
	int status = 0 -write_account(sens, blks, key_type, keyc, money);//写入
	if (status) {
		CString hits(hit.error_hit[status].c_str());
		meStatus.SetWindowText(hits);
	}
	else {
		meStatus.SetWindowText(_T("初始化成功"));
		CFile file;
		file.Open(_T("history.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate); //打开文件
		file.SeekToEnd();//移到末尾
		CString str,query;
		CTime t; 
		t = CTime::GetCurrentTime(); //获取时间
		str = t.Format("%Y/%m/%d %X");
		str += _T(" UID:")+ uid;//设置输入信息
		str += _T(" Init:") + tmp +_T("\r\n");
		file.Write(CStringA(str), strlen(CStringA(str)));//写入
		file.Close();//关闭
		mlhistory.InsertString(mlhistory.GetCount(), str);//添加到历史记录中
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


void CMoney::OnBnClickedButtonHisLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	CStdioFile  file;
	file.Open(_T("history.txt"), CFile::modeRead | CFile::typeText);
	CString his; 
	while (file.ReadString(his)) {//分行读取
		mlhistory.AddString(his);
	}

}


void CMoney::OnBnClickedButtonHisClean()
{
	// TODO: 在此添加控件通知处理程序代码
	CFile file;
	file.Open(_T("history.txt"), CFile::modeCreate | CFile::modeWrite );
	file.Close();
	mlhistory.ResetContent();
}

BOOL CMoney::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (meAdd.GetFocus()|| meSub.GetFocus() || meMoney.GetFocus()) {
		short nks = GetKeyState(VK_CONTROL);
		if (nks & 0x8000) {
			return CDialog::PreTranslateMessage(pMsg);
		}

		//检查输入的内容
		if ((pMsg->wParam >= 0x30 && pMsg->wParam <= 0x39)|| pMsg->wParam <= 0x08) {
			return CDialog::PreTranslateMessage(pMsg);
		}
		else {
			MessageBeep(-1);
			pMsg->wParam = NULL;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

 /*//历史记录数据库加载，溯源到 卡的某个扇区的某个块目前考虑到展示文件读写 暂未合并
void CMoney::OnBnClickedButtonHisLoad()
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
		meStatus.SetWindowText(_T("数据库中不存在历史记录"));
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