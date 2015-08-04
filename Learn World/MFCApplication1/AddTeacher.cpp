// AddTeacher.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "AddTeacher.h"
#include "afxdialogex.h"
#include "AdminDlg.h"


// AddTeacher dialog

IMPLEMENT_DYNAMIC(AddTeacher, CDialogEx)

AddTeacher::AddTeacher(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddTeacher::IDD, pParent)
	, Phone(_T(""))
	, Add(_T(""))
	, Name(_T(""))
	, Pass(_T(""))
	, User(_T(""))
{

	EnableAutomation();

}

AddTeacher::~AddTeacher()
{
}

void AddTeacher::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void AddTeacher::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITINFO_NAME2, user);
	DDX_Control(pDX, IDC_EDITINFO_NAME3, pass);
	DDX_Control(pDX, IDC_EDITINFO_NAME, name);
	DDX_Control(pDX, IDC_EDITINFO_ADD, add);
	DDX_Control(pDX, IDC_EDITINFO_DB, date);
	DDX_Control(pDX, IDC_EDITINFO_PHONE, phone);
	DDX_Control(pDX, IDC_COMBO1, MonthBox);
	DDX_Control(pDX, IDC_COMBO3, DayBox);
	DDX_Control(pDX, IDC_COMBO2, YearBox);
	DDX_Text(pDX, IDC_EDIT6, Phone);
	DDX_Text(pDX, IDC_EDIT3, Add);
	DDX_Text(pDX, IDC_EDIT4, Name);
	DDX_Text(pDX, IDC_EDIT5, Pass);
	DDX_Text(pDX, IDC_EDIT2, User);
}


BEGIN_MESSAGE_MAP(AddTeacher, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_SOCKET, &AddTeacher::MessageControl)
	ON_BN_CLICKED(IDC_ADDTEACHER_FINISH, &AddTeacher::OnBnClickedAddteacherFinish)
	ON_BN_CLICKED(IDC_ADDTEACHER_BACK, &AddTeacher::OnBnClickedAddteacherBack)
	ON_BN_CLICKED(IDC_EDITINFO_MALE, &AddTeacher::OnBnClickedEditinfoMale)
	ON_BN_CLICKED(IDC_EDITINFO_FEMALE, &AddTeacher::OnBnClickedEditinfoFemale)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(AddTeacher, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IAddTeacher to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {22F1DFC9-CFEC-44BA-97EE-7CB7C09EFC19}
static const IID IID_IAddTeacher =
{ 0x22F1DFC9, 0xCFEC, 0x44BA, { 0x97, 0xEE, 0x7C, 0xB7, 0xC0, 0x9E, 0xFC, 0x19 } };

BEGIN_INTERFACE_MAP(AddTeacher, CDialogEx)
	INTERFACE_PART(AddTeacher, IID_IAddTeacher, Dispatch)
END_INTERFACE_MAP()
AddTeacher * CurAddTeacher = NULL;

// AddTeacher message handlers
BOOL AddTeacher::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	user.SetFontItalic(TRUE);
	user.SetFontBold(TRUE);
	user.SetFontSize(14);
	pass.SetFontItalic(TRUE);
	pass.SetFontBold(TRUE);
	pass.SetFontSize(14);
	name.SetFontItalic(TRUE);
	name.SetFontBold(TRUE);
	name.SetFontSize(14);
	add.SetFontItalic(TRUE);
	add.SetFontBold(TRUE);
	add.SetFontSize(14);
	date.SetFontItalic(TRUE);
	date.SetFontBold(TRUE);
	date.SetFontSize(14);
	phone.SetFontItalic(TRUE);
	phone.SetFontBold(TRUE);
	phone.SetFontSize(14);



	WSAAsyncSelect(*CurSocket, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	
	FinishButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_ADDTEACHER_FINISH));
	LONG GWLOK = GetWindowLong(FinishButton->m_hWnd, GWL_STYLE);
	SetWindowLong(FinishButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Finish.LoadBitmaps(IDB_FINISH, IDB_FINISH_PRESSED, 0, 0);
	Finish.SubclassDlgItem(IDC_ADDTEACHER_FINISH, this);
	Finish.SizeToContent();
	//Add SignIn picture
	BackButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_ADDTEACHER_BACK));
	GWLOK = GetWindowLong(BackButton->m_hWnd, GWL_STYLE);
	SetWindowLong(BackButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Back.LoadBitmaps(IDB_BACK, IDB_BACK_PRESSED, 0, 0);
	Back.SubclassDlgItem(IDC_ADDTEACHER_BACK, this);
	Back.SizeToContent();

	AddString2ComboBox();


	return TRUE;  // return TRUE  unless you set the focus to a control
}


LRESULT  AddTeacher::MessageControl(WPARAM wParam, LPARAM lParam)
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
			MessageBox(L"This username is taken, please choose another one", NULL, MB_OK);
			break;
		}
		break;
	}
	case FD_CLOSE:
	{
		closesocket(*CurSocket);
		MessageBox(L"Server has closed connection", NULL, MB_OK);
		break;
	}
	}
	return 0;

}

void AddTeacher::OnBnClickedAddteacherFinish()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if ( Name == ""){ MessageBox(L"Full name cannot be blank", NULL, MB_OK); return; }
	if ( Add == "")	{ MessageBox(L"Address cannot be blank", NULL, MB_OK); return; }
	if ( Phone == ""){ MessageBox(L"Phone number cannot be blank", NULL, MB_OK); return; }
	if (User == "") { MessageBox(L"Username cannot be blank", NULL, MB_OK); return; }
	if (Pass == "") { MessageBox(L"Password cannot be blank", NULL, MB_OK); return; }
	wstring day = to_wstring(DayBox.GetCurSel() + 1);
	wstring year = to_wstring(YearBox.GetCurSel() + 1950);
	wstring month = to_wstring(MonthBox.GetCurSel() + 1);
	CString DAY = day.c_str();
	CString MONTH = month.c_str();
	CString YEAR = year.c_str();

	CString Command;
	Command = L"4\r\n";
	Command += User + L"*&*" + Pass + L"*&*" + Name + L"*&*" + DAY + L"*&*" + MONTH + L"*&*";
	Command += YEAR + L"*&*" +  Gender + L"*&*" +  Add + L"*&*" +  Phone + L"*&*\r\n";
	SendString(Command);

	OnBnClickedAddteacherBack();
}


void AddTeacher::OnBnClickedAddteacherBack()
{
	// TODO: Add your control notification handler code here
	closesocket(*CurSocket);
	AfxGetApp()->m_pMainWnd = CurAdmin;
	StartSocket(CurAdmin->m_hWnd);
	WSAAsyncSelect(*CurSocket, CurAdmin->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	CurAdmin->ShowWindow(SW_SHOWDEFAULT);
	this->ShowWindow(SW_HIDE);
	//delete CurEditInfo;
	//CurEditInfo = NULL;
}

BOOL AddTeacher::OnEraseBkgnd(CDC * pDC)
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
void AddTeacher::OnSysCommand(UINT nID, LPARAM lParam)
{

	if (nID == SC_CLOSE)
	{
		closesocket(*CurSocket);
		AfxGetApp()->m_pMainWnd = CurAdmin;
		StartSocket(CurAdmin->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurAdmin->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurAdmin->ShowWindow(SW_SHOWDEFAULT);
		this->ShowWindow(SW_HIDE);
	}

	CDialogEx::OnSysCommand(nID, lParam);
}

void AddTeacher::AddString2ComboBox()
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

void AddTeacher::OnBnClickedEditinfoMale()
{
	// TODO: Add your control notification handler code here
	CheckDlgButton(IDC_EDITINFO_FEMALE, MF_UNCHECKED);
	Gender = L"Male";
}


void AddTeacher::OnBnClickedEditinfoFemale()
{
	// TODO: Add your control notification handler code here
	CheckDlgButton(IDC_EDITINFO_MALE, MF_UNCHECKED);
	Gender = L"Female";
}
