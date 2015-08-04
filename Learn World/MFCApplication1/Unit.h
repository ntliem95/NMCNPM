#pragma once
#include "afxwin.h"


// Unit dialog

class Unit : public CDialogEx
{
	DECLARE_DYNAMIC(Unit)

public:
	Unit(CWnd* pParent = NULL);   // standard constructor
	virtual ~Unit();

	virtual void OnFinalRelease();
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
// Dialog Data
	enum { IDD = IDD_UNIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void LoadNote();
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

public:
	int m_nCurHeight;
	int m_nScrollPos;
	CRect m_rect;
	CButton Unit1;
	CButton Unit2;
	CButton Unit3;
	CButton Unit4;
	CButton Unit5;
	afx_msg void OnBnClickedUnit1();
	afx_msg void OnBnClickedUnit2();
	afx_msg void OnBnClickedUnit3();
	afx_msg void OnBnClickedUnit4();
	afx_msg void OnBnClickedUnit5();
};
extern Unit * CurUnit;