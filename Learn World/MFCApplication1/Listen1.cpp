// Listen1.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "Listen1.h"
#include "afxdialogex.h"

// Listen1 dialog
#include "Unit.h"
#include "ChooseSkill.h"
Listen1 * CurListen1 = NULL;
IMPLEMENT_DYNAMIC(Listen1, CDialogEx)

Listen1::Listen1(CWnd* pParent /*=NULL*/)
	: CDialogEx(Listen1::IDD, pParent)
{

}

Listen1::~Listen1()
{
}

void Listen1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STUDENT_CHANGEPASS, Answer3);
	DDX_Control(pDX, IDC_STATI, Answer2);
	DDX_Control(pDX, IDC_STATI1, Answer1);
	DDX_Control(pDX, IDC_STATI2, Answer4);
	DDX_Control(pDX, IDC_STATI5, Answer5);
	DDX_Control(pDX, IDC_OCX1, player);
	DDX_Control(pDX, IDC_STA1, Title);
	DDX_Control(pDX, IDC_STA2, Question1);
	DDX_Control(pDX, IDC_STA3, Question4);
	DDX_Control(pDX, IDC_STAT2, Question5);
	DDX_Control(pDX, IDC_STATI23, Question2);
	DDX_Control(pDX, IDC_ST2, Question3);
}


BEGIN_MESSAGE_MAP(Listen1, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_L1_CHECK, &Listen1::OnBnClickedL1Check)
	ON_BN_CLICKED(IDC_L1_BACK, &Listen1::OnBnClickedL1Back)
	ON_BN_CLICKED(IDC_ANSWER1_1, &Listen1::OnBnClickedAnswer11)
	ON_BN_CLICKED(IDC_ANSWER1_2, &Listen1::OnBnClickedAnswer12)
	ON_BN_CLICKED(IDC_ANSWER1_3, &Listen1::OnBnClickedAnswer13)
	ON_BN_CLICKED(IDC_ANSWER2_1, &Listen1::OnBnClickedAnswer21)
	ON_BN_CLICKED(IDC_ANSWER2_2, &Listen1::OnBnClickedAnswer22)
	ON_BN_CLICKED(IDC_ANSWER2_3, &Listen1::OnBnClickedAnswer23)
	ON_BN_CLICKED(IDC_ANSWER3_1, &Listen1::OnBnClickedAnswer31)
	ON_BN_CLICKED(IDC_ANSWER3_2, &Listen1::OnBnClickedAnswer32)
	ON_BN_CLICKED(IDC_ANSWER3_3, &Listen1::OnBnClickedAnswer33)
	ON_BN_CLICKED(IDC_ANSWER4_1, &Listen1::OnBnClickedAnswer41)
	ON_BN_CLICKED(IDC_ANSWER4_2, &Listen1::OnBnClickedAnswer42)
	ON_BN_CLICKED(IDC_ANSWER4_3, &Listen1::OnBnClickedAnswer43)
	ON_BN_CLICKED(IDC_ANSWER5_1, &Listen1::OnBnClickedAnswer51)
	ON_BN_CLICKED(IDC_ANSWER5_2, &Listen1::OnBnClickedAnswer52)
	ON_BN_CLICKED(IDC_ANSWER5_3, &Listen1::OnBnClickedAnswer53)
END_MESSAGE_MAP()


// Listen1 message handlers
BOOL Listen1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	IWMPSettings *pMediaPlayerSettings = NULL;
	player.get_settings()->QueryInterface(__uuidof(IWMPSettings), (void**)&pMediaPlayerSettings);
	pMediaPlayerSettings->put_autoStart(VARIANT_FALSE);
	player.put_URL(L"Database\\Unit1\\L1.mp3");

	Title.SetFontSize(14);
	Title.SetFontBold(1);
	Question1.SetFontSize(13);
	Question2.SetFontSize(13);
	Question3.SetFontSize(13);
	Question4.SetFontSize(13);
	Question5.SetFontSize(13);

	BackButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_L1_BACK));
	LONG GWLOK = GetWindowLong(BackButton->m_hWnd, GWL_STYLE);
	SetWindowLong(BackButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Back.LoadBitmaps(IDB_BACK, IDB_BACK_PRESSED, 0, 0);
	Back.SubclassDlgItem(IDC_L1_BACK, this);
	Back.SizeToContent();


	CheckButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_L1_CHECK));
	GWLOK = GetWindowLong(CheckButton->m_hWnd, GWL_STYLE);
	SetWindowLong(CheckButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Check.LoadBitmaps(IDB_CHECKANSWER, IDB_CHECKANSWER_PRESSED, 0, IDB_CHECKANSWER_PRESSED);
	Check.SubclassDlgItem(IDC_L1_CHECK, this);
	Check.SizeToContent();
	return TRUE;
}

void Listen1::OnSysCommand(UINT nID, LPARAM lParam)
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

void Listen1::OnBnClickedL1Check()
{
	// TODO: Add your control notification handler code here
	Answer1.SetText(L"Answer: understanding local people (you might find some of our Australian slang more difficult to understand)");
	Answer2.SetText(L"Answer: 50 (currently about 50 members)");
	Answer3.SetText(L"Answer: Once every two weeks (every second Thursday)");
	Answer4.SetText(L"Answer: A talk (usually one of the members gives a little presentation)");
	Answer5.SetText(L"Answer: Meet Australians (the main point of the club is to give people like you the chance to mix in more with people from this country)");
	Answer1.SetTextColor(RGB(255, 0, 0));
	Answer2.SetTextColor(RGB(255, 0, 0));
	Answer3.SetTextColor(RGB(255, 0, 0));
	Answer4.SetTextColor(RGB(255, 0, 0));
	Answer5.SetTextColor(RGB(255, 0, 0));
	Answer1.ShowWindow(SW_SHOWDEFAULT);
	Answer2.ShowWindow(SW_SHOWDEFAULT);
	Answer3.ShowWindow(SW_SHOWDEFAULT);
	Answer4.ShowWindow(SW_SHOWDEFAULT);
	Answer5.ShowWindow(SW_SHOWDEFAULT);
}


void Listen1::OnBnClickedL1Back()
{
	// TODO: Add your control notification handler code here
	AfxGetApp()->m_pMainWnd = CurChooseSkills;
	CurChooseSkills->ShowWindow(SW_SHOWDEFAULT);
	this->ShowWindow(SW_HIDE);
	CurUnit->ShowWindow(SW_HIDE);
	delete CurListen1;
	CurListen1 = NULL;
}


void Listen1::OnBnClickedAnswer11()
{
	Choice[0] = 1;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer12()
{
	Choice[0] = 2;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer13()
{
	Choice[0] = 3;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer21()
{
	Choice[1] = 1;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer22()
{
	Choice[1] = 2;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer23()
{
	Choice[1] = 3;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer31()
{
	Choice[2] = 1;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer32()
{
	Choice[2] = 2;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer33()
{
	Choice[2] = 3;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer41()
{
	Choice[3] = 1;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer42()
{
	Choice[3] = 2;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer43()
{
	Choice[3] = 3;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer51()
{
	Choice[4] = 1;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer52()
{
	Choice[4] = 2;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}


void Listen1::OnBnClickedAnswer53()
{
	Choice[4] = 3;
	UpdateData(TRUE);
	int check = 0;
	for (int i = 0; i < 5; i++)
		if (Choice[i] != 0)
			check++;
	if (check == 5)
		GetDlgItem(IDC_L1_CHECK)->EnableWindow(1);
}
