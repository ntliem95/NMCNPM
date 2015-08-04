// EditInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "EditInfoDlg.h"
#include "afxdialogex.h"
#include "AdminDlg.h"
#include "StudentDlg.h"
#include "TeacherDlg.h"

// EditInfoDlg dialog
EditInfoDlg * CurEditInfo = NULL;
IMPLEMENT_DYNAMIC(EditInfoDlg, CDialogEx)

EditInfoDlg::EditInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(EditInfoDlg::IDD, pParent)
	, EDITINFO_Name(_T(""))
	, EDITINFO_Add(_T(""))
	, EDITINFO_Phone(_T(""))
{

	EnableAutomation();

}

EditInfoDlg::~EditInfoDlg()
{
}

void EditInfoDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void EditInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, EDITINFO_Name);
	DDX_Text(pDX, IDC_EDIT3, EDITINFO_Add);
	DDX_Text(pDX, IDC_EDIT6, EDITINFO_Phone);
	DDX_Control(pDX, IDC_EDITINFO_NAME, Name);
	DDX_Control(pDX, IDC_EDITINFO_ADD, Address);
	DDX_Control(pDX, IDC_EDITINFO_DB, Date);
	DDX_Control(pDX, IDC_EDITINFO_PHONE, Phone);
	DDX_Control(pDX, IDC_COMBO1, DayBox);
	DDX_Control(pDX, IDC_COMBO3, MonthBox);
	DDX_Control(pDX, IDC_COMBO2, YearBox);
}


BEGIN_MESSAGE_MAP(EditInfoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_EDITINFO_FEMALE, &EditInfoDlg::OnBnClickedEditinfoFemale)
	ON_BN_CLICKED(IDC_EDITINFO_MALE, &EditInfoDlg::OnBnClickedEditinfoMale)
	ON_BN_CLICKED(IDC_EDITINFO_FINISH, &EditInfoDlg::OnBnClickedEditinfoFinish)
	ON_BN_CLICKED(IDC_EDITINFO_BACK, &EditInfoDlg::OnBnClickedEditinfoBack)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(EditInfoDlg, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IEditInfoDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {250599CC-B802-4AFC-9C21-9E89D2B18C0F}
static const IID IID_IEditInfoDlg =
{ 0x250599CC, 0xB802, 0x4AFC, { 0x9C, 0x21, 0x9E, 0x89, 0xD2, 0xB1, 0x8C, 0xF } };

BEGIN_INTERFACE_MAP(EditInfoDlg, CDialogEx)
	INTERFACE_PART(EditInfoDlg, IID_IEditInfoDlg, Dispatch)
END_INTERFACE_MAP()

void EditInfoDlg::AddString2ComboBox()
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
// EditInfoDlg message handlers
BOOL EditInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here

	Name.SetFontSize(14);
	Name.SetFontItalic(TRUE);
	Name.SetFontBold(TRUE);
	Address.SetFontSize(14);
	Address.SetFontItalic(TRUE);
	Address.SetFontBold(TRUE);
	Date.SetFontSize(14);
	Date.SetFontItalic(TRUE);
	Date.SetFontBold(TRUE);
	Phone.SetFontSize(14);
	Phone.SetFontItalic(TRUE);
	Phone.SetFontBold(TRUE);

	AddString2ComboBox();
	//WSAAsyncSelect(*CurSocket, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	if (CurAccount.Gender.Compare(L"Male") == 0) CheckDlgButton(IDC_EDITINFO_MALE, MF_CHECKED);
	else CheckDlgButton(IDC_EDITINFO_FEMALE, MF_CHECKED);
	EDITINFO_Add = CurAccount.Add;
	EDITINFO_Name = CurAccount.Name;
	EDITINFO_Phone = CurAccount.Phone;
	EDITINFO_Gender = CurAccount.Gender;
	DayBox.SetCurSel(CurAccount.Db.iDay - 1);
	MonthBox.SetCurSel(CurAccount.Db.iMonth - 1);
	YearBox.SetCurSel(CurAccount.Db.iYear - 1950);
	UpdateData(FALSE);

	FinishButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_EDITINFO_FINISH));
	LONG GWLOK = GetWindowLong(FinishButton->m_hWnd, GWL_STYLE);
	SetWindowLong(FinishButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Finish.LoadBitmaps(IDB_FINISH, IDB_FINISH_PRESSED, 0, 0);
	Finish.SubclassDlgItem(IDC_EDITINFO_FINISH, this);
	Finish.SizeToContent();
	//Add SignIn picture
	BackButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_EDITINFO_BACK));
	GWLOK = GetWindowLong(BackButton->m_hWnd, GWL_STYLE);
	SetWindowLong(BackButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Back.LoadBitmaps(IDB_BACK, IDB_BACK_PRESSED, 0, 0);
	Back.SubclassDlgItem(IDC_EDITINFO_BACK, this);
	Back.SizeToContent();

	return TRUE;  // return TRUE  unless you set the focus to a control
}
BOOL EditInfoDlg::OnEraseBkgnd(CDC * pDC)
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

	pDC->StretchBlt(0, 0, rect.right, rect.bottom, &dc, 0, 0, bmw, bmh, SRCCOPY);
	DeleteObject(C);

	ReleaseDC(&dc);
	return true;
}
void EditInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

	if (nID == SC_CLOSE)
	{
		ReturnToPreviousDlg();
	}

	CDialogEx::OnSysCommand(nID, lParam);
}

void EditInfoDlg::ReturnToPreviousDlg()
{
	closesocket(*CurSocket);
	if (PreDlg_Of_EditInfo == 1)
	{
		AfxGetApp()->m_pMainWnd = CurAdmin;
		StartSocket(CurAdmin->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurAdmin->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurAdmin->ShowWindow(SW_SHOWDEFAULT);
	}
	if (PreDlg_Of_EditInfo  == 2)
	{
		AfxGetApp()->m_pMainWnd = CurTeacher;
		StartSocket(CurTeacher->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurTeacher->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurTeacher->ShowWindow(SW_SHOWDEFAULT);
	}
	if (PreDlg_Of_EditInfo == 3)
	{
		AfxGetApp()->m_pMainWnd = CurStudent;
		StartSocket(CurStudent->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurStudent->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurStudent->ShowWindow(SW_SHOWDEFAULT);
	}
	this->ShowWindow(SW_HIDE);
	//delete CurEditInfo;
	//CurEditInfo = NULL;
}

void EditInfoDlg::OnBnClickedEditinfoFemale()
{
	// TODO: Add your control notification handler code here
	CheckDlgButton(IDC_EDITINFO_MALE, MF_UNCHECKED);
	EDITINFO_Gender = L"Female";
}

void EditInfoDlg::OnBnClickedEditinfoMale()
{
	// TODO: Add your control notification handler code here
	CheckDlgButton(IDC_EDITINFO_FEMALE, MF_UNCHECKED);
	EDITINFO_Gender = L"Male";
}


void EditInfoDlg::OnBnClickedEditinfoFinish()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (EDITINFO_Name == ""){ MessageBox(L"Your name cannot be blank", NULL, MB_OK); return; }
	if (EDITINFO_Add == "")	{ MessageBox(L"Your Address cannot be blank", NULL, MB_OK); return; }
	if (EDITINFO_Phone == ""){ MessageBox(L"Your Phone number cannot be blank", NULL, MB_OK); return; }

	wstring day = to_wstring(DayBox.GetCurSel() + 1);
	wstring year = to_wstring(YearBox.GetCurSel() + 1950);
	wstring month = to_wstring(MonthBox.GetCurSel() + 1);
	CString DAY = day.c_str();
	CString MONTH = month.c_str();
	CString YEAR = year.c_str();

	CString Command;
	Command = L"3\r\n";
	Command += CurAccount.UserName + L"*&*" + EDITINFO_Name + L"*&*" + DAY + L"*&*" + MONTH + L"*&*";
	Command +=  YEAR + L"*&*" + EDITINFO_Gender + L"*&*" + EDITINFO_Add + L"*&*" + EDITINFO_Phone + L"*&*\r\n";
	SendString(Command);


	CurAccount.Add = EDITINFO_Add;
	CurAccount.Name = EDITINFO_Name;
	CurAccount.Phone = EDITINFO_Phone;
	CurAccount.Gender = EDITINFO_Gender;
	CurAccount.Db.iDay = DayBox.GetCurSel() + 1;
	CurAccount.Db.iMonth = MonthBox.GetCurSel() + 1;
	CurAccount.Db.iYear = YearBox.GetCurSel() + 1950;
	ReturnToPreviousDlg();
}


void EditInfoDlg::OnBnClickedEditinfoBack()
{
	// TODO: Add your control notification handler code here
	ReturnToPreviousDlg();
}
