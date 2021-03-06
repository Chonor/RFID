// CUserInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "RFID.h"
#include "CUserInfo.h"
#include "afxdialogex.h"


// CUserInfo 对话框

IMPLEMENT_DYNAMIC(CUserInfo, CDialog)

CUserInfo::CUserInfo(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CUserInfo, pParent)
{
	
}

CUserInfo::~CUserInfo()
{
}

void CUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_UIDS, meUid);
	DDX_Control(pDX, IDC_EDIT_UNAME, meUname);
	DDX_Control(pDX, IDC_EDIT_COLLEGE, meCollege);
	DDX_Control(pDX, IDC_EDIT_USER_S, meStatus);
}


BEGIN_MESSAGE_MAP(CUserInfo, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CUserInfo::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, &CUserInfo::OnBnClickedButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CUserInfo::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CUserInfo 消息处理程序


void CUserInfo::OnBnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码

	if (cid.GetLength() == 0) {
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
	else {
		CRecordset rs(&db);
		CString str;
		if (!cid.GetLength()) {//判断是否获取到卡片UID
			meStatus.SetWindowText(_T("请获取卡片UID"));
			return;
		}
		//构建查询语句，此处为了区别userid 使用cid代替卡片UID
		str.Format(_T("SELECT * FROM Users WHERE cid = '%s'"),cid);
		rs.Open(CRecordset::forwardOnly, str);//接收结果
		if (rs.IsEOF()) {//没有查询到任何信息
			meStatus.SetWindowText(_T("用户信息不存在"));
		}
		else {//查询成功，展示信息
			CString id, name, college;
			rs.GetFieldValue(_T("uid"), id);
			rs.GetFieldValue(_T("uname"), name);
			rs.GetFieldValue(_T("college"), college);
			meUid.SetWindowText(id);
			meUname.SetWindowText(name);
			meCollege.SetWindowText(college);
			meStatus.SetWindowText(_T("查询成功"));
		}
		rs.Close();
		db.Close();
		return;
	}
}


void CUserInfo::OnBnClickedButtonWrite()
{
	//REPLACE INTO Users(cid, uid, uname, college) VALUES('1234', '12345678', 'test1', 'test')
	// TODO: 在此添加控件通知处理程序代码

	if (cid.GetLength() == 0) {
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
	else {
		CRecordset rs(&db);
		CString str,id,name,college;
		if (!cid.GetLength()) {
			meStatus.SetWindowText(_T("请获取卡片UID"));
			return;
		}
		meUid.GetWindowText(id);
		meUname.GetWindowText(name);
		meCollege.GetWindowText(college);
		if (id.GetLength() == 0) {
			meStatus.SetWindowText(_T("请输入学号"));
			return;
		}
		if (name.GetLength() == 0) {
			meStatus.SetWindowText(_T("请输入姓名"));
			return;
		}
		if (college.GetLength() == 0) {
			meStatus.SetWindowText(_T("请输入学院"));
			return;
		}
		str.Format(_T("REPLACE INTO Users(cid, uid, uname, college) VALUES('%s', '%s', '%s', '%s')"), cid,id,name,college);
		try{
			db.ExecuteSQL(str);
		}
		catch (CDBException *e){
			e->ReportError();  //报告异常原因，如主键异常
			e->Delete();
			db.Close();
			return;
		}
		catch (CMemoryException *e){
			MessageBox(_T("数据库内存异常!"));
			e->Delete();
			return;
		}
		catch (...){
			MessageBox(_T("数据库其它异常!"));
			return;
		}
		meStatus.SetWindowText(_T("更新成功"));
		db.Close();
		return;
	}
}


void CUserInfo::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	meUid.SetWindowText(_T(""));
	meUname.SetWindowText(_T(""));
	meCollege.SetWindowText(_T(""));
	meStatus.SetWindowText(_T("清理成功"));
}
