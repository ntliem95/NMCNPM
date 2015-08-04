#pragma once
#include "afxwin.h"


// ForgotPass dialog

class ForgotPass : public CDialogEx
{
	DECLARE_DYNAMIC(ForgotPass)

public:
	ForgotPass(CWnd* pParent = NULL);   // standard constructor
	virtual ~ForgotPass()
	{

	}

// Dialog Data
	enum { IDD = IDD_FORGOT_PASS };

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
	LRESULT MessageControl(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	CButton * BackButton;
	CBitmapButton Back;
	CButton * NextButton;
	CBitmapButton Next;
	afx_msg void OnBnClickedForgotBack();
	CString Username;
	CString Email;
	CString NewPassword;
	CString ConfirmPassword;
	afx_msg void OnBnClickedForgotNext();
	void ReturnToPreviousDlg();
	CLabel Step1;
	CLabel Username_TEXT;
	CLabel Phone_Text;
	CLabel Step2;
	CLabel Pass_TEXT;
	CLabel RePass_TEXT;
};

extern ForgotPass * CurForgotPass;