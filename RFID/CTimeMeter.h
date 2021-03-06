#pragma once

#include "CHit.h"
// CTimeMeter 对话框

class CTimeMeter : public CDialog
{
	DECLARE_DYNAMIC(CTimeMeter)

public:
	CTimeMeter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTimeMeter();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTimeMeter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString key, sen, blk, uid;
	unsigned char key_type;
	Hits hit;
	CEdit meHour1, meHour2, meMin1, meMin2, meSec1, meSec2, meStatus;
	CButton mbStart;
	CListBox mlhistory;
	bool start;
	int cnt;
	afx_msg void OnBnClickedButtonTime();
	afx_msg void OnBnClickedButtonTimeinit();
	afx_msg void OnBnClickedButtonUse();
	afx_msg void OnBnClickedButtonAddTime();
	afx_msg void OnBnClickedButtonHisClean2();
	afx_msg void OnBnClickedButtonHisLoad2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
