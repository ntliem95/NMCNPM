#pragma once
#include "afxwin.h"
#include "ocx1.h"
#include <wmp.h>
#include "CWMPPlayer4.h"

// Listen1 dialog

class Listen1 : public CDialogEx
{
	DECLARE_DYNAMIC(Listen1)

public:
	Listen1(CWnd* pParent = NULL);   // standard constructor
	virtual ~Listen1();
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
	enum { IDD = IDD_LISTEN1 };

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
	afx_msg void OnBnClickedL1Check();
	afx_msg void OnBnClickedL1Back();
	int Choice[5]; // 1 , 2 , 3  ; 0 = no choice
	afx_msg void OnBnClickedAnswer11();
	afx_msg void OnBnClickedAnswer12();
	afx_msg void OnBnClickedAnswer13();
	afx_msg void OnBnClickedAnswer21();
	afx_msg void OnBnClickedAnswer22();
	afx_msg void OnBnClickedAnswer23();
	afx_msg void OnBnClickedAnswer31();
	afx_msg void OnBnClickedAnswer32();
	afx_msg void OnBnClickedAnswer33();
	afx_msg void OnBnClickedAnswer41();
	afx_msg void OnBnClickedAnswer42();
	afx_msg void OnBnClickedAnswer43();
	afx_msg void OnBnClickedAnswer51();
	afx_msg void OnBnClickedAnswer52();
	afx_msg void OnBnClickedAnswer53();
	CLabel Answer3;
	CLabel Answer2;
	CLabel Answer1;
	CLabel Answer4;
	CLabel Answer5;
	CWMPPlayer4 player;
	CLabel Title;
	CLabel Question1;
	CLabel Question4;
	CLabel Question5;
	CLabel Question2;
	CLabel Question3;
};
extern Listen1* CurListen1;