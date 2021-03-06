#pragma once
#include"CHit.h"

// CRnW 对话框

class CRnW : public CDialog
{
	DECLARE_DYNAMIC(CRnW)

public:
	CRnW(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRnW();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CRnW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString key, sen, blk;
	unsigned char key_type;
	CButton  mbRSen, mbRBlock, mbWBlock,mbClean;
	CEdit  meBlock0, meBlock1, meBlock2, meBlock3_1, meBlock3_2, meBlock3_3, meStatus;
	Hits hit;
	afx_msg void OnBnClickedButtonRSen();
	afx_msg void OnBnClickedButtonRBlock();
	afx_msg void OnBnClickedButtonWBlock();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonRClear();
};
