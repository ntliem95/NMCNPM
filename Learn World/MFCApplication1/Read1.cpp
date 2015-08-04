// Read1.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "Read1.h"
#include "afxdialogex.h"
#include "Unit.h"
#include "ChooseSkill.h"

// Read1 dialog
Read1 * CurRead1 = NULL;
IMPLEMENT_DYNAMIC(Read1, CDialogEx)

Read1::Read1(CWnd* pParent /*=NULL*/)
	: CDialogEx(Read1::IDD, pParent)
	, Content(_T(""))
{

}

Read1::~Read1()
{
}

void Read1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Paragraph);
	DDX_Control(pDX, IDC_STATICR, Title);
	DDX_Control(pDX, IDC_TRUE, True);
	DDX_Control(pDX, IDC_FALSE, False);
	DDX_Control(pDX, IDC_NOT, Not);
	DDX_Text(pDX, IDC_EDIT1, Content);
	DDX_Control(pDX, IDC_A1, A1);
	DDX_Control(pDX, IDC_A2, A2);
	DDX_Control(pDX, IDC_A3, A3);
	DDX_Control(pDX, IDC_A4, A4);
	DDX_Control(pDX, IDC_A5, A5);
	DDX_Control(pDX, IDC_STATI1, C1);
	DDX_Control(pDX, IDC_STATI4, C2);
	DDX_Control(pDX, IDC_STATI3, C3);
	DDX_Control(pDX, IDC_STATI6, C4);
	DDX_Control(pDX, IDC_STATI2, C5);
}


BEGIN_MESSAGE_MAP(Read1, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_R1_CHECK, &Read1::OnBnClickedR1Check)
	ON_BN_CLICKED(IDC_R1_BACK, &Read1::OnBnClickedR1Back)
	ON_CBN_SELCHANGE(IDC_A1, &Read1::OnCbnSelchangeA1)
	ON_CBN_SELCHANGE(IDC_A2, &Read1::OnCbnSelchangeA2)
	ON_CBN_SELCHANGE(IDC_A3, &Read1::OnCbnSelchangeA3)
	ON_CBN_SELCHANGE(IDC_A4, &Read1::OnCbnSelchangeA4)
	ON_CBN_SELCHANGE(IDC_A5, &Read1::OnCbnSelchangeA5)
END_MESSAGE_MAP()

void Read1::OnSysCommand(UINT nID, LPARAM lParam)
{

	if (nID == SC_CLOSE)
	{
		AfxGetApp()->m_pMainWnd = CurChooseSkills;
		CurChooseSkills->ShowWindow(SW_SHOWDEFAULT);
		this->ShowWindow(SW_HIDE);
		CurUnit->ShowWindow(SW_HIDE);
	}
	CDialogEx::OnSysCommand(nID, lParam);
}
// Read1 message handlers
BOOL Read1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString temp;
	FILE *fStream1;
	errno_t e = _tfopen_s(&fStream1, _T("Database\\Unit1\\R1.txt"), _T("rt,ccs=UNICODE"));
	CStdioFile f1(fStream1);  // open the file from this stream
	for (int i = 0; i < 7; i++)
	{
		f1.ReadString(temp);
		Content += temp + L"\r\n\r\n";

	}
	f1.Close();
	UpdateData(FALSE);
	Title.SetFontSize(14);
	Title.SetFontBold(1);
	True.SetFontBold(1);
	Not.SetFontBold(1);
	False.SetFontBold(1);

	C1.SetTextColor(RGB(255, 0, 0));
	C1.ShowWindow(SW_HIDE);
	C2.SetTextColor(RGB(255, 0, 0));
	C2.ShowWindow(SW_HIDE);
	C3.SetTextColor(RGB(255, 0, 0));
	C3.ShowWindow(SW_HIDE);
	C4.SetTextColor(RGB(255, 0, 0));
	C4.ShowWindow(SW_HIDE);
	C5.SetTextColor(RGB(255, 0, 0));
	C5.ShowWindow(SW_HIDE);

	BackButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_R1_BACK));
	LONG GWLOK = GetWindowLong(BackButton->m_hWnd, GWL_STYLE);
	SetWindowLong(BackButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Back.LoadBitmaps(IDB_BACK, IDB_BACK_PRESSED, 0, 0);
	Back.SubclassDlgItem(IDC_R1_BACK, this);
	Back.SizeToContent();


	CheckButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_R1_CHECK));
	GWLOK = GetWindowLong(CheckButton->m_hWnd, GWL_STYLE);
	SetWindowLong(CheckButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Check.LoadBitmaps(IDB_CHECKANSWER, IDB_CHECKANSWER_PRESSED, 0, IDB_CHECKANSWER_PRESSED);
	Check.SubclassDlgItem(IDC_R1_CHECK, this);
	Check.SizeToContent();

	GetDlgItem(IDC_R1_BACK)->SetFocus();
	return FALSE;
}

void Read1::OnBnClickedR1Check()
{
	// TODO: Add your control notification handler code here
	C1.ShowWindow(SW_SHOWDEFAULT);
	C2.ShowWindow(SW_SHOWDEFAULT);
	C3.ShowWindow(SW_SHOWDEFAULT);
	C4.ShowWindow(SW_SHOWDEFAULT);
	C5.ShowWindow(SW_SHOWDEFAULT);
}


void Read1::OnBnClickedR1Back()
{
	AfxGetApp()->m_pMainWnd = CurChooseSkills;
	CurChooseSkills->ShowWindow(SW_SHOWDEFAULT);
	this->ShowWindow(SW_HIDE);
	CurUnit->ShowWindow(SW_HIDE);
	delete CurRead1;
	CurRead1 = NULL;
}


void Read1::OnCbnSelchangeA1()
{
	UpdateData(TRUE);
	if (A1.GetCurSel() != -1 && A2.GetCurSel() != -1 && A3.GetCurSel() != -1 && A4.GetCurSel() != -1 && A5.GetCurSel() != -1)
		GetDlgItem(IDC_R1_CHECK)->EnableWindow(1);
}


void Read1::OnCbnSelchangeA2()
{
	UpdateData(TRUE);
	if (A1.GetCurSel() != -1 && A2.GetCurSel() != -1 && A3.GetCurSel() != -1 && A4.GetCurSel() != -1 && A5.GetCurSel() != -1)
		GetDlgItem(IDC_R1_CHECK)->EnableWindow(1);
}


void Read1::OnCbnSelchangeA3()
{
	UpdateData(TRUE);
	if (A1.GetCurSel() != -1 && A2.GetCurSel() != -1 && A3.GetCurSel() != -1 && A4.GetCurSel() != -1 && A5.GetCurSel() != -1)
		GetDlgItem(IDC_R1_CHECK)->EnableWindow(1);
}


void Read1::OnCbnSelchangeA4()
{
	UpdateData(TRUE);
	if (A1.GetCurSel() != -1 && A2.GetCurSel() != -1 && A3.GetCurSel() != -1 && A4.GetCurSel() != -1 && A5.GetCurSel() != -1)
		GetDlgItem(IDC_R1_CHECK)->EnableWindow(1);
}


void Read1::OnCbnSelchangeA5()
{
	UpdateData(TRUE);
	if (A1.GetCurSel() != -1 && A2.GetCurSel() != -1 && A3.GetCurSel() != -1 && A4.GetCurSel() != -1 && A5.GetCurSel() != -1)
		GetDlgItem(IDC_R1_CHECK)->EnableWindow(1);
}
