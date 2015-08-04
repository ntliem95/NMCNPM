#pragma once
#include "afxwin.h"


// EditInfoDlg dialog

class EditInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditInfoDlg)

public:
	EditInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~EditInfoDlg();

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
	enum { IDD = IDD_EDITINFO };
	HICON m_hIcon;
	CButton * BackButton;
	CBitmapButton Back;
	CButton * FinishButton;
	CBitmapButton Finish;
	void ReturnToPreviousDlg();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString EDITINFO_Name;
	CString EDITINFO_Add;
	CString EDITINFO_Phone;
	CString EDITINFO_Gender;
	CLabel Name;
	CLabel Address;
	CLabel Date;
	CLabel Phone;
	CLabel Note;
	afx_msg void OnBnClickedEditinfoFemale();
	afx_msg void OnBnClickedEditinfoMale();
	void AddString2ComboBox();
	
	afx_msg void OnBnClickedEditinfoFinish();
	afx_msg void OnBnClickedEditinfoBack();
	CComboBox DayBox;
	CComboBox MonthBox;
	CComboBox YearBox;
};
extern EditInfoDlg * CurEditInfo;