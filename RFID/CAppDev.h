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

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
};
