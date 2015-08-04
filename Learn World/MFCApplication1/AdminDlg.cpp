// AdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "AdminDlg.h"
#include "afxdialogex.h"
#include "ForgotPass.h"
#include "SignInDlg.h"
#include "EditInfoDlg.h"
#include "AddTeacher.h"
#include "DeleteAccountDlg.h"
#include "ViewRateDlg.h"
#include "EvaluateDlg.h"

// AdminDlg dialog
AdminDlg * CurAdmin = NULL;
IMPLEMENT_DYNAMIC(AdminDlg, CDialogEx)

AdminDlg::AdminDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AdminDlg::IDD, pParent)
{

	EnableAutomation();

}

AdminDlg::~AdminDlg()
{
	
}

void AdminDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void AdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADMIN_GREETING, Greeting);
}


BEGIN_MESSAGE_MAP(AdminDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ADMIN_SIGNOUT, &AdminDlg::OnBnClickedAdminSignout)
	ON_BN_CLICKED(IDC_ADMIN_CHANGEPASS, &AdminDlg::OnBnClickedAdminChangepass)
	ON_BN_CLICKED(IDC_ADMIN_EDITINFO, &AdminDlg::OnBnClickedAdminEditinfo)
	ON_BN_CLICKED(IDC_ADMIN_TEACHER, &AdminDlg::OnBnClickedAdminTeacher)
	ON_BN_CLICKED(IDC_ADMIN_DELETE, &AdminDlg::OnBnClickedAdminDelete)
	ON_BN_CLICKED(IDC_VIEW_TEACHER, &AdminDlg::OnBnClickedViewTeacher)
	ON_BN_CLICKED(IDC_VIEW_STUDENT, &AdminDlg::OnBnClickedViewStudent)
	ON_BN_CLICKED(IDC_EVALUATE_TEACHER, &AdminDlg::OnBnClickedEvaluateTeacher)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(AdminDlg, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IAdminDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {373DC5A3-1036-48E6-8B1A-D13DC87CE85C}
static const IID IID_IAdminDlg =
{ 0x373DC5A3, 0x1036, 0x48E6, { 0x8B, 0x1A, 0xD1, 0x3D, 0xC8, 0x7C, 0xE8, 0x5C } };

BEGIN_INTERFACE_MAP(AdminDlg, CDialogEx)
	INTERFACE_PART(AdminDlg, IID_IAdminDlg, Dispatch)
END_INTERFACE_MAP()
void AdminDlg::OnDestroy()
{
	delete CurAdmin;
	CurAdmin = NULL;
}
void AdminDlg::OnPaint()
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
void AdminDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		CString Command = L"-1\r\n0*&*";
		Command += CurAccount.UserName + L"*&*\r\n";
		SendString(Command);
		delete CurSIGNIN;
	}
	CDialogEx::OnSysCommand(nID, lParam);
}
// AdminDlg message handlers
void AdminDlg::SetButton()
{
	LONG GWLOK;
	SignOutButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_ADMIN_SIGNOUT));
	GWLOK = GetWindowLong(SignOutButton->m_hWnd, GWL_STYLE);
	SetWindowLong(SignOutButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	SignOut.LoadBitmaps(IDB_SIGNOUT, IDB_SIGNOUT_PRESSED, 0, 0);
	SignOut.SubclassDlgItem(IDC_ADMIN_SIGNOUT, this);
	SignOut.SizeToContent();

	EvaluateTeacherButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_EVALUATE_TEACHER));
	GWLOK = GetWindowLong(EvaluateTeacherButton->m_hWnd, GWL_STYLE);
	SetWindowLong(EvaluateTeacherButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	EvaluateTeacher.LoadBitmaps(IDB_EVALUATE_TEACHER, IDB_EVALUATE_TEACHER_PRESSED, 0, 0);
	EvaluateTeacher.SubclassDlgItem(IDC_EVALUATE_TEACHER, this);
	EvaluateTeacher.SizeToContent();

	StudentRatingButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_VIEW_STUDENT));
	GWLOK = GetWindowLong(StudentRatingButton->m_hWnd, GWL_STYLE);
	SetWindowLong(StudentRatingButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	StudentRating.LoadBitmaps(IDB_STUDENT_RATING, IDB_STUDENT_RATING_PRESSED, 0, 0);
	StudentRating.SubclassDlgItem(IDC_VIEW_STUDENT, this);
	StudentRating.SizeToContent();

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

	DeleteAccountButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_ADMIN_DELETE));
	GWLOK = GetWindowLong(DeleteAccountButton->m_hWnd, GWL_STYLE);
	SetWindowLong(DeleteAccountButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	DeleteAccount.LoadBitmaps(IDB_DELETE_ACCOUNT, IDB_DELETE_ACCOUNT_PRESSED, 0, 0);
	DeleteAccount.SubclassDlgItem(IDC_ADMIN_DELETE, this);
	DeleteAccount.SizeToContent();

	ChangePassButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_ADMIN_CHANGEPASS));
	GWLOK = GetWindowLong(ChangePassButton->m_hWnd, GWL_STYLE);
	SetWindowLong(ChangePassButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	ChangePass.LoadBitmaps(IDB_CHANGEPASS, IDB_CHANGEPASS_PRESS, 0, 0);
	ChangePass.SubclassDlgItem(IDC_ADMIN_CHANGEPASS, this);
	ChangePass.SizeToContent();
}

BOOL AdminDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	SetButton();

	CString text = L"Welcome back , ";
	text += CurAccount.Name;
	Greeting.SetText(text);
	Greeting.SetFontItalic(TRUE);
	Greeting.SetFontSize(16);
	Greeting.SetTextColor(RGB(255, 255, 255));
	//Add Register picture


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void AdminDlg::OnBnClickedAdminSignout()
{
	// TODO: Add your control notification handler code here
	SendString(L"-1\r\n0*&*" + CurAccount.UserName + L"*&*\r\n");
	WSAAsyncSelect(*CurSocket, CurSIGNIN->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	AfxGetApp()->m_pMainWnd = CurSIGNIN;
	CurSIGNIN->ShowWindow(SW_SHOWDEFAULT);
	this->ShowWindow(SW_HIDE);
	delete CurAdmin;
	CurAdmin = NULL;
}

BOOL AdminDlg::OnEraseBkgnd(CDC * pDC)
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

void AdminDlg::OnBnClickedAdminChangepass()
{
	// TODO: Add your control notification handler code here
	if (CurForgotPass != NULL)
	{
		delete CurForgotPass; 
		CurForgotPass = NULL;
	}
	CurForgotPass = new ForgotPass;
	CurForgotPass->Create(IDD_FORGOT_PASS, NULL);
	PreDlg_Of_ForgotPass = 1;
	AfxGetApp()->m_pMainWnd = CurForgotPass;
	CurForgotPass->ShowWindow(SW_SHOWDEFAULT);
	CurAdmin = this;
	this->ShowWindow(SW_HIDE);
}

void AdminDlg::OnBnClickedAdminEditinfo()
{
	// TODO: Add your control notification handler code here
	if (CurEditInfo != NULL)
	{
		delete CurEditInfo;
		CurEditInfo = NULL;
	}
	CurEditInfo = new EditInfoDlg;
	CurEditInfo->Create(IDD_EDITINFO, NULL);
	PreDlg_Of_EditInfo = 1;
	AfxGetApp()->m_pMainWnd = CurEditInfo;
	CurEditInfo->ShowWindow(SW_SHOWDEFAULT);
	CurAdmin = this;
	this->ShowWindow(SW_HIDE);
}

void AdminDlg::OnBnClickedAdminTeacher()
{
	// TODO: Add your control notification handler code here
	if (CurAddTeacher == NULL)
	{
		CurAddTeacher = new AddTeacher;
		CurAddTeacher->Create(IDD_ADDTEACHER, NULL);
	}
	AfxGetApp()->m_pMainWnd = CurAddTeacher;
	CurAddTeacher->ShowWindow(SW_SHOWDEFAULT);
	CurAdmin = this;
	this->ShowWindow(SW_HIDE);
}

void AdminDlg::OnBnClickedAdminDelete()
{
	// TODO: Add your control notification handler code here
	if (CurDelete == NULL)
	{
		CurDelete = new DeleteAccountDlg;
		CurDelete->Create(IDD_DELETE_ACCOUNT, NULL);
	}
	AfxGetApp()->m_pMainWnd = CurDelete;
	CurDelete->ShowWindow(SW_SHOWDEFAULT);
	CurAdmin = this;
	this->ShowWindow(SW_HIDE);
}

void AdminDlg::OnBnClickedViewTeacher()
{
	// TODO: Add your control notification handler code here
	ViewRateMode = 0;
	PreDlg_Of_Evalute = 0;
	if (CurViewRate == NULL)
	{
		CurViewRate = new ViewRateDlg;
		CurViewRate->Create(IDD_VIEWRATE, NULL);
	}
	AfxGetApp()->m_pMainWnd = CurViewRate;
	CurViewRate->ShowWindow(SW_SHOWDEFAULT);
	CurAdmin = this;
	this->ShowWindow(SW_HIDE);
	CurViewRate->SetWindowTextW(L"View Teacher Rating");
}

void AdminDlg::OnBnClickedViewStudent()
{
	// TODO: Add your control notification handler code here
	ViewRateMode = 1;
	if (CurViewRate == NULL)
	{
		CurViewRate = new ViewRateDlg;
		CurViewRate->Create(IDD_VIEWRATE, NULL);
	}
	AfxGetApp()->m_pMainWnd = CurViewRate;
	CurViewRate->ShowWindow(SW_SHOWDEFAULT);
	CurAdmin = this;
	this->ShowWindow(SW_HIDE);
	CurViewRate->SetWindowTextW(L"View Student Rating");
}

void AdminDlg::OnBnClickedEvaluateTeacher()
{
	// TODO: Add your control notification handler code here
	ViewRateMode = 0;
	PreDlg_Of_Evalute = 0;
	if (CurEvaluate == NULL)
	{
		CurEvaluate = new EvaluateDlg;
		CurEvaluate->Create(IDD_EVALUATE_TEACHER, NULL);
	}
	AfxGetApp()->m_pMainWnd = CurEvaluate;
	CurEvaluate->ShowWindow(SW_SHOWDEFAULT);
	CurAdmin = this;
	this->ShowWindow(SW_HIDE);
	CurEvaluate->SetWindowTextW(L"Evaluate Teacher");
}
