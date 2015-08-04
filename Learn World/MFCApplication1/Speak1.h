#pragma once
#include "afxwin.h"


// Speak1 dialog

class Speak1 : public CDialogEx
{
	DECLARE_DYNAMIC(Speak1)

public:
	Speak1(CWnd* pParent = NULL);   // standard constructor
	virtual ~Speak1();
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
	enum { IDD = IDD_SPEAK1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CString Content;
	CLabel Title;
	CLabel Should;
	CLabel Sample;
	CButton * BackButton;
	CBitmapButton Back;
	afx_msg void OnBnClickedS1Back();
};
extern Speak1 * CurSpeak1;
