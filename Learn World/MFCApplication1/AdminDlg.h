#pragma once
#include "afxwin.h"


// AdminDlg dialog

class AdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AdminDlg)

public:
	AdminDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AdminDlg();
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
	enum { IDD = IDD_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	BOOL AdminDlg::OnEraseBkgnd(CDC * pDC);
	afx_msg void OnDestroy();
	void OnPaint();
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	HICON m_hIcon;
	afx_msg void OnBnClickedAdminSignout();
	afx_msg void OnBnClickedAdminChangepass();
	afx_msg void OnBnClickedAdminEditinfo();
	CLabel Greeting;
	afx_msg void OnBnClickedAdminTeacher();
	afx_msg void OnBnClickedAdminDelete();
	afx_msg void OnBnClickedViewTeacher();
	afx_msg void OnBnClickedViewStudent();
	afx_msg void OnBnClickedEvaluateTeacher();

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

extern AdminDlg * CurAdmin;