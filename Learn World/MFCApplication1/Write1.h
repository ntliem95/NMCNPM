#pragma once
#include "afxwin.h"


// Write1 dialog

class Write1 : public CDialogEx
{
	DECLARE_DYNAMIC(Write1)

public:
	Write1(CWnd* pParent = NULL);   // standard constructor
	virtual ~Write1();
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
	enum { IDD = IDD_WRITING1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CLabel Title;
	CLabel Note;
	afx_msg void OnBnClickedSample();
	CLabel WordCount;
	int Count;
	CString Content;
	CEdit Edit;
	afx_msg void OnBnClickedW1Finish();
	afx_msg void OnBnClickedW1Back();
	CButton * BackButton;
	CBitmapButton Back;
	CButton * FinishButton;
	CBitmapButton Finish;
	CString Sample;
	afx_msg void OnEnChangeEdit2();
	CString CountWord;
};
extern Write1 * CurWrite1;