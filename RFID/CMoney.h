#pragma once
#include"CHit.h"

// CMoney 对话框

class CMoney : public CDialog
{
	DECLARE_DYNAMIC(CMoney)

public:
	CMoney(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMoney();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMoney };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString key, sen, blk,uid;
	unsigned char key_type;
	CButton mbInit, mbQuery, mbAdd, mbSub, mbLoad, mbClean;
	CEdit meMoney, meAdd, meSub, meStatus;
	CListBox mlhistory;
	Hits hit;
	afx_msg void OnBnClickedButtonMoney();
	afx_msg void OnBnClickedButtonAddMoney();
	afx_msg void OnBnClickedButtonSubMoney();
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonHisLoad();
	afx_msg void OnBnClickedButtonHisClean();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
