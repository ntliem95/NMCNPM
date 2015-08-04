#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// EvaluateDlg dialog

class EvaluateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EvaluateDlg)

public:
	EvaluateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~EvaluateDlg();
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
	HICON m_hIcon;
// Dialog Data
	enum { IDD = IDD_EVALUATE_TEACHER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	LRESULT MessageControl(WPARAM wParam, LPARAM lParam);
	BOOL OnInitDialog();
	void OnPaint();
	BOOL OnEraseBkgnd(CDC * pDC);
	void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	int  nItem = -1;
	int nRating;
	int newRating;
	CButton * BackButton;
	CBitmapButton Back;
	CButton * FinishButton;
	CBitmapButton Finish;
	void AddListTable(CString &A);
	int TableSize;
	CListCtrl ListView;
	CString SearchKey;
	afx_msg void OnBnClickedDeleteBack();
	afx_msg void OnEnChangeSearch();
	CLabel Rating;
	CLabel  AccountList;
	CLabel  Search;
	afx_msg void OnHdnItemclickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedConfirm();
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
};
extern EvaluateDlg * CurEvaluate;