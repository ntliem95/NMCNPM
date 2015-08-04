#pragma once
#include "afxwin.h"


// StudentDlg dialog

class StudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(StudentDlg)

public:
	StudentDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~StudentDlg();

// Dialog Data
	enum { IDD = IDD_STUDENT };

protected:
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
	afx_msg void OnPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	BOOL OnEraseBkgnd(CDC * pDC);
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStudentChangepass();
	afx_msg void OnBnClickedStudentEditinfo();
	afx_msg void OnBnClickedStudentSignout();
	CLabel Greeting;
	HICON m_hIcon;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();

	CButton * SignOutButton;
	CBitmapButton SignOut;
	CButton * ChangePassButton;
	CBitmapButton ChangePass;
	CButton * EditInfoButton;
	CBitmapButton EditInfo;
	CButton * StudentRatingButton;
	CBitmapButton StudentRating;
	CButton * EvaluateTeacherButton;
	CBitmapButton EvaluateTeacher;
	CButton * LearningButton;
	CBitmapButton Learning;
	CButton * Test4SkillButton;
	CBitmapButton Test4Skill;
	void SetButton();
};

extern StudentDlg * CurStudent;