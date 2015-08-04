// ViewRateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "ViewRateDlg.h"
#include "afxdialogex.h"
#include "AdminDlg.h"
#include "StudentDlg.h"
#include "TeacherDlg.h"
// ViewRateDlg dialog
ViewRateDlg * CurViewRate = NULL;
IMPLEMENT_DYNAMIC(ViewRateDlg, CDialogEx)

ViewRateDlg::ViewRateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ViewRateDlg::IDD, pParent)
	, SearchKey(_T(""))
{

	EnableAutomation();

}

ViewRateDlg::~ViewRateDlg()
{
}

void ViewRateDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void ViewRateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SEARCH, SearchKey);
	DDX_Control(pDX, IDC_LIST2, ListView);
	DDX_Control(pDX, IDC_STA2, AccountList);
	DDX_Control(pDX, IDC_STA1, Search);
}


BEGIN_MESSAGE_MAP(ViewRateDlg, CDialogEx)
	ON_EN_CHANGE(IDC_SEARCH, &ViewRateDlg::OnEnChangeSearch)
	ON_BN_CLICKED(IDC_DELETE_BACK, &ViewRateDlg::OnBnClickedViewRateBack)
	ON_WM_SYSCOMMAND()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_MESSAGE(WM_SOCKET, &ViewRateDlg::MessageControl)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(ViewRateDlg, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IViewRateDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {19657D6C-6854-48F9-B139-581FC07C0B9F}
static const IID IID_IViewRateDlg =
{ 0x19657D6C, 0x6854, 0x48F9, { 0xB1, 0x39, 0x58, 0x1F, 0xC0, 0x7C, 0xB, 0x9F } };

BEGIN_INTERFACE_MAP(ViewRateDlg, CDialogEx)
	INTERFACE_PART(ViewRateDlg, IID_IViewRateDlg, Dispatch)
END_INTERFACE_MAP()

BOOL ViewRateDlg::OnEraseBkgnd(CDC * pDC)
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
void ViewRateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

	if (nID == SC_CLOSE)
	{
		closesocket(*CurSocket);

		if (PreDlg_Of_Evalute == 0)
		{
			AfxGetApp()->m_pMainWnd = CurAdmin;
			StartSocket(CurAdmin->m_hWnd);
			WSAAsyncSelect(*CurSocket, CurAdmin->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
			CurAdmin->ShowWindow(SW_SHOWDEFAULT);
		}
		if (PreDlg_Of_Evalute == 1)
		{
			AfxGetApp()->m_pMainWnd = CurStudent;
			StartSocket(CurStudent->m_hWnd);
			WSAAsyncSelect(*CurSocket, CurStudent->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
			CurStudent->ShowWindow(SW_SHOWDEFAULT);
		}
		this->ShowWindow(SW_HIDE);
	}

	CDialogEx::OnSysCommand(nID, lParam);
	
}
void ViewRateDlg::OnPaint()
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
// ViewRateDlg message handlers
BOOL ViewRateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	WSAAsyncSelect(*CurSocket, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);

	Search.SetFontItalic(TRUE);
	Search.SetFontBold(TRUE);
	Search.SetFontSize(14);

	AccountList.SetFontItalic(TRUE);
	AccountList.SetFontBold(TRUE);
	AccountList.SetFontSize(14);

	//Add SignIn picture
	BackButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_DELETE_BACK));
	LONG GWLOK = GetWindowLong(BackButton->m_hWnd, GWL_STYLE);
	SetWindowLong(BackButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Back.LoadBitmaps(IDB_BACK, IDB_BACK_PRESSED, 0, 0);
	Back.SubclassDlgItem(IDC_DELETE_BACK, this);
	Back.SizeToContent();
	TableSize = 0;
	ListView.SetExtendedStyle(ListView.GetExtendedStyle() | LVS_EX_GRIDLINES);
	ListView.SetExtendedStyle(ListView.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	TableSize = 0;
	ListView.InsertColumn(0, _T("Username"), LVCFMT_LEFT, 100);
	ListView.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 150);
	ListView.InsertColumn(2, _T("Phone"), LVCFMT_LEFT, 100);
	ListView.InsertColumn(3, _T("Rating"), LVCFMT_LEFT, 50);

	ListView.DeleteAllItems();
	if (ViewRateMode == 0)
		SendString(L"15\r\n1\r\n");
	if (ViewRateMode == 1)
		SendString(L"15\r\n2\r\n");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void ViewRateDlg::AddListTable(CString &A)
{
	CString Info[4];
	SplitString(A, Info);
	int Index = ListView.InsertItem(TableSize, Info[0]);
	ListView.SetItemText(Index, 1, Info[1]);
	ListView.SetItemText(Index, 2, Info[2]);
	ListView.SetItemText(Index, 3, Info[3]);
	TableSize++;
}

LRESULT ViewRateDlg::MessageControl(WPARAM wParam, LPARAM lParam)
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
		case -15:
			ListView.DeleteAllItems();
			TableSize = 0;
			break;
		case 15: // Create table
			AddListTable(strResult[1]);
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

void ViewRateDlg::OnEnChangeSearch()
{
	UpdateData(TRUE);
	CString Command;
	if (ViewRateMode == 0)
		Command = L"13\r\n";
	else
		Command = L"14\r\n";
	Command += SearchKey + L"\r\n";
	SendString(Command);
}


void ViewRateDlg::OnBnClickedViewRateBack()
{
	// TODO: Add your control notification handler code here
	closesocket(*CurSocket);

	if (PreDlg_Of_Evalute == 0)
	{
		AfxGetApp()->m_pMainWnd = CurAdmin;
		StartSocket(CurAdmin->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurAdmin->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurAdmin->ShowWindow(SW_SHOWDEFAULT);
	}
	if (PreDlg_Of_Evalute == 1)
	{
		AfxGetApp()->m_pMainWnd = CurStudent;
		StartSocket(CurStudent->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurStudent->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurStudent->ShowWindow(SW_SHOWDEFAULT);
	}
	if (PreDlg_Of_Evalute == 2)
	{
		AfxGetApp()->m_pMainWnd = CurTeacher;
		StartSocket(CurTeacher->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurTeacher->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurTeacher->ShowWindow(SW_SHOWDEFAULT);
	}
	this->ShowWindow(SW_HIDE);
	delete CurViewRate;
	CurViewRate = NULL;
}
