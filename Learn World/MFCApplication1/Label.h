#if !defined(AFX_LABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
#define AFX_LABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Label.h : header file
//
//CLabel& SetBkColor(COLORREF crBkgnd) 	Set the background colour of the control
//CLabel& SetText(const CString& strText) 	Sets the text of the controls
//CLabel& SetTextColor(COLORREF crText) 	Sets the text colour of the control
//CLabel& SetFontBold(BOOL bBold) 	Toggles the state of the bold attribute of the text in the control
//CLabel& SetFontName(const CString& strFont) 	The the fonts face name in the control
//CLabel& SetFontUnderline(BOOL bSet) 	Toggles the state of the underline font attribute of the control
//CLabel& SetFontItalic(BOOL bSet) 	Toggles the state of the italic font attribute of the control
//CLabel& SetFontSize(int nSize) 	Sets the fonts size in points.
//CLabel& SetSunken(BOOL bSet) 	Toggles the state of the sunken attribue of the control
//CLabel& SetBorder(BOOL bSet) 	Toggles the state of the borders attribute
//CLabel& FlashText(BOOL bSet) 	Toggles the state of the text flashing attribute
//CLabel& FlashBackground(BOOL bSet) 	Toggles the state of the text flashing attribute
//CLabel& SetLink(BOOL bLink) 	Toggles the state of the link attribute(allows label to become internet link)
//CLabel& SetLinkCursor(HCURSOR hCursor) 	Sets the cursor for the link.
/////////////////////////////////////////////////////////////////////////////
// CLabel window
enum FlashType {None, Text, Background };

class CLabel : public CStatic
{
// Construction
public:
	CLabel();
	CLabel& SetBkColor(COLORREF crBkgnd);
	CLabel& SetTextColor(COLORREF crText);
	CLabel& SetText(const CString& strText);
	CLabel& SetFontBold(BOOL bBold);
	CLabel& SetFontName(const CString& strFont);
	CLabel& SetFontUnderline(BOOL bSet);
	CLabel& SetFontItalic(BOOL bSet);
	CLabel& SetFontSize(int nSize);
	CLabel& SetSunken(BOOL bSet);
	CLabel& SetBorder(BOOL bSet);
	CLabel& FlashText(BOOL bActivate);
	CLabel& FlashBackground(BOOL bActivate);
	CLabel& SetLink(BOOL bLink);
	CLabel& SetLinkCursor(HCURSOR hCursor);

// Attributes
public:
protected:
	void ReconstructFont();
	COLORREF	m_crText;
	HBRUSH		m_hBrush;
	HBRUSH		m_hwndBrush;
	LOGFONT		m_lf;
	CFont		m_font;
	CString		m_strText;
	BOOL		m_bState;
	BOOL		m_bTimer;
	BOOL		m_bLink;
	FlashType	m_Type;
	HCURSOR		m_hCursor;
			// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabel)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLabel();
	CBitmap m_Bmp;
	// Generated message map functions
protected:
	//{{AFX_MSG(CLabel)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
