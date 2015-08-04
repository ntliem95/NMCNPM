
// SignInDlg.h : header file
//

#pragma once

#include "LearnWorld.h"
#include "afxbutton.h"
#include "afxcmn.h"
#include "afxwin.h"


class SignInDlg : public CDialogEx
{
//DECLARE_DYNAMIC(SignInDlg)
// Construction
public:
	SignInDlg(CWnd* pParent = NULL);	// standard constructor
	 ~SignInDlg()
	{
		//this->DestroyWindow();
	}
// Dialog Data
	enum { IDD = IDD_SIGNIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	void OnOK()
	{
	}
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

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	afx_msg void OnDestroy();
	LRESULT MessageControl(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSignin();
	afx_msg void OnNMClickForgotPass(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTerms(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSigninRegister();
	//Sign In
	CString ID;
	CString Password;
	CButton * SignInButton;
	CBitmapButton SignIn;
	//////////////////////////////////////////

	//Create Account
	CLabel Label_Register;
	CButton * RegisterButton;
	CBitmapButton Register;
	CComboBox MonthBox;
	CComboBox DayBox;
	CComboBox YearBox;
	CString Register_Username;
	CString Register_Name;
	CString Register_Pass;
	CString Register_RePass;
	CString Register_Add;
	CString Register_Phone;
	CString Register_Gender;
	void AddString2ComboBox();
	//////////////////////////////////////////

	//Forget password

	//////////////////////////////////////////

	afx_msg void OnBnClickedGenderMale();
	afx_msg void OnBnClickedGenderFemale();
	void SetTextDlg();
	CLabel TEXT_ID;
	CLabel TEXT_PASSWORD;
	CLabel TEXT_TERM;
	CLabel TEXT_GENDER;
	CLabel TEXT_DATE;
	CLabel TEXT_PHONE;
	CLabel TEXT_ADD;
	CLabel TEXT_PASS2;
	CLabel TEXT_PASS1;
	CLabel TEXT_USER;
	CLabel TEXT_NAME;
	CProgressCtrl test;
};
extern SignInDlg * CurSIGNIN;