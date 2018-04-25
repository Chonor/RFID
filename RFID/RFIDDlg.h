
// RFIDDlg.h: 头文件
//

#pragma once
#include "CAppDev.h"
#include "CDebugger.h"
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
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_tabs;
	CDebugger m_debug;
	CAppDev m_app;
};
