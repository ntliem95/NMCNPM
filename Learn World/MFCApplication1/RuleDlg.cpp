// RuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "SignInDlg.h"
#include "RuleDlg.h"



// RuleDlg dialog
RuleDlg * CurRULE = NULL;
IMPLEMENT_DYNAMIC(RuleDlg, CDialogEx)

RuleDlg::RuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(RuleDlg::IDD, pParent)
	, Terms(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void RuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TERMS, Terms);
	DDX_Control(pDX, IDC_TERMS, check);
	DDX_Control(pDX, IDC_RULE_TITLE, label);
}


BEGIN_MESSAGE_MAP(RuleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_RULE_BACK, &RuleDlg::OnBnClickedRuleBack)
END_MESSAGE_MAP()


// RuleDlg message handlers
BOOL RuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	Terms += _T("When using products Let Learn IELTS, prohibit Users having some acts, including but not limited to: \r\n\r\n");
	Terms += _T("Taking advantage of the offer, exchange, post, use Let Learn IELTS aims:\r\n");
	Terms+=_T("\t- Against the State of the Socialist Republic of Vietnam; detrimental to national security, social order and social security; undermining national unity bloc; propaganda war of aggression, terrorism; sowing hatred, conflicts between nations, ethnic, racial, religious\r\n");
	Terms+=_T("\t- Propagate and incite violence, obscene, depraved crime, social evils, superstitions, destructive fine traditions of the nation.\r\n");
	Terms+=_T("\t- Absolutely not discuss, publish content about political issues.\r\n\r\n");
	Terms+=_T("Taking advantage of using IELTS Let Learn to disclose state secrets, military secrets, security, economic, diplomatic and other secrets defined by law in any form on Let Learn IELTS\r\n\r\n");
	Terms+= _T("Advertising, propaganda and purchase goods and services or dissemination is prohibited press works, literature, arts, publications banned on Let Learn IELTS.\r\n\r\nWhen using pictures of other individuals, Users must get the consent of the individual. It is strictly prohibited to use other people's images that violate the honor, dignity and prestige of the picture.\r\n\r\nLet Learn IELTS advantage to collect user information, disclosure of information and data on the private lives of other users or harassment, verbal abuse, annoy, or any lack of cultural behavior when to communicate.\r\n\r\nPutting information distortion, slander, ridicule, insult to reputable organizations and individuals under any form (ridicule, derision, discrimination based on religion, gender, ethnicity ....).\r\n\r\nBehavior, attitude harm the reputation Let Learn IELTS and / or LEARN WORLD in any form or methods.\r\n\r\nStrictly prohibits the promotion of any product in any form, including but not limited to, send, transmit any messages are promotional, invitation, letter chain, investment opportunities on Let Learn IELTS without the consent in writing of LEARN WORLD.\r\n\r\nLet Learn IELTS advantage to organized forms of betting, gambling or agreements relating to cash, cash or kind.\r\n\r\nDisturbing, destroying the host system; Impede access to information and use of legitimate services on Let Learn IELTS.\r\n\r\nUnauthorized use of passwords, encryption keys from organizations, individuals and private information, personal information and internet resources.\r\n\r\nDirectly or indirectly use any device, software, or other means to remove, change, ignore, evade, obstruct, or destroy any copyright, trademark, or the seal other proprietary mark or any control system data, devices, content protection measures as well as measures to restrict access from different geographical regions.\r\n\r\nCreating, reproducing, distributing or advertising the details of any other content, unless otherwise agreed by Let Learn IELTS. Users are not allowed to build business models using the content whether or not for profit; Content is mentioned in Let Learn IELTS including without limitation any text, graphics, images, layout, interface, icons, images, audio and video materials, and stills. Users are not used Let Learn IELTS to provide services to any third parties. Also, LEARN WORLD prohibits the creation of derivative works or materials derived from or based on any content unless it gets permission from the MPT in writing.\r\n\r\nForging organizations, individuals and spreading false information, false information on IELTS Let Learn prejudicing the rights and legitimate interests of organizations and individuals.\r\n\r\n");
	Terms+= _T("Absolutely do not use any program, tool or other means to interfere Let Learn IELTS.\r\n\r\n");
	Terms += _T("Strictly forbidden to distribute, disseminate or cheer for any activity aimed at intervention, sabotage or entering data products provide or host systems Let Learn IELTS. \r\n\r\n");
	Terms += _T("Not to have any act aimed perform any act harmful to the security system of IELTS and Let Learn LEARN WORLD.\r\n\r\n");
	Terms += _T("Prohibits any other infringement of any kind to products, property and prestige LEARN WORLD.");
	UpdateData(FALSE);

	BackButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_RULE_BACK));
	LONG GWLOK = GetWindowLong(BackButton->m_hWnd, GWL_STYLE);
	SetWindowLong(BackButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Back.LoadBitmaps(IDB_BACK, IDB_BACK_PRESSED, 0, 0);
	Back.SubclassDlgItem(IDC_RULE_BACK, this);
	Back.SizeToContent();


	label.SetText(L"Agreement \n Please review the terms before register an account");
	label.SetFontBold(TRUE);
	label.SetFontSize(17);

	GetDlgItem(IDC_RULE_BACK)->SetFocus();

	return FALSE;  // return TRUE  unless you set the focus to a control
}
void RuleDlg::OnPaint()
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
void RuleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

	if (nID == SC_CLOSE)
	{
		if (CurRULE != NULL);
			//delete CurRULE;
	}
	
	CDialogEx::OnSysCommand(nID, lParam);
}


void RuleDlg::OnBnClickedRuleBack()
{
	this->ShowWindow(FALSE);
}

BOOL RuleDlg::OnEraseBkgnd(CDC * pDC)
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