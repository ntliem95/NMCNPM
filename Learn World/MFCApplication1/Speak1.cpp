// Speak1.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "Speak1.h"
#include "afxdialogex.h"
#include "Unit.h"
#include "ChooseSkill.h"

// Speak1 dialog

IMPLEMENT_DYNAMIC(Speak1, CDialogEx)
Speak1 * CurSpeak1 = NULL;
Speak1::Speak1(CWnd* pParent /*=NULL*/)
	: CDialogEx(Speak1::IDD, pParent)
	, Content(_T(""))
{

}

Speak1::~Speak1()
{
}

void Speak1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Content);
	DDX_Control(pDX, IDC_STA, Title);
	DDX_Control(pDX, IDC_STATICR, Should);
	DDX_Control(pDX, IDC_STAT, Sample);
}


BEGIN_MESSAGE_MAP(Speak1, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_S1_BACK, &Speak1::OnBnClickedS1Back)
END_MESSAGE_MAP()


// Speak1 message handlers
void Speak1::OnSysCommand(UINT nID, LPARAM lParam)
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

BOOL Speak1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString temp;
	FILE *fStream1;
	errno_t e = _tfopen_s(&fStream1, _T("Database\\Unit1\\S1.txt"), _T("rt,ccs=UNICODE"));
	CStdioFile f1(fStream1);  // open the file from this stream
	for (int i = 0; i < 6; i++)
	{
		f1.ReadString(temp);
		Content += temp + L"\r\n\r\n";

	}
	f1.Close();
	UpdateData(FALSE);
	Title.SetFontSize(14);
	Title.SetFontBold(1);
	Should.SetFontSize(13);
	Should.SetFontUnderline(1);
	Sample.SetFontSize(13);
	Sample.SetFontUnderline(1);

	BackButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_S1_BACK));
	LONG GWLOK = GetWindowLong(BackButton->m_hWnd, GWL_STYLE);
	SetWindowLong(BackButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Back.LoadBitmaps(IDB_BACK, IDB_BACK_PRESSED, 0, 0);
	Back.SubclassDlgItem(IDC_S1_BACK, this);
	Back.SizeToContent();

	GetDlgItem(IDC_R1_BACK)->SetFocus();
	return FALSE;
}

void Speak1::OnBnClickedS1Back()
{
	AfxGetApp()->m_pMainWnd = CurChooseSkills;
	CurChooseSkills->ShowWindow(SW_SHOWDEFAULT);
	this->ShowWindow(SW_HIDE);
	CurUnit->ShowWindow(SW_HIDE);
	delete CurSpeak1;
	CurSpeak1 = NULL;
}
