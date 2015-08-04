#pragma once
#include "afxwin.h"


// Read1 dialog

class Read1 : public CDialogEx
{
	DECLARE_DYNAMIC(Read1)

public:
	Read1(CWnd* pParent = NULL);   // standard constructor
	virtual ~Read1();
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
	enum { IDD = IDD_READING1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CButton * BackButton;
	CBitmapButton Back;
	CButton * CheckButton;
	CBitmapButton Check;
	CEdit Paragraph;
	CLabel Title;
	CLabel True;
	CLabel False;
	CLabel Not;
	CString Content;
	CComboBox A1;
	CComboBox A2;
	CComboBox A3;
	CComboBox A4;
	CComboBox A5;
	afx_msg void OnBnClickedR1Check();
	afx_msg void OnBnClickedR1Back();
	afx_msg void OnCbnSelchangeA1();
	afx_msg void OnCbnSelchangeA2();
	afx_msg void OnCbnSelchangeA3();
	afx_msg void OnCbnSelchangeA4();
	afx_msg void OnCbnSelchangeA5();
	CLabel C1;
	CLabel C2;
	CLabel C3;
	CLabel C4;
	CLabel C5;
};
extern Read1 * CurRead1;