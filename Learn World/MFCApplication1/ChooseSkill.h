#pragma once
#include "afxwin.h"
// ChooseSkill dialog

class ChooseSkill : public CDialogEx
{
	DECLARE_DYNAMIC(ChooseSkill)

public:
	ChooseSkill(CWnd* pParent = NULL);   // standard constructor
	~ChooseSkill()
	{
		delete WriteButton;
		delete SpeakButton;
		delete ListenButton;
		delete ReadButton;
	}

	virtual void OnFinalRelease();

// Dialog Data
	enum { IDD = IDD_CHOOSESKILL };

protected:
	HICON m_hIcon;
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
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton Write;
	CBitmapButton Read;
	CBitmapButton Listen;
	CBitmapButton Speak;
	CButton *WriteButton;
	CButton *SpeakButton;
	CButton *ListenButton;
	CButton *ReadButton;
	CButton * BackButton;
	CBitmapButton Back;

	afx_msg void OnBnClickedWrite();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedListen();
	afx_msg void OnBnClickedSpeak();
	afx_msg void OnBnClickedRead();
};

extern ChooseSkill * CurChooseSkills;