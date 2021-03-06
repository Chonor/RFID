
// RFIDDlg.h: 头文件
//

#pragma once
#include "CRnW.h"
#include "CMoney.h"
#include"CHit.h"
#include"CUserInfo.h"
#include"CTimeMeter.h"
// CRFIDDlg 对话框
class CRFIDDlg : public CDialog
{
// 构造
public:
	CRFIDDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RFID_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	
// 实现
protected:
    HICON m_hIcon;
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	void synchronous();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_tabs;
	CRnW m_rnw;
	CMoney m_money;
	CUserInfo m_user;
	CTimeMeter m_time;
	CString keys;
	CButton mbStart, mbVersion, mbUid, mrbA, mrbB, mbDefault, mbClean;
	CEdit meStatus, meVersion, meUid, meKey;
	CComboBox mcbSen, mcbBlock;
	bool power;
	unsigned char key_type;
	
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonVersion();
	afx_msg void OnBnClickedButtonUid();
	afx_msg void OnBnClickedRadioKeya();
	afx_msg void OnBnClickedRadioKeyb();
	afx_msg void OnBnClickedButtonKey();
	afx_msg void OnBnClickedButtonClean();
	afx_msg void OnCbnKillfocusComboSen();
	afx_msg void OnCbnKillfocusComboBlock();
	afx_msg void OnEnKillfocusEditKey();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
};
