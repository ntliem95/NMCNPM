#pragma once
#include "afxwin.h"


// TeacherDlg dialog

class TeacherDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TeacherDlg)

public:
	TeacherDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~TeacherDlg();
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
	virtual void OnFinalRelease();

// Dialog Data
	enum { IDD = IDD_TEACHER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	BOOL OnEraseBkgnd(CDC * pDC);
	void OnPaint();
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	HICON m_hIcon;
	afx_msg void OnBnClickedTeacherChangepass();
	CLabel Greeting;
	afx_msg void OnBnClickedTeacherSignout();
	afx_msg void OnBnClickedTeacherEditinfo();
	afx_msg void OnBnClickedButton4();

	CButton * SignOutButton;
	CBitmapButton SignOut;
	CButton * ChangePassButton;
	CBitmapButton ChangePass;
	CButton * EditInfoButton;
	CBitmapButton EditInfo;
	CButton * StudentRatingButton;
	CBitmapButton StudentRating;
	CButton * TeacherRatingButton;
	CBitmapButton TeacherRating;
	CButton * AddTeacherButton;
	CBitmapButton AddTeacherBtt;
	CButton * DeleteAccountButton;
	CBitmapButton DeleteAccount;
	CButton * EvaluateTeacherButton;
	CBitmapButton EvaluateTeacher;
	void SetButton();
};
extern TeacherDlg * CurTeacher;