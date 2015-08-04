// DeleteAccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "DeleteAccountDlg.h"
#include "afxdialogex.h"
#include "AdminDlg.h"

// DeleteAccountDlg dialog
DeleteAccountDlg * CurDelete = NULL;
IMPLEMENT_DYNAMIC(DeleteAccountDlg, CDialogEx)

DeleteAccountDlg::DeleteAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DeleteAccountDlg::IDD, pParent)
	, SearchKey(_T(""))
{

	EnableAutomation();

}

DeleteAccountDlg::~DeleteAccountDlg()
{
}

void DeleteAccountDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void DeleteAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, ListView);
	DDX_Text(pDX, IDC_SEARCH, SearchKey);
	DDX_Control(pDX, IDC_STATI1, Search);
	DDX_Control(pDX, IDC_STATI2, AccountList);
}


BEGIN_MESSAGE_MAP(DeleteAccountDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_SOCKET, &DeleteAccountDlg::MessageControl)
	ON_BN_CLICKED(IDC_DELETE_ACCOUNT, &DeleteAccountDlg::OnBnClickedDeleteAccount)
	ON_EN_CHANGE(IDC_SEARCH, &DeleteAccountDlg::OnEnChangeSearch)
	ON_BN_CLICKED(IDC_DELETE_BACK, &DeleteAccountDlg::OnBnClickedDeleteBack)
	ON_BN_CLICKED(IDC_DEACTIVATE_ACCOUNT, &DeleteAccountDlg::OnBnClickedDeactivateAccount)
	ON_BN_CLICKED(IDC_ACTIVATE_ACCOUNT, &DeleteAccountDlg::OnBnClickedActivateAccount)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(DeleteAccountDlg, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IDeleteAccountDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {477E9F02-E0BE-441B-9D58-DB90DB6E1A5C}
static const IID IID_IDeleteAccountDlg =
{ 0x477E9F02, 0xE0BE, 0x441B, { 0x9D, 0x58, 0xDB, 0x90, 0xDB, 0x6E, 0x1A, 0x5C } };

BEGIN_INTERFACE_MAP(DeleteAccountDlg, CDialogEx)
	INTERFACE_PART(DeleteAccountDlg, IID_IDeleteAccountDlg, Dispatch)
END_INTERFACE_MAP()


// DeleteAccountDlg message handlers
BOOL DeleteAccountDlg::OnEraseBkgnd(CDC * pDC)
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
void DeleteAccountDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

BOOL DeleteAccountDlg::OnInitDialog()
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
	ListView.InsertColumn(1, _T("Role"), LVCFMT_LEFT, 100);
	ListView.InsertColumn(2, _T("Status"), LVCFMT_LEFT,100);
	SendString(L"15\r\n0\r\n");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void DeleteAccountDlg::AddListTable(CString &A)
{
	CString Info[3];
	SplitString(A, Info);
	int Index = ListView.InsertItem(TableSize, Info[0]);
	ListView.SetItemText(Index, 1, Info[1]);
	ListView.SetItemText(Index, 2, Info[2]);
	TableSize++;
}

LRESULT DeleteAccountDlg::MessageControl(WPARAM wParam, LPARAM lParam)
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
		case -15: //Clear table
			ListView.DeleteAllItems();
			TableSize = 0;
			break;
		case 15 : // Create table
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

void DeleteAccountDlg::OnBnClickedDeleteAccount()
{
	// TODO: Add your control notification handler code here
	int  nItem = -1;
	nItem = ListView.GetNextItem(nItem, LVNI_SELECTED);
	if (nItem == -1)
	{
		MessageBox(L"Please choose an account to proceed ", NULL, MB_OK);
	}
	CString Username = ListView.GetItemText(nItem, 0);
	CString Command = L"17\r\n";
	Command += Username + L"\r\n";
	SendString(Command);
	ListView.DeleteItem(nItem);
}


void DeleteAccountDlg::OnEnChangeSearch()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	CString Command = L"16\r\n";
	Command += SearchKey + L"\r\n";
	SendString(Command);
}


void DeleteAccountDlg::OnBnClickedDeleteBack()
{
	// TODO: Add your control notification handler code here
	closesocket(*CurSocket);
	AfxGetApp()->m_pMainWnd = CurAdmin;
	StartSocket(CurAdmin->m_hWnd);
	WSAAsyncSelect(*CurSocket, CurAdmin->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	CurAdmin->ShowWindow(SW_SHOWDEFAULT);
	this->ShowWindow(SW_HIDE);
	delete CurDelete;
	CurDelete = NULL;
}


void DeleteAccountDlg::OnBnClickedDeactivateAccount()
{
	// TODO: Add your control notification handler code here
	int  nItem = -1;
	nItem = ListView.GetNextItem(nItem, LVNI_SELECTED);
	if (nItem == -1)
	{
		MessageBox(L"Please choose an account to proceed ", NULL, MB_OK);
	}
	//ListView.DeleteItem(nItem);
	CString Username = ListView.GetItemText(nItem, 0);
	CString Command = L"18\r\n";
	Command += Username + L"\r\n";
	SendString(Command);
	ListView.SetItemText(nItem, 2, L"Deactivated");
}


void DeleteAccountDlg::OnBnClickedActivateAccount()
{
	// TODO: Add your control notification handler code here
	int  nItem = -1;
	nItem = ListView.GetNextItem(nItem, LVNI_SELECTED);
	if (nItem == -1)
	{
		MessageBox(L"Please choose an account to proceed ", NULL, MB_OK);
	}
	//ListView.DeleteItem(nItem);
	CString Username = ListView.GetItemText(nItem, 0);
	CString Command = L"19\r\n";
	Command += Username + L"\r\n";
	SendString(Command);
	ListView.SetItemText(nItem, 2, L"Active");
}
