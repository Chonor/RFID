#pragma once


// CAppDev 对话框

class CAppDev : public CDialog
{
	DECLARE_DYNAMIC(CAppDev)

public:
	CAppDev(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAppDev();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAppDev };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CButton m_b_money_init, m_b_money_q, m_b_money_add, m_b_money_sub, m_rba, m_rbb;
	CEdit m_e_money, m_e_money_add, m_e_money_sub, m_e_money_s, m_e_key;
	DECLARE_MESSAGE_MAP()
public:
	
	unsigned char key_type;
	CString keys;
	int blk;
	int sen;
	string error_hit[19];
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonMoney();
	afx_msg void OnBnClickedButtonAddMoney();
	afx_msg void OnBnClickedButtonSubMoney();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
