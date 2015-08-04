#pragma once
#include "afxwin.h"


// AddTeacher dialog

class AddTeacher : public CDialogEx
{
	DECLARE_DYNAMIC(AddTeacher)

public:
	AddTeacher(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddTeacher();
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

	HICON m_hIcon;
// Dialog Data
	enum { IDD = IDD_ADDTEACHER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	LRESULT MessageControl(WPARAM wParam, LPARAM lParam);
	BOOL OnInitDialog();
	BOOL OnEraseBkgnd(CDC * pDC);
	void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedAddteacherFinish();
	afx_msg void OnBnClickedAddteacherBack();
	afx_msg void OnBnClickedEditinfoMale();
	afx_msg void OnBnClickedEditinfoFemale();
	void AddString2ComboBox();
	CButton * BackButton;
	CBitmapButton Back;
	CButton * FinishButton;
	CBitmapButton Finish;
	CLabel user;
	CLabel pass;
	CLabel name;
	CLabel add;
	CLabel date;
	CLabel phone;
	CComboBox MonthBox;
	CComboBox DayBox;
	CComboBox YearBox;
	CString Phone;
	CString Add;
	CString Name;
	CString Pass;
	CString User;
	CString Gender;
};
extern AddTeacher * CurAddTeacher;