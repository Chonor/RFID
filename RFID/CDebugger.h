#pragma once


// CDebugger 对话框

class CDebugger : public CDialog
{
	DECLARE_DYNAMIC(CDebugger)

public:
	CDebugger(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDebugger();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDebugger };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CButton m_b_start,m_b_version,m_b_uid,m_b_set,m_b_key,m_b_r_sen,m_b_r_block,m_b_w_block,m_rba,m_rbb;
	CEdit m_e_start, m_e_version, m_e_uid, m_e_info, m_e_led_info, m_e_led_dig, m_e_led_s, m_e_key, m_e_block0, m_e_block1, m_e_block2, m_e_block3_1, m_e_block3_2, m_e_block3_3, m_e_rnw_s;
	CComboBox m_cb_sen, m_cb_block;
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnBnClickedRadioKey();
	unsigned char key_type;
	bool power;
	string error_hit[19];
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonUid();
	afx_msg void OnBnClickedButtonVersion();
	afx_msg void OnBnClickedButtonKey();
	afx_msg void OnBnClickedButtonRClear();
	afx_msg void OnBnClickedButtonRSen();
	afx_msg void OnBnClickedButtonRBlock();
	afx_msg void OnBnClickedButtonWBlock();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
