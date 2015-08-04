#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// DeleteAccountDlg dialog

class DeleteAccountDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteAccountDlg)

public:
	DeleteAccountDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~DeleteAccountDlg();
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
	enum { IDD = IDD_DELETE_ACCOUNT };

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
	CButton * BackButton;
	CBitmapButton Back;
	CListCtrl ListView;
	void AddListTable(CString &A);
	int TableSize;
	afx_msg void OnBnClickedDeleteAccount();
	afx_msg void OnEnChangeSearch();
	CString SearchKey;
	afx_msg void OnBnClickedDeleteBack();
	afx_msg void OnBnClickedDeactivateAccount();
	afx_msg void OnBnClickedActivateAccount();
	CLabel Search;
	CLabel AccountList;
};
extern DeleteAccountDlg * CurDelete;