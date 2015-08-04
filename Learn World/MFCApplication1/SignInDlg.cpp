
// SignInDlg.cpp : implementation file
//



#include "stdafx.h"
#include "afxdialogex.h"
#include "SignInDlg.h"
#include "RuleDlg.h"
#include "ChooseSkill.h"
#include "ForgotPass.h"
#include <string>
#include "StudentDlg.h"
#include "TeacherDlg.h"
#include "AdminDlg.h"
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_BITBUT 35666

SignInDlg * CurSIGNIN = NULL;


SignInDlg::SignInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(SignInDlg::IDD, pParent)
	, ID(_T(""))
	, Password(_T(""))
	, Register_Username(_T(""))
	, Register_Name(_T(""))
	, Register_Pass(_T(""))
	, Register_RePass(_T(""))
	, Register_Add(_T(""))
	, Register_Phone(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void SignInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SIGNIN_ID, ID);
	DDX_Text(pDX, IDC_SIGNIN_PASSWORD, Password);
	DDX_Control(pDX, IDC_LABEL_REGISTER, Label_Register);
	DDX_Control(pDX, IDC_COMBO1, MonthBox);
	DDX_Control(pDX, IDC_COMBO2, DayBox);
	DDX_Control(pDX, IDC_COMBO3, YearBox);
	DDX_Text(pDX, IDC_SIGNUP_NAME, Register_Username);
	DDX_Text(pDX, IDC_SIGNUP_ID, Register_Name);
	DDX_Text(pDX, IDC_SIGNUP_PASSWORD, Register_Pass);
	DDX_Text(pDX, IDC_SIGNUP_REPASSWORD, Register_RePass);
	DDX_Text(pDX, IDC_SIGNUP_NAME2, Register_Add);
	DDX_Text(pDX, IDC_SIGNUP_ID2, Register_Phone);
	DDX_Control(pDX, IDC_TEXT_ID, TEXT_ID);
	DDX_Control(pDX, IDC_TEXT_PASSWORD, TEXT_PASSWORD);
	DDX_Control(pDX, IDC_TEXT_TERM, TEXT_TERM);
	DDX_Control(pDX, IDC_TEXT_GENDER, TEXT_GENDER);
	DDX_Control(pDX, IDC_TEXT_DB, TEXT_DATE);
	DDX_Control(pDX, IDC_TEXT_PHONE, TEXT_PHONE);
	DDX_Control(pDX, IDC_TEXT_ADDRESS, TEXT_ADD);
	DDX_Control(pDX, IDC_TEXT_PASSWORD2, TEXT_PASS2);
	DDX_Control(pDX, IDC_TEXT_PASSWORD1, TEXT_PASS1);
	DDX_Control(pDX, IDC_TEXT_USER, TEXT_USER);
	DDX_Control(pDX, IDC_TEXT_NAME, TEXT_NAME);
}

BEGIN_MESSAGE_MAP(SignInDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SIGNIN, &SignInDlg::OnBnClickedSignin)
	ON_NOTIFY(NM_CLICK, IDC_FORGOT_PASS, &SignInDlg::OnNMClickForgotPass)
	ON_NOTIFY(NM_CLICK, IDC_TERMS, &SignInDlg::OnNMClickTerms)
	ON_BN_CLICKED(IDC_SIGNIN_REGISTER, &SignInDlg::OnBnClickedSigninRegister)
	ON_MESSAGE(WM_SOCKET, &SignInDlg::MessageControl)
	ON_BN_CLICKED(IDC_CHECK_MALE, &SignInDlg::OnBnClickedGenderMale)
	ON_BN_CLICKED(IDC_CHECK_FEMALE, &SignInDlg::OnBnClickedGenderFemale)
END_MESSAGE_MAP()

void SignInDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		if (CurRULE != NULL)
			delete CurRULE;
	}
	CDialogEx::OnSysCommand(nID, lParam);
}

void SignInDlg::OnPaint()
{

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

HCURSOR SignInDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void SignInDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (CurRULE != NULL)
		delete CurRULE;
	if (CurForgotPass != NULL)
		delete CurForgotPass;

}

BOOL SignInDlg::OnEraseBkgnd(CDC * pDC)
{
	CDialogEx::OnEraseBkgnd(pDC);
	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	int bmw, bmh;



	CBitmap C;
	C.LoadBitmapW(IDB_BACKGROUND);
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
// SignInDlg message handlers

void SignInDlg::AddString2ComboBox()
{
	MonthBox.AddString(L"01"); MonthBox.AddString(L"02"); MonthBox.AddString(L"03"); MonthBox.AddString(L"04"); MonthBox.AddString(L"05"); MonthBox.AddString(L"06");
	MonthBox.AddString(L"07"); MonthBox.AddString(L"08"); MonthBox.AddString(L"09"); MonthBox.AddString(L"10"); MonthBox.AddString(L"11"); MonthBox.AddString(L"12");

	CString temp;
	for (int i = 1; i < 32; i++)
	{
		temp = to_wstring(i).c_str();
		if (i < 10)
			DayBox.AddString(L"0" + temp);
		else
			DayBox.AddString(temp);
	}

	for (int i = 1950; i < 2016; i++)
		YearBox.AddString(to_wstring(i).c_str());

}

void SignInDlg::SetTextDlg()
{
	TEXT_TERM.SetFontSize(16);
	TEXT_ID.SetFontSize(15);
	TEXT_ID.SetFontBold(TRUE);
	TEXT_ID.SetFontItalic(TRUE);
	TEXT_PASSWORD.SetFontSize(15);
	TEXT_PASSWORD.SetFontBold(TRUE);
	TEXT_PASSWORD.SetFontItalic(TRUE);
	TEXT_USER.SetFontSize(15);
	TEXT_USER.SetFontBold(TRUE);
	TEXT_USER.SetFontItalic(TRUE);
	TEXT_NAME.SetFontSize(15);
	TEXT_NAME.SetFontBold(TRUE);
	TEXT_NAME.SetFontItalic(TRUE);
	TEXT_PASS1.SetFontSize(15);
	TEXT_PASS1.SetFontBold(TRUE);
	TEXT_PASS1.SetFontItalic(TRUE);
	TEXT_PASS2.SetFontSize(15);
	TEXT_PASS2.SetFontBold(TRUE);
	TEXT_PASS2.SetFontItalic(TRUE);
	TEXT_GENDER.SetFontSize(15);
	TEXT_GENDER.SetFontBold(TRUE);
	TEXT_GENDER.SetFontItalic(TRUE);
	TEXT_DATE.SetFontSize(15);
	TEXT_DATE.SetFontBold(TRUE);
	TEXT_DATE.SetFontItalic(TRUE);
	TEXT_PHONE.SetFontSize(15);
	TEXT_PHONE.SetFontBold(TRUE);
	TEXT_PHONE.SetFontItalic(TRUE);
	TEXT_ADD.SetFontSize(15);
	TEXT_ADD.SetFontBold(TRUE);
	TEXT_ADD.SetFontItalic(TRUE);
	Label_Register.SetFontBold(TRUE);
	Label_Register.SetFontSize(20);
	Label_Register.SetFontItalic(TRUE);
}

BOOL SignInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// Add "About..." menu item to system menu.
	//Add string to Commbo box
	AddString2ComboBox();
	DayBox.SetCurSel(0);
	MonthBox.SetCurSel(0);
	YearBox.SetCurSel(0);

	SetTextDlg();

	//Add Register picture
	SignInButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_SIGNIN));
	LONG GWLOK = GetWindowLong(SignInButton->m_hWnd, GWL_STYLE);
	SetWindowLong(SignInButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	SignIn.LoadBitmaps(IDB_SIGNIN, IDB_SIGNIN_PRESSED, 0, 0);
	SignIn.SubclassDlgItem(IDC_SIGNIN, this);
	SignIn.SizeToContent();
	//Add SignIn picture
	RegisterButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_SIGNIN_REGISTER));
	GWLOK = GetWindowLong(RegisterButton->m_hWnd, GWL_STYLE);
	SetWindowLong(RegisterButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Register.LoadBitmaps(IDB_REGISTER, IDB_REGISTER_PRESSED, 0, 0);
	Register.SubclassDlgItem(IDC_SIGNIN_REGISTER, this);
	Register.SizeToContent();


	return FALSE;  // return TRUE  unless you set the focus to a control
}


void SignInDlg::OnNMClickTerms(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	if (CurRULE == NULL)
	{
		CurRULE = new RuleDlg;
		CurRULE->Create(IDD_RULE, this);
	}

	CurRULE->ShowWindow(TRUE);
}

void SignInDlg::OnBnClickedGenderMale()
{
	// TODO: Add your control notification handler code here
	CheckDlgButton(IDC_CHECK_FEMALE, MF_UNCHECKED);
	Register_Gender = L"Male";
}

void SignInDlg::OnBnClickedGenderFemale()
{
	// TODO: Add your control notification handler code here
	CheckDlgButton(IDC_CHECK_MALE, MF_UNCHECKED);
	Register_Gender = L"Female";
}

void SignInDlg::OnBnClickedSignin()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (Password == "" && ID == "" || (ID == ""))
	{
		MessageBox(L"Please enter your ID", 0, MB_OK);
		return;
	}
	if (Password == "")
	{
		MessageBox(L"Please enter your Password", 0, MB_OK);
		return;
	}
	if (isServerOnline == 0)
	{
		isServerOnline = StartSocket(m_hWnd);
		WSAAsyncSelect(*CurSocket, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	}
	if (isServerOnline == 0)
	{
		MessageBox(_T("Can't connect to server. Please try later"), _T("ERROR"), 0);
		return;
	}
	CString Command;
	Command = L"0\r\n" + ID + L"*&*" + Password + L"*&*\r\n";
	SendString(Command);

}

void SignInDlg::OnNMClickForgotPass(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	if (isServerOnline == 0)
	{
		isServerOnline = StartSocket(m_hWnd);
	}
	if (isServerOnline == 0)
	{
		MessageBox(_T("Can't connect to server. Please try later"), _T("ERROR"), 0);
		return;
	}
	if (CurForgotPass == NULL)
	{
		CurForgotPass = new ForgotPass;
		CurForgotPass->Create(IDD_FORGOT_PASS, NULL);
	}
	PreDlg_Of_ForgotPass = 0;
	AfxGetApp()->m_pMainWnd = CurForgotPass;
	CurForgotPass->ShowWindow(SW_SHOWDEFAULT);
	CurSIGNIN = this;
	this->ShowWindow(SW_HIDE);
	
	
}

void SignInDlg::OnBnClickedSigninRegister()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	if (Register_Name == ""){ MessageBox(L"Please add your Name", NULL, MB_OK); return; }
	if (Register_Username == ""){ MessageBox(L"Please choose a Username", NULL, MB_OK);	return; }
	if (Register_Pass == ""){ MessageBox(L"Please type your password", NULL, MB_OK); return; }
	if (Register_RePass == ""){ MessageBox(L"Please type your password again", NULL, MB_OK); return; }
	if (Register_Pass.Compare(Register_RePass) != 0) { MessageBox(L"Make sure to type password correctly", NULL, MB_OK); return; }
	if (Register_Add == "")	{ MessageBox(L"Please add your Address", NULL, MB_OK); return; }
	if (Register_Phone == ""){ MessageBox(L"Please add your phone number", NULL, MB_OK); return; }
	if (Register_Gender == ""){ MessageBox(L"Please select your gender", NULL, MB_OK); return; }
	if (isServerOnline == 0)
	{
		isServerOnline = StartSocket(m_hWnd);
		WSAAsyncSelect(*CurSocket, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	}
	if (isServerOnline == 0){ MessageBox(_T("Can't connect to server. Please try later"), _T("ERROR"), 0); return; }

	wstring day = to_wstring(DayBox.GetCurSel() + 1);
	wstring year = to_wstring(YearBox.GetCurSel() + 1950);
	wstring month = to_wstring(MonthBox.GetCurSel() + 1);
	CString DAY = day.c_str();
	CString MONTH = month.c_str();
	CString YEAR = year.c_str();

	CString Command = L"1\r\n";
	Command += Register_Username + L"*&*" + Register_Pass + L"*&*" + Register_RePass + L"*&*" + Register_Name + L"*&*";
	Command += DAY + L"*&*" + MONTH + L"*&*" + YEAR + L"*&*" + Register_Gender + L"*&*" + Register_Add + L"*&*" + Register_Phone + L"*&*\r\n";
	SendString(Command);
}

LRESULT  SignInDlg::MessageControl(WPARAM wParam, LPARAM lParam)
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
			if (flag2 == -1)
			{
				MessageBox(L"This account is Deactivated by Admin", NULL, MB_OK);
				break;
			}
			if (flag2 == 0)
			{
				MessageBox(L"This account is being used , please wait for it to Sign out", NULL, MB_OK);
				break;
			}
			if (flag2 == 1)
			{
				MessageBox(L"Wrong ID  or Password", NULL, MB_OK);
				break;
			}
			if (flag2 == 2)
			{
				MessageBox(L"Your username is taken", NULL, MB_OK);
				break;
			}
			break;
		case 0:

			break;
		case 1:
			if (flag2 == 0) // admin
			{
				CurAccount.type = 0;
				//Open Admin dialog
				if (CurAdmin != NULL)
					delete CurAdmin;
				CurAdmin = new AdminDlg;
				CurAdmin->Create(IDD_ADMIN, NULL);
				AfxGetApp()->m_pMainWnd = CurAdmin;
				CurAdmin->ShowWindow(SW_SHOWDEFAULT);
				CurSIGNIN = this;
				this->ShowWindow(SW_HIDE);
				break;
			}
			if (flag2 == 1) //teacher
			{
				CurAccount.type = 1;
				//Open Teacher dialog
				if (CurTeacher != NULL)
					delete CurTeacher;
				CurTeacher = new TeacherDlg;
				CurTeacher->Create(IDD_TEACHER, NULL);
				AfxGetApp()->m_pMainWnd = CurTeacher;
				CurTeacher->ShowWindow(SW_SHOWDEFAULT);
				CurSIGNIN = this;
				this->ShowWindow(SW_HIDE);
				break;
			}
			if (flag2 == 2) // user
			{
				CurAccount.type = 2;
				//Open User dialog
				
				if (CurStudent != NULL)
					delete CurStudent;
				CurStudent = new StudentDlg;
				CurStudent->Create(IDD_STUDENT, NULL);
				AfxGetApp()->m_pMainWnd = CurStudent;
				CurStudent->ShowWindow(SW_SHOWDEFAULT);
				CurSIGNIN = this;
				this->ShowWindow(SW_HIDE);
				break;
			}
			break;
		case 1507:
			CString Info[10];
			SplitString(strResult[1], Info);
			CurAccount.UserName = Info[0];
			CurAccount.Pass = Info[1];
			CurAccount.Name = Info[2];
			CurAccount.Db.iDay = _ttoi(Info[3]);
			CurAccount.Db.iMonth = _ttoi(Info[4]);
			CurAccount.Db.iYear = _ttoi(Info[5]);
			CurAccount.Gender = Info[6];
			CurAccount.Add = Info[7];
			CurAccount.Phone = Info[8];
			break;
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
