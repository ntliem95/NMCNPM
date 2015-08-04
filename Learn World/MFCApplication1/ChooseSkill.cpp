// ChooseSkill.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "ChooseSkill.h"
#include "afxdialogex.h"
#include "StudentDlg.h"
#include "Unit.h"
#define ID_BITBUT 35666
ChooseSkill * CurChooseSkills = NULL;
// ChooseSkill dialog

IMPLEMENT_DYNAMIC(ChooseSkill, CDialogEx)

ChooseSkill::ChooseSkill(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChooseSkill::IDD, pParent)
{

	EnableAutomation();

}

void ChooseSkill::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}
void ChooseSkill::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChooseSkill, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_WRITE, &ChooseSkill::OnBnClickedWrite)
	ON_BN_CLICKED(IDC_BACK, &ChooseSkill::OnBnClickedBack)
	ON_BN_CLICKED(IDC_LISTEN, &ChooseSkill::OnBnClickedListen)
	ON_BN_CLICKED(IDC_SPEAK, &ChooseSkill::OnBnClickedSpeak)
	ON_BN_CLICKED(IDC_READ, &ChooseSkill::OnBnClickedRead)
END_MESSAGE_MAP()


// ChooseSkill message handlers
BOOL ChooseSkill::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	CurChooseSkills = this;

	BackButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_L1_BACK));
	LONG GWLOK = GetWindowLong(BackButton->m_hWnd, GWL_STYLE);
	SetWindowLong(BackButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Back.LoadBitmaps(IDB_BACK, IDB_BACK_PRESSED, 0, 0);
	Back.SubclassDlgItem(IDC_L1_BACK, this);
	Back.SizeToContent();

	WriteButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_WRITE));
	GWLOK = GetWindowLong(WriteButton->m_hWnd, GWL_STYLE);
	SetWindowLong(WriteButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Write.LoadBitmaps(IDB_WRITING, 0,IDB_WRITING_SELECTED,0);
	Write.SubclassDlgItem(IDC_WRITE, this);

	ListenButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_LISTEN));
	GWLOK = GetWindowLong(ListenButton->m_hWnd, GWL_STYLE);
	SetWindowLong(ListenButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Listen.LoadBitmaps(IDB_LISTENING,0, IDB_LISTENING_SELECTED ,0);
	Listen.SubclassDlgItem(IDC_LISTEN, this);

	ReadButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_READ));
	GWLOK = GetWindowLong(ReadButton->m_hWnd, GWL_STYLE);
	SetWindowLong(ReadButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Read.LoadBitmaps(IDB_READING, 0,IDB_READING_SELECTED , 0);
	Read.SubclassDlgItem(IDC_READ, this);

	SpeakButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_SPEAK));
	GWLOK = GetWindowLong(SpeakButton->m_hWnd, GWL_STYLE);
	SetWindowLong(SpeakButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Speak.LoadBitmaps(IDB_SPEAKING,0, IDB_SPEAKING_SELECTED , 0);
	Speak.SubclassDlgItem(IDC_SPEAK, this);


	GetDlgItem(IDC_BACK)->SetFocus();
	return FALSE;  // return TRUE  unless you set the focus to a control
}
void ChooseSkill::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void ChooseSkill::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		AfxGetApp()->m_pMainWnd = CurStudent;
		CurStudent->ShowWindow(SW_SHOWDEFAULT);
		this->ShowWindow(SW_HIDE);
		delete CurUnit;
	}
	CDialogEx::OnSysCommand(nID, lParam);
}


BOOL ChooseSkill::OnEraseBkgnd(CDC * pDC)
{
	CDialogEx::OnEraseBkgnd(pDC);
	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	int bmw, bmh;


	CBitmap C;
	C.LoadBitmapW(IDB_BACKGROUND1);
	dc.SelectObject(&C);
	BITMAP bmap3;
	C.GetBitmap(&bmap3);
	bmw = bmap3.bmWidth; bmh = bmap3.bmHeight;
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0, 0, rect.right, rect.bottom, &dc, 0, 0, bmw, bmh, SRCCOPY);
	DeleteObject(C);

	ReleaseDC(&dc);
	return true;
}



void ChooseSkill::OnBnClickedBack()
{
	// TODO: Add your control notification handler code here
	AfxGetApp()->m_pMainWnd = CurStudent;
	CurStudent->ShowWindow(SW_SHOWDEFAULT);
	this->ShowWindow(SW_HIDE);
	delete CurUnit;
}


void ChooseSkill::OnBnClickedWrite()
{
	PreviousSkill = 0;
	CWnd * A = GetDlgItem(IDD_CHOOSESKILL);
	if (CurUnit != NULL)
	{
		CurUnit->ShowWindow(SW_HIDE);
		delete CurUnit;
		CurUnit = NULL;
	}
	CurUnit = new Unit;
	CurUnit->Create(IDD_UNIT,A);
	CurUnit->SetWindowPos(&wndTop, 350, 50, 500, 500, SWP_SHOWWINDOW);
	GetDlgItem(IDC_WRITE)->SetFocus();
}


void ChooseSkill::OnBnClickedListen()
{
	// TODO: Add your control notification handler code here
	PreviousSkill = 1;
	CWnd * A = GetDlgItem(IDD_CHOOSESKILL);
	if (CurUnit != NULL)
	{
		CurUnit->ShowWindow(SW_HIDE);
		delete CurUnit;
		CurUnit = NULL;
	}
	CurUnit = new Unit;
	CurUnit->Create(IDD_UNIT, A);
	CurUnit->SetWindowPos(&wndTop, 350, 50, 500, 500, SWP_SHOWWINDOW);
	GetDlgItem(IDC_LISTEN)->SetFocus();
}


void ChooseSkill::OnBnClickedSpeak()
{
	// TODO: Add your control notification handler code here
	PreviousSkill = 2;
	CWnd * A = GetDlgItem(IDD_CHOOSESKILL);
	if (CurUnit != NULL)
	{
		CurUnit->ShowWindow(SW_HIDE);
		delete CurUnit;
		CurUnit = NULL;
	}
	CurUnit = new Unit;
	CurUnit->Create(IDD_UNIT, A);
	CurUnit->SetWindowPos(&wndTop, 350, 50, 500, 500, SWP_SHOWWINDOW);
	GetDlgItem(IDC_SPEAK)->SetFocus();
}


void ChooseSkill::OnBnClickedRead()
{
	// TODO: Add your control notification handler code here
	
	PreviousSkill = 3;
	CWnd * A = GetDlgItem(IDD_CHOOSESKILL);
	if (CurUnit != NULL)
	{
		CurUnit->ShowWindow(SW_HIDE);
		delete CurUnit;
		CurUnit = NULL;
	}
	CurUnit = new Unit;
	CurUnit->Create(IDD_UNIT, A);
	CurUnit->SetWindowPos(&wndTop, 350, 50, 500, 500, SWP_SHOWWINDOW);
	GetDlgItem(IDC_READ)->SetFocus();
}
