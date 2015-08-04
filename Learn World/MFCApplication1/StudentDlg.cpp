// StudentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "StudentDlg.h"
#include "afxdialogex.h"
#include "ForgotPass.h"
#include "EditInfoDlg.h"
#include "SignInDlg.h"
#include "EvaluateDlg.h"
#include "ChooseSkill.h"
#include "ViewRateDlg.h"
// StudentDlg dialog
StudentDlg * CurStudent = NULL;
IMPLEMENT_DYNAMIC(StudentDlg, CDialogEx)

StudentDlg::StudentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(StudentDlg::IDD, pParent)
{

}

StudentDlg::~StudentDlg()
{
}

void StudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STUDENT_GREETING, Greeting);
}


BEGIN_MESSAGE_MAP(StudentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_STUDENT_CHANGEPASS, &StudentDlg::OnBnClickedStudentChangepass)
	ON_BN_CLICKED(IDC_STUDENT_EDITINFO, &StudentDlg::OnBnClickedStudentEditinfo)
	ON_BN_CLICKED(IDC_STUDENT_SIGNOUT, &StudentDlg::OnBnClickedStudentSignout)
	ON_BN_CLICKED(IDC_STUDENT_LEARNING, &StudentDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_STUDENT_EVALUATE, &StudentDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_STUDENT_VIEW, &StudentDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// StudentDlg message handlers

void StudentDlg::OnPaint()
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
void StudentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		CString Command = L"-1\r\n2*&*";
		Command += CurAccount.UserName + L"*&*\r\n";
		SendString(Command);
		delete CurSIGNIN;
		//CurStudent = NULL;
	}
	CDialogEx::OnSysCommand(nID, lParam);
}
BOOL StudentDlg::OnEraseBkgnd(CDC * pDC)
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
void StudentDlg::SetButton()
{
	LONG GWLOK;
	Test4SkillButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_STUDENT_TEST));
	GWLOK = GetWindowLong(Test4SkillButton->m_hWnd, GWL_STYLE);
	SetWindowLong(Test4SkillButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Test4Skill.LoadBitmaps(IDB_TEST, IDB_TEST_PRESSED, 0, 0);
	Test4Skill.SubclassDlgItem(IDC_STUDENT_TEST, this);
	Test4Skill.SizeToContent();

	LearningButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_STUDENT_LEARNING));
	GWLOK = GetWindowLong(LearningButton->m_hWnd, GWL_STYLE);
	SetWindowLong(LearningButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Learning.LoadBitmaps(IDB_LEARNING, IDB_LEARNING_PRESSED, 0, 0);
	Learning.SubclassDlgItem(IDC_STUDENT_LEARNING, this);
	Learning.SizeToContent();

	SignOutButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_STUDENT_SIGNOUT));
	GWLOK = GetWindowLong(SignOutButton->m_hWnd, GWL_STYLE);
	SetWindowLong(SignOutButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	SignOut.LoadBitmaps(IDB_SIGNOUT, IDB_SIGNOUT_PRESSED, 0, 0);
	SignOut.SubclassDlgItem(IDC_STUDENT_SIGNOUT, this);
	SignOut.SizeToContent();

	EvaluateTeacherButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_STUDENT_EVALUATE));
	GWLOK = GetWindowLong(EvaluateTeacherButton->m_hWnd, GWL_STYLE);
	SetWindowLong(EvaluateTeacherButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	EvaluateTeacher.LoadBitmaps(IDB_EVALUATE_TEACHER, IDB_EVALUATE_TEACHER_PRESSED, 0, 0);
	EvaluateTeacher.SubclassDlgItem(IDC_STUDENT_EVALUATE, this);
	EvaluateTeacher.SizeToContent();

	ChangePassButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_STUDENT_CHANGEPASS));
	GWLOK = GetWindowLong(ChangePassButton->m_hWnd, GWL_STYLE);
	SetWindowLong(ChangePassButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	ChangePass.LoadBitmaps(IDB_CHANGEPASS, IDB_CHANGEPASS_PRESS, 0, 0);
	ChangePass.SubclassDlgItem(IDC_STUDENT_CHANGEPASS, this);
	ChangePass.SizeToContent();

	EditInfoButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_STUDENT_EDITINFO));
	GWLOK = GetWindowLong(EditInfoButton->m_hWnd, GWL_STYLE);
	SetWindowLong(EditInfoButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	EditInfo.LoadBitmaps(IDB_EDIT_INFO, IDB_EDIT_INFO_PRESSED, 0, 0);
	EditInfo.SubclassDlgItem(IDC_STUDENT_EDITINFO, this);
	EditInfo.SizeToContent();

	StudentRatingButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_STUDENT_VIEW));
	GWLOK = GetWindowLong(StudentRatingButton->m_hWnd, GWL_STYLE);
	SetWindowLong(StudentRatingButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	StudentRating.LoadBitmaps(IDB_STUDENT_RATING, IDB_STUDENT_RATING_PRESSED, 0, 0);
	StudentRating.SubclassDlgItem(IDC_STUDENT_VIEW, this);
	StudentRating.SizeToContent();
}

BOOL StudentDlg::OnInitDialog()
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

void StudentDlg::OnBnClickedStudentChangepass()
{
	// TODO: Add your control notification handler code here
	if (CurForgotPass != NULL)
	{
		delete CurForgotPass;
		CurForgotPass = NULL;
	}
	CurForgotPass = new ForgotPass;
	CurForgotPass->Create(IDD_FORGOT_PASS, NULL);
	PreDlg_Of_ForgotPass = 3;
	AfxGetApp()->m_pMainWnd = CurForgotPass;
	CurForgotPass->ShowWindow(SW_SHOWDEFAULT);
	CurStudent = this;
	this->ShowWindow(SW_HIDE);
}


void StudentDlg::OnBnClickedStudentEditinfo()
{
	// TODO: Add your control notification handler code here
	if (CurEditInfo != NULL)
	{
		delete CurEditInfo;
		CurEditInfo = NULL;
	}
	CurEditInfo = new EditInfoDlg;
	CurEditInfo->Create(IDD_EDITINFO, NULL);
	PreDlg_Of_EditInfo = 3;
	AfxGetApp()->m_pMainWnd = CurEditInfo;
	CurEditInfo->ShowWindow(SW_SHOWDEFAULT);
	CurStudent = this;
	this->ShowWindow(SW_HIDE);
}


void StudentDlg::OnBnClickedStudentSignout()
{
	// TODO: Add your control notification handler code here


	SendString(L"-1\r\n2*&*" + CurAccount.UserName + L"*&*\r\n");
	WSAAsyncSelect(*CurSocket, CurSIGNIN->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	AfxGetApp()->m_pMainWnd = CurSIGNIN;
	CurSIGNIN->ShowWindow(SW_SHOWDEFAULT);
	this->ShowWindow(SW_HIDE);
	delete CurStudent;
	CurStudent = NULL;
}


void StudentDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	if (CurChooseSkills == NULL)
	{
		CurChooseSkills = new ChooseSkill;
		CurChooseSkills->Create(IDD_CHOOSESKILL, NULL);
	}
	
	AfxGetApp()->m_pMainWnd = CurChooseSkills;
	CurChooseSkills->ShowWindow(SW_SHOWDEFAULT);
	CurStudent = this;
	this->ShowWindow(SW_HIDE);
}


void StudentDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	ViewRateMode = 0;
	PreDlg_Of_Evalute = 1;
	if (CurEvaluate == NULL)
	{
		CurEvaluate = new EvaluateDlg;
		CurEvaluate->Create(IDD_EVALUATE_TEACHER, NULL);
	}
	AfxGetApp()->m_pMainWnd = CurEvaluate;
	CurEvaluate->ShowWindow(SW_SHOWDEFAULT);
	CurStudent = this;
	this->ShowWindow(SW_HIDE);
	CurEvaluate->SetWindowTextW(L"Evaluate Teacher");
}


void StudentDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	ViewRateMode = 1;
	PreDlg_Of_Evalute = 1;
	if (CurViewRate == NULL)
	{
		CurViewRate = new ViewRateDlg;
		CurViewRate->Create(IDD_VIEWRATE, NULL);
	}
	AfxGetApp()->m_pMainWnd = CurViewRate;
	CurViewRate->ShowWindow(SW_SHOWDEFAULT);
	CurStudent = this;
	this->ShowWindow(SW_HIDE);
	CurViewRate->SetWindowTextW(L"View Student Rating");
}
