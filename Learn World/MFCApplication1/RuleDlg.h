#pragma once
#include "LearnWorld.h"
#include "afxwin.h"
// RuleDlg dialog


class RuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RuleDlg)

public:
	RuleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~RuleDlg()
	{
		
	}

// Dialog Data
	enum { IDD = IDD_RULE };

protected:
	HICON m_hIcon;
	void OnOK(){}
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		switch (pMsg->message)
		{
		case WM_KEYDOWN:

			switch (pMsg->wParam)
			{
			case VK_ESCAPE:
			case VK_CANCEL: return true;
			}
			break;
		}

		return CDialog::PreTranslateMessage(pMsg);
	}

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRuleBack();
	CButton * BackButton;
	CBitmapButton Back;
	CString Terms;
	CEdit check;
	CLabel label;
};
extern RuleDlg * CurRULE;