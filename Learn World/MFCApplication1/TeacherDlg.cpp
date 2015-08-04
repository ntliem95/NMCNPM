// TeacherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "TeacherDlg.h"
#include "afxdialogex.h"
#include "ForgotPass.h"
#include "SignInDlg.h"
#include "EditInfoDlg.h"
#include "ViewRateDlg.h"

// TeacherDlg dialog
TeacherDlg * CurTeacher = NULL;
IMPLEMENT_DYNAMIC(TeacherDlg, CDialogEx)

TeacherDlg::TeacherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(TeacherDlg::IDD, pParent)
{

	EnableAutomation();

}

TeacherDlg::~TeacherDlg()
{
}

void TeacherDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void TeacherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GREETING, Greeting);
}


BEGIN_MESSAGE_MAP(TeacherDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_TEACHER_CHANGEPASS, &TeacherDlg::OnBnClickedTeacherChangepass)
	ON_BN_CLICKED(IDC_TEACHER_SIGNOUT, &TeacherDlg::OnBnClickedTeacherSignout)
	ON_BN_CLICKED(IDC_TEACHER_EDITINFO, &TeacherDlg::OnBnClickedTeacherEditinfo)
	ON_BN_CLICKED(IDC_BUTTON4, &TeacherDlg::OnBnClickedButton4)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(TeacherDlg, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_ITeacherDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {83BE1197-7A68-4F76-B133-B75285291481}
static const IID IID_ITeacherDlg =
{ 0x83BE1197, 0x7A68, 0x4F76, { 0xB1, 0x33, 0xB7, 0x52, 0x85, 0x29, 0x14, 0x81 } };

BEGIN_INTERFACE_MAP(TeacherDlg, CDialogEx)
	INTERFACE_PART(TeacherDlg, IID_ITeacherDlg, Dispatch)
END_INTERFACE_MAP()

void TeacherDlg::OnPaint()
{
	Greeting.SetText(L"Welcome back ,                         ");
	Greeting.SetFontItalic(TRUE);
	Greeting.SetFontSize(16);
	Greeting.SetTextColor(RGB(255, 255, 255));


	CString text = L"Welcome back , ";
	text += CurAccount.Name;
	Greeting.SetText(text);
	Greeting.SetFontItalic(TRUE);
	Greeting.SetFontSize(16);
	Greeting.SetTextColor(RGB(255, 255, 255));
	if (IsIconic())
	{
		CPaintDC dc1(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc1.GetSafeHdc()), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc1.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

	}
}
void TeacherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		CString Command = L"-1\r\n1*&*";
		Command += CurAccount.UserName + L"*&*\r\n";
		SendString(Command);
		delete CurSIGNIN;
	}
	CDialogEx::OnSysCommand(nID, lParam);
}
BOOL TeacherDlg::OnEraseBkgnd(CDC * pDC)
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

	CBitmap B;
	B.LoadBitmapW(IDB_BAR2);
	dc.SelectObject(&B);
	BITMAP bmap1;
	B.GetBitmap(&bmap1);
	bmw = bmap1.bmWidth; bmh = bmap1.bmHeight;
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0, 0, rect.right, 30, &dc, 0, 0, bmw, bmh, SRCCOPY);
	DeleteObject(B);

	ReleaseDC(&dc);
	return true;
}
// AdminDlg message handlers
void TeacherDlg::SetButton()
{
	LONG GWLOK;
	ChangePassButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_ADMIN_CHANGEPASS));
	GWLOK = GetWindowLong(ChangePassButton->m_hWnd, GWL_STYLE);
	SetWindowLong(ChangePassButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	ChangePass.LoadBitmaps(IDB_CHANGEPASS, IDB_CHANGEPASS_PRESS, 0, 0);
	ChangePass.SubclassDlgItem(IDC_ADMIN_CHANGEPASS, this);
	ChangePass.SizeToContent();

	EditInfoButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_ADMIN_EDITINFO));
	GWLOK = GetWindowLong(EditInfoButton->m_hWnd, GWL_STYLE);
	SetWindowLong(EditInfoButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	EditInfo.LoadBitmaps(IDB_EDIT_INFO, IDB_EDIT_INFO_PRESSED, 0, 0);
	EditInfo.SubclassDlgItem(IDC_ADMIN_EDITINFO, this);
	EditInfo.SizeToContent();

	TeacherRatingButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_VIEW_TEACHER));
	GWLOK = GetWindowLong(TeacherRatingButton->m_hWnd, GWL_STYLE);
	SetWindowLong(TeacherRatingButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	TeacherRating.LoadBitmaps(IDB_TEACHER_RATING, IDB_TEACHER_RATING_PRESSED, 0, 0);
	TeacherRating.SubclassDlgItem(IDC_VIEW_TEACHER, this);
	TeacherRating.SizeToContent();

	EditInfoButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_ADMIN_EDITINFO));
	GWLOK = GetWindowLong(EditInfoButton->m_hWnd, GWL_STYLE);
	SetWindowLong(EditInfoButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	EditInfo.LoadBitmaps(IDB_EDIT_INFO, IDB_EDIT_INFO_PRESSED, 0, 0);
	EditInfo.SubclassDlgItem(IDC_ADMIN_EDITINFO, this);
	EditInfo.SizeToContent();
}

BOOL TeacherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetButton();

	CString text = L"Welcome back , ";
	text += CurAccount.Name;
	Greeting.SetText(text);
	Greeting.SetFontItalic(TRUE);
	Greeting.SetFontSize(16);
	Greeting.SetTextColor(RGB(255, 255, 255));
	//Add Register picture
	//SignOutButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_ADMIN_SIGNOUT));
	//LONG GWLOK = GetWindowLong(SignOutButton->m_hWnd, GWL_STYLE);
	//SetWindowLong(SignOutButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	//SignOut.LoadBitmaps(IDB_SIGNOUT, IDB_SIGNOUT_PRESSED, 0, 0);
	//SignOut.SubclassDlgItem(IDC_ADMIN_SIGNOUT, this);
	//SignOut.SizeToContent();
	//Add SignIn picture


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// TeacherDlg message handlers


void TeacherDlg::OnBnClickedTeacherChangepass()
{
	// TODO: Add your control notification handler code here
	if (CurForgotPass != NULL)
	{
		delete CurForgotPass;
		CurForgotPass = NULL;
	}
	CurForgotPass = new ForgotPass;
	CurForgotPass->Create(IDD_FORGOT_PASS, NULL);
	PreDlg_Of_ForgotPass = 2;
	AfxGetApp()->m_pMainWnd = CurForgotPass;
	CurForgotPass->ShowWindow(SW_SHOWDEFAULT);
	CurTeacher = this;
	this->ShowWindow(SW_HIDE);
}

void TeacherDlg::OnBnClickedTeacherSignout()
{
	SendString(L"-1\r\n1*&*" + CurAccount.UserName + L"*&*\r\n");
	WSAAsyncSelect(*CurSocket, CurSIGNIN->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	AfxGetApp()->m_pMainWnd = CurSIGNIN;
	CurSIGNIN->ShowWindow(SW_SHOWDEFAULT);
	this->ShowWindow(SW_HIDE);
	delete CurTeacher;
	CurTeacher = NULL;
}

void TeacherDlg::OnBnClickedTeacherEditinfo()
{
	// TODO: Add your control notification handler code here
	if (CurEditInfo != NULL)
	{
		delete CurEditInfo;
		CurEditInfo = NULL;
	}
	CurEditInfo = new EditInfoDlg;
	CurEditInfo->Create(IDD_EDITINFO, NULL);
	PreDlg_Of_EditInfo = 2;
	AfxGetApp()->m_pMainWnd = CurEditInfo;
	CurEditInfo->ShowWindow(SW_SHOWDEFAULT);
	CurTeacher = this;
	this->ShowWindow(SW_HIDE);
}


void TeacherDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	ViewRateMode = 0;
	PreDlg_Of_Evalute = 2;
	if (CurViewRate == NULL)
	{
		CurViewRate = new ViewRateDlg;
		CurViewRate->Create(IDD_VIEWRATE, NULL);
	}
	AfxGetApp()->m_pMainWnd = CurViewRate;
	CurViewRate->ShowWindow(SW_SHOWDEFAULT);
	CurTeacher = this;
	this->ShowWindow(SW_HIDE);
	CurViewRate->SetWindowTextW(L"View Teacher Rating");
}
