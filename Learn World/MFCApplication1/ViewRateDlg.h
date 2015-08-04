#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// ViewRateDlg dialog

class ViewRateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ViewRateDlg)

public:
	ViewRateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ViewRateDlg();
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
	enum { IDD = IDD_VIEWRATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	LRESULT MessageControl(WPARAM wParam, LPARAM lParam);
	BOOL OnInitDialog();
	void OnPaint();
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
	CString SearchKey;
	afx_msg void OnEnChangeSearch();
	afx_msg void OnBnClickedViewRateBack();
	CLabel AccountList;
	CLabel Search;
};

extern ViewRateDlg * CurViewRate;