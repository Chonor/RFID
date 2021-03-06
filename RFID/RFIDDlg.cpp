
// RFIDDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "RFID.h"
#include "RFIDDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRFIDDlg 对话框



CRFIDDlg::CRFIDDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_RFID_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRFIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabs);
	DDX_Control(pDX, IDC_EDIT_START, meStatus);
	DDX_Control(pDX, IDC_EDIT_VERSION, meVersion);
	DDX_Control(pDX, IDC_EDIT_UID, meUid);
	DDX_Control(pDX, IDC_EDIT_KEY, meKey);
	DDX_Control(pDX, IDC_BUTTON_START, mbStart);
	DDX_Control(pDX, IDC_BUTTON_VERSION, mbVersion);
	DDX_Control(pDX, IDC_BUTTON_UID, mbUid);
	DDX_Control(pDX, IDC_BUTTON_KEY,mbDefault);
	DDX_Control(pDX, IDC_BUTTON_CLEAN, mbClean);
	DDX_Control(pDX, IDC_RADIO_KEYA, mrbA);
	DDX_Control(pDX, IDC_RADIO_KEYB, mrbB);
	DDX_Control(pDX, IDC_COMBO_SEN, mcbSen);
	DDX_Control(pDX, IDC_COMBO_BLOCK, mcbBlock);
}

BEGIN_MESSAGE_MAP(CRFIDDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CRFIDDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON_START, &CRFIDDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_VERSION, &CRFIDDlg::OnBnClickedButtonVersion)
	ON_BN_CLICKED(IDC_BUTTON_UID, &CRFIDDlg::OnBnClickedButtonUid)
	ON_BN_CLICKED(IDC_RADIO_KEYA, &CRFIDDlg::OnBnClickedRadioKeya)
	ON_BN_CLICKED(IDC_RADIO_KEYB, &CRFIDDlg::OnBnClickedRadioKeyb)
	ON_BN_CLICKED(IDC_BUTTON_KEY, &CRFIDDlg::OnBnClickedButtonKey)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CRFIDDlg::OnBnClickedButtonClean)
	ON_CBN_KILLFOCUS(IDC_COMBO_SEN, &CRFIDDlg::OnCbnKillfocusComboSen)
	ON_CBN_KILLFOCUS(IDC_COMBO_BLOCK, &CRFIDDlg::OnCbnKillfocusComboBlock)
	ON_EN_KILLFOCUS(IDC_EDIT_KEY, &CRFIDDlg::OnEnKillfocusEditKey)
END_MESSAGE_MAP()


// CRFIDDlg 消息处理程序

BOOL CRFIDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDD_ABOUTBOX);
		//ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	power = false;
	key_type = 0x00;
	meKey.SetLimitText(12);

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	SetWindowText(_T("RFID"));//即可
	m_tabs.InsertItem(0, _T("读写操作"));
	m_tabs.InsertItem(1, _T("电子钱包"));
	m_tabs.InsertItem(2, _T("用户信息"));
	m_tabs.InsertItem(3, _T("计时系统"));
	m_rnw.Create(IDD_CRnW, GetDlgItem(IDD_RFID_DIALOG));
	m_money.Create(IDD_CMoney, GetDlgItem(IDD_RFID_DIALOG));
	m_user.Create(IDD_CUserInfo, GetDlgItem(IDD_RFID_DIALOG));
	m_time.Create(IDD_CTimeMeter, GetDlgItem(IDD_RFID_DIALOG));
	//设置子窗口位置
	CRect rc;
	m_tabs.GetClientRect(rc);
	rc.top += 145;
	rc.right +=9;
	rc.bottom += 125;
	rc.left += 9;
	//设置显示
	m_rnw.MoveWindow(&rc);
	m_rnw.ShowWindow(true);
	m_money.MoveWindow(&rc);
	m_money.ShowWindow(false);
	m_user.MoveWindow(&rc);
	m_user.ShowWindow(false);
	m_time.MoveWindow(&rc);
	m_time.ShowWindow(false);
	m_tabs.SetCurSel(0);
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRFIDDlg::synchronous()
{
	CString key, sen, blk,uid;
	meKey.GetWindowText(key);
	mcbSen.GetWindowText(sen);
	mcbBlock.GetWindowText(blk);
	meUid.GetWindowText(uid);
	//uid = _T("403D95");
	m_rnw.blk = blk;
	m_rnw.sen = sen;
	m_rnw.key_type = key_type;
	m_rnw.key = key;

	m_money.blk = blk;
	m_money.sen = sen;
	m_money.key_type = key_type;
	m_money.key = key;
	m_money.uid = uid;

	m_user.cid = uid;

	m_time.blk = blk;
	m_time.sen = sen;
	m_time.key_type = key_type;
	m_time.key = key;
	m_time.uid = uid;
}

void CRFIDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRFIDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRFIDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRFIDDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int cursel = m_tabs.GetCurSel();
	if (cursel == 0)
	{
		m_rnw.ShowWindow(true);
		m_money.ShowWindow(false);
		m_user.ShowWindow(false);
		m_time.ShowWindow(false);
	}
	else if(cursel==1){
		m_rnw.ShowWindow(false);
		m_money.ShowWindow(true);
		m_user.ShowWindow(false);
		m_time.ShowWindow(false);

	}
	else if(cursel==2) {
		m_rnw.ShowWindow(false);
		m_money.ShowWindow(false);
		m_user.ShowWindow(true);
		m_time.ShowWindow(false);
	}
	else {
		m_rnw.ShowWindow(false);
		m_money.ShowWindow(false);
		m_user.ShowWindow(false);
		m_time.ShowWindow(true);
	}
	synchronous();

}


void CRFIDDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	Hits hits;
	if (power) {
		int start = 0 - IDD_PowerOff();
		CString hits(hits.error_hit[start].c_str());
		meStatus.SetWindowText(hits);
		if (!start) {
			mbStart.SetWindowText(_T("开启"));
			power = false;
		}
	}
	else {
		int start = 0 - IDD_PowerOn();
		CString hits(hits.error_hit[start].c_str());
		meStatus.SetWindowText(hits);
		if (!start) {
			mbStart.SetWindowText(_T("关闭"));
			power = true;
		}
	}
}


void CRFIDDlg::OnBnClickedButtonVersion()
{
	// TODO: 在此添加控件通知处理程序代码
	Hits hits;
	unsigned char version[50];
	int version_len;
	int status = 0 - Reader_Version(version, &version_len);
	if (status) { //是否读取成功
		CString hits(hits.error_hit[status].c_str());
		meVersion.SetWindowText(hits);
	}
	else {
		CString Ver, tmp;
		for (int i = 0; i < version_len; i++) {//16进制转换
			tmp.Format(_T("%02X"), version[i]);
			Ver += tmp;
		}
		meVersion.SetWindowText(Ver);
	}
}


void CRFIDDlg::OnBnClickedButtonUid()
{
	// TODO: 在此添加控件通知处理程序代码
	Hits hits;
	unsigned char uid[50];
	int uid_len;
	int status = 0 - find_14443(uid, &uid_len);
	if (status) {//判断是否读取成功
		CString hits(hits.error_hit[status].c_str());
		meUid.SetWindowText(hits);
	}
	else {
		CString Uid, tmp;
		for (int i = 0; i < uid_len; i++) { //转换
			tmp.Format(_T("%02X"), uid[i]);
			Uid += tmp;
		}
		meStatus.SetWindowText(_T("开启成功"));
		mbStart.SetWindowText(_T("关闭"));
		power = true;
		
		meUid.SetWindowText(Uid);
		synchronous();						//同步功能，向子界面同步UID
	}
}


void CRFIDDlg::OnBnClickedRadioKeya()
{
	// TODO: 在此添加控件通知处理程序代码
	key_type = 0x0A;
	synchronous();
}


void CRFIDDlg::OnBnClickedRadioKeyb()
{
	// TODO: 在此添加控件通知处理程序代码
	key_type = 0x0B;
	synchronous();
}


void CRFIDDlg::OnBnClickedButtonKey()
{
	// TODO: 在此添加控件通知处理程序代码
	meKey.SetWindowText(_T("FFFFFFFFFFFF"));
	mrbA.SetCheck(0);
	mrbB.SetCheck(1);
	key_type = 0x0B;
	synchronous();
}


void CRFIDDlg::OnBnClickedButtonClean()
{
	// TODO: 在此添加控件通知处理程序代码
	meKey.SetWindowText(_T(""));
	mrbA.SetCheck(0);
	mrbB.SetCheck(0);
	key_type = 0;
	synchronous();
}


void CRFIDDlg::OnCbnKillfocusComboSen()
{
	// TODO: 在此添加控件通知处理程序代码
	synchronous();
}


void CRFIDDlg::OnCbnKillfocusComboBlock()
{
	// TODO: 在此添加控件通知处理程序代码
	synchronous();
}


void CRFIDDlg::OnEnKillfocusEditKey()
{
	// TODO: 在此添加控件通知处理程序代码
	synchronous();
}

BOOL CRFIDDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (meKey.GetFocus()) {
		short nks = GetKeyState(VK_CONTROL);
		if (nks & 0x8000) {
			return CDialog::PreTranslateMessage(pMsg);
		}

		//检查输入的内容
		if ((pMsg->wParam >= 0x30 && pMsg->wParam <= 0x39) ||
			(pMsg->wParam >= 'a' && pMsg->wParam <= 'f') ||
			(pMsg->wParam >= 'A' && pMsg->wParam <= 'F') ||
			(pMsg->wParam == 0x08) ||
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
