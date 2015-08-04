// Write1.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "Write1.h"
#include "afxdialogex.h"
#include "Unit.h"
#include "ChooseSkill.h"

// Write1 dialog
Write1 * CurWrite1 = NULL;
IMPLEMENT_DYNAMIC(Write1, CDialogEx)

Write1::Write1(CWnd* pParent /*=NULL*/)
	: CDialogEx(Write1::IDD, pParent)
	, Content(_T(""))
	, CountWord(_T(""))
{

}

Write1::~Write1()
{
}

void Write1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Title, Title);
	DDX_Control(pDX, IDC_STAs, Note);
	DDX_Control(pDX, IDC_STAT, WordCount);
	DDX_Text(pDX, IDC_EDIT2, Content);
	DDX_Control(pDX, IDC_EDIT2, Edit);
	DDX_Text(pDX, IDC_EDIT3, CountWord);
}


BEGIN_MESSAGE_MAP(Write1, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_SAMPLE, &Write1::OnBnClickedSample)
	ON_BN_CLICKED(IDC_W1_FINISH, &Write1::OnBnClickedW1Finish)
	ON_BN_CLICKED(IDC_W1_BACk, &Write1::OnBnClickedW1Back)
	ON_EN_CHANGE(IDC_EDIT2, &Write1::OnEnChangeEdit2)
END_MESSAGE_MAP()


// Write1 message handlers
void Write1::OnSysCommand(UINT nID, LPARAM lParam)
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

BOOL Write1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString temp;
	FILE *fStream1;
	errno_t e = _tfopen_s(&fStream1, _T("Database\\Unit1\\W1.txt"), _T("rt,ccs=UNICODE"));
	CStdioFile f1(fStream1);  // open the file from this stream
	for (int i = 0; i < 6; i++)
	{
		f1.ReadString(temp);
		Sample += temp + L"\r\n\r\n";

	}
	f1.Close();
	UpdateData(FALSE);
	Title.SetFontSize(14);
	Title.SetFontBold(1);
	Note.SetFontSize(13);

	BackButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_S1_BACK));
	LONG GWLOK = GetWindowLong(BackButton->m_hWnd, GWL_STYLE);
	SetWindowLong(BackButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Back.LoadBitmaps(IDB_BACK, IDB_BACK_PRESSED, 0, 0);
	Back.SubclassDlgItem(IDC_S1_BACK, this);
	Back.SizeToContent();

	FinishButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_W1_FINISH));
	GWLOK = GetWindowLong(FinishButton->m_hWnd, GWL_STYLE);
	SetWindowLong(FinishButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Finish.LoadBitmaps(IDB_FINISH, IDB_FINISH_PRESSED, 0, 0);
	Finish.SubclassDlgItem(IDC_W1_FINISH, this);
	Finish.SizeToContent();

	GetDlgItem(IDC_R1_BACK)->SetFocus();
	return FALSE;
}

void Write1::OnBnClickedSample()
{
	MessageBox(Sample, L"Sample", MB_OK);
}


void Write1::OnBnClickedW1Finish()
{
	// TODO: Add your control notification handler code here
	Edit.EnableWindow(0);
}


void Write1::OnBnClickedW1Back()
{
	AfxGetApp()->m_pMainWnd = CurChooseSkills;
	CurChooseSkills->ShowWindow(SW_SHOWDEFAULT);
	this->ShowWindow(SW_HIDE);
	CurUnit->ShowWindow(SW_HIDE);
	delete CurWrite1;
	CurWrite1 = NULL;
}


void Write1::OnEnChangeEdit2()
{
	UpdateData(TRUE);

	int nSpaces = 0;
	unsigned int i = 0;

	// Skip over spaces at the beginning of the word
	while (isspace(Content[i]))
		i++;

	for (; i < Content.GetLength(); i++)
	{
		if (isspace(Content[i]))
		{
			nSpaces++;

			// Skip over duplicate spaces & if a NULL character is found, we're at the end of the string
			while (isspace(Content[i++]))
				if (Content[i] == '\0')
					nSpaces--;
		}
	}

	CountWord = to_wstring(nSpaces + 1).c_str();
	UpdateData(FALSE);
}
