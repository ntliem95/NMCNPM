// ForgotPass.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "ForgotPass.h"
#include "afxdialogex.h"
#include "SignInDlg.h"
#include "AdminDlg.h"
#include "StudentDlg.h"
#include "TeacherDlg.h"
// ForgotPass dialog
ForgotPass * CurForgotPass = NULL;
IMPLEMENT_DYNAMIC(ForgotPass, CDialogEx)

ForgotPass::ForgotPass(CWnd* pParent /*=NULL*/)
	: CDialogEx(ForgotPass::IDD, pParent)
	, Username(_T(""))
	, Email(_T(""))
	, NewPassword(_T(""))
	, ConfirmPassword(_T(""))
{

}


void ForgotPass::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Username);
	DDX_Text(pDX, IDC_EDIT2, Email);
	DDX_Text(pDX, IDC_EDIT4, NewPassword);
	DDX_Text(pDX, IDC_EDIT5, ConfirmPassword);
	DDX_Control(pDX, IDC_FORGOT_STEP1, Step1);
	DDX_Control(pDX, IDC_FORGOT_USERNAME, Username_TEXT);
	DDX_Control(pDX, IDC_FORGOT_PHONE, Phone_Text);
	DDX_Control(pDX, IDC_FORGOT_STEP2, Step2);
	DDX_Control(pDX, IDC_FORGOT_NEWPASS, Pass_TEXT);
	DDX_Control(pDX, IDC_FORGOT_CONFIRMPASS, RePass_TEXT);
}


BEGIN_MESSAGE_MAP(ForgotPass, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FORGOT_BACK, &ForgotPass::OnBnClickedForgotBack)
	ON_BN_CLICKED(IDC_FORGOT_NEXT, &ForgotPass::OnBnClickedForgotNext)
	ON_MESSAGE(WM_SOCKET, &ForgotPass::MessageControl)
END_MESSAGE_MAP()


// ForgotPass message handlers
BOOL ForgotPass::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	WSAAsyncSelect(*CurSocket, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);

	NextButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_FORGOT_NEXT));
	LONG GWLOK = GetWindowLong(NextButton->m_hWnd, GWL_STYLE);
	SetWindowLong(NextButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Next.LoadBitmaps(IDB_NEXT, IDB_NEXT_PRESSED, 0, 0);
	Next.SubclassDlgItem(IDC_FORGOT_NEXT, this);
	Next.SizeToContent();
	//Add SignIn picture
	BackButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_FORGOT_BACK));
	GWLOK = GetWindowLong(BackButton->m_hWnd, GWL_STYLE);
	SetWindowLong(BackButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Back.LoadBitmaps(IDB_BACK, IDB_BACK_PRESSED, 0, 0);
	Back.SubclassDlgItem(IDC_FORGOT_BACK, this);
	Back.SizeToContent();

	return TRUE;  // return TRUE  unless you set the focus to a control
}
BOOL ForgotPass::OnEraseBkgnd(CDC * pDC)
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
void ForgotPass::OnPaint()
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
void ForgotPass::OnSysCommand(UINT nID, LPARAM lParam)
{

	if (nID == SC_CLOSE)
	{
		ReturnToPreviousDlg();
	}

	CDialogEx::OnSysCommand(nID, lParam);
}
void ForgotPass::ReturnToPreviousDlg()
{
	closesocket(*CurSocket);
	if (PreDlg_Of_ForgotPass == 2)
	{
		AfxGetApp()->m_pMainWnd = CurTeacher;
		StartSocket(CurTeacher->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurTeacher->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurTeacher->ShowWindow(SW_SHOWDEFAULT);
	}
	if (PreDlg_Of_ForgotPass == 3)
	{
		AfxGetApp()->m_pMainWnd = CurStudent;
		StartSocket(CurStudent->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurStudent->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurStudent->ShowWindow(SW_SHOWDEFAULT);
	}
	if (PreDlg_Of_ForgotPass == 1)
	{
		AfxGetApp()->m_pMainWnd = CurAdmin;
		StartSocket(CurAdmin->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurAdmin->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurAdmin->ShowWindow(SW_SHOWDEFAULT);
	}
	if (PreDlg_Of_ForgotPass == 0)
	{
		AfxGetApp()->m_pMainWnd = CurSIGNIN;
		StartSocket(CurSIGNIN->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurSIGNIN->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurSIGNIN->ShowWindow(SW_SHOWDEFAULT);
	}
	this->ShowWindow(SW_HIDE);
}

int check = 0;
LRESULT  ForgotPass::MessageControl(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam))
	{
		// Display the error and close the socket
		closesocket(wParam);
	}
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
	{
		CString temp;
		if (RecvString(temp)<0)
			break;
		CString strResult[2];
		SplitFlag(temp, strResult);
		int flag1 = _ttoi(strResult[0]);
		int flag2;
		if (flag1 != 1507)
			flag2 = _ttoi(strResult[1]);
		switch (flag1)
		{
		case -1:
			if (flag2 == 0)
			{
				MessageBox(L"Your username is not found", NULL, MB_OK);
				break;
			}
			if (flag2 == 1)
			{
				MessageBox(L"Your Phone number is not correct", NULL, MB_OK);
				break;
			}
			break;
		case 0:
			if (flag2 == 0)
			{
				GetDlgItem(IDC_FORGOT_STEP2)->ShowWindow(SW_SHOWDEFAULT);
				GetDlgItem(IDC_FORGOT_NEWPASS)->ShowWindow(SW_SHOWDEFAULT);
				GetDlgItem(IDC_FORGOT_CONFIRMPASS)->ShowWindow(SW_SHOWDEFAULT);
				GetDlgItem(IDC_EDIT_NEWPASS)->ShowWindow(SW_SHOWDEFAULT);
				GetDlgItem(IDC_EDIT_CONFIRMPASS)->ShowWindow(SW_SHOWDEFAULT);


				GetDlgItem(IDC_FORGOT_STEP1)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_FORGOT_USERNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_FORGOT_PHONE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT_PHONE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_HIDE);
				check = 1;
				break;
			}
			if (flag2 == 1)
			{
				MessageBox(L"Your Password has changed. You can now Sign in with your new Password", NULL, MB_OK);
				ReturnToPreviousDlg();
				check = 0;
				break;
			}
		}
		break;
	}
	case FD_CLOSE:
	{
		closesocket(*CurSocket);
		MessageBox(L"Server has closed connection", NULL, MB_OK);
		isServerOnline = 0;
		break;
	}
	}
	return 0;

}


void ForgotPass::OnBnClickedForgotBack()
{
	// TODO: Add your control notification handler code here
	if (check == 0) // back to sign in
	{
		ReturnToPreviousDlg();
		delete CurForgotPass;
		CurForgotPass = NULL;
	}
	else //back to step 1
	{
		GetDlgItem(IDC_FORGOT_STEP2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FORGOT_NEWPASS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FORGOT_CONFIRMPASS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_NEWPASS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CONFIRMPASS)->ShowWindow(SW_HIDE);


		GetDlgItem(IDC_FORGOT_STEP1)->ShowWindow(SW_SHOWDEFAULT);
		GetDlgItem(IDC_FORGOT_USERNAME)->ShowWindow(SW_SHOWDEFAULT);
		GetDlgItem(IDC_FORGOT_PHONE)->ShowWindow(SW_SHOWDEFAULT);
		GetDlgItem(IDC_EDIT_PHONE)->ShowWindow(SW_SHOWDEFAULT);
		GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_SHOWDEFAULT);
	}
}


void ForgotPass::OnBnClickedForgotNext()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (check == 0) //step 1
	{
		if (Username == "")
		{
			MessageBox(L"Please enter your Username to varify your account", NULL, MB_OK);
			return;
		}
		if (Email == "")
		{
			MessageBox(L"Please enter your Phone number to varify your account", NULL, MB_OK);
			return;
		}
		CString Command;
		Command = "2\r\n0*&*";
		Command += Username + L"*&*" + Email + L"*&*\r\n";
		SendString(Command);
	}
	else // step 2
	{
		if (NewPassword == "" || ConfirmPassword == "")
		{
			MessageBox(L"Please enter the new password you want", NULL, MB_OK);
			return;
		}
		if (NewPassword.Compare(ConfirmPassword) != 0)
		{
			MessageBox(L"Please make sure these two password are the same", NULL, MB_OK);
			return;
		}
		CString Command;
		Command = "2\r\n1*&*";
		Command += Username + L"*&*" + NewPassword + L"*&*\r\n";
		SendString(Command);
	}
}
