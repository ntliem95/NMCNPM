// EvaluateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "EvaluateDlg.h"
#include "afxdialogex.h"
#include "AdminDlg.h"
#include "StudentDlg.h"
// EvaluateDlg dialog
EvaluateDlg * CurEvaluate = NULL;
IMPLEMENT_DYNAMIC(EvaluateDlg, CDialogEx)

EvaluateDlg::EvaluateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(EvaluateDlg::IDD, pParent)
	, SearchKey(_T(""))
{

}

EvaluateDlg::~EvaluateDlg()
{
}

void EvaluateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, ListView);
	DDX_Text(pDX, IDC_SEARCH, SearchKey);
	DDX_Control(pDX, IDC_STA2, Rating);
	DDX_Control(pDX, IDC_STAT1, AccountList);
	DDX_Control(pDX, IDC_STAT, Search);
}


BEGIN_MESSAGE_MAP(EvaluateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DELETE_BACK, &EvaluateDlg::OnBnClickedDeleteBack)
	ON_EN_CHANGE(IDC_SEARCH, &EvaluateDlg::OnEnChangeSearch)
	ON_WM_SYSCOMMAND()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_SOCKET, &EvaluateDlg::MessageControl)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &EvaluateDlg::OnHdnItemclickList2)
	ON_BN_CLICKED(IDC_Confirm, &EvaluateDlg::OnBnClickedConfirm)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &EvaluateDlg::OnNMClickList2)
END_MESSAGE_MAP()


// EvaluateDlg message handlers
BOOL EvaluateDlg::OnEraseBkgnd(CDC * pDC)
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

	int a = 100;
	for (int i = 0; i < 5; i++)
	{
		CBitmap A;
		A.LoadBitmapW(IDB_STAR);
		dc.SelectObject(&A);
		BITMAP bmap1;
		A.GetBitmap(&bmap1);
		bmw = bmap1.bmWidth; bmh = bmap1.bmHeight;
		pDC->SetStretchBltMode(HALFTONE);
		pDC->TransparentBlt(a+=50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 255, 255));
		DeleteObject(A);
		ReleaseDC(&dc);
	}
	return true;
}
void EvaluateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void EvaluateDlg::OnPaint()
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
BOOL EvaluateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	WSAAsyncSelect(*CurSocket, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);

	Rating.SetFontBold(TRUE);
	Rating.SetFontSize(14);
	Rating.SetFontItalic(TRUE);
	Search.SetFontBold(TRUE);
	Search.SetFontSize(14);
	Search.SetFontItalic(TRUE);
	AccountList.SetFontBold(TRUE);
	AccountList.SetFontSize(14);
	AccountList.SetFontItalic(TRUE);

	//Add SignIn picture
	BackButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_DELETE_BACK));
	LONG GWLOK = GetWindowLong(BackButton->m_hWnd, GWL_STYLE);
	SetWindowLong(BackButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Back.LoadBitmaps(IDB_BACK, IDB_BACK_PRESSED, 0, 0);
	Back.SubclassDlgItem(IDC_DELETE_BACK, this);
	Back.SizeToContent();
	FinishButton = reinterpret_cast<CButton *>(GetDlgItem(IDC_Confirm));
	GWLOK = GetWindowLong(FinishButton->m_hWnd, GWL_STYLE);
	SetWindowLong(FinishButton->m_hWnd, GWL_STYLE, GWLOK | BS_OWNERDRAW);
	Finish.LoadBitmaps(IDB_FINISH, IDB_FINISH_PRESSED, 0, 0);
	Finish.SubclassDlgItem(IDC_Confirm, this);
	Finish.SizeToContent();
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

void EvaluateDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);
	CDC * pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	int bmw, bmh;
	CBitmap A;
	A.LoadBitmapW(IDB_STAR_GOLD);
	CBitmap B;
	B.LoadBitmapW(IDB_STAR);
	BITMAP bmap1;
	A.GetBitmap(&bmap1);
	bmw = bmap1.bmWidth; bmh = bmap1.bmHeight;
	int a = 100;
	
	if (point.x > 150 && point.x < 200 && point.y > 310 && point.y < 360)
	{
		newRating = 1;
		GetDlgItem(IDC_Confirm)->EnableWindow(1);
		if (nItem == -1)
		{
			MessageBox(L"Please choose an teacher inorder to evaluate ", NULL, MB_OK);
			return;
		}
		dc.SelectObject(&A);
		pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
		dc.SelectObject(&B);
		for (int i = 0; i < 4; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
	}
	if (point.x > 200 && point.x < 250 && point.y > 310 && point.y < 360)
	{
		newRating = 2;
		GetDlgItem(IDC_Confirm)->EnableWindow(1);
		if (nItem == -1)
		{
			MessageBox(L"Please choose an teacher inorder to evaluate ", NULL, MB_OK);
			return;
		}
		dc.SelectObject(&A);
		for (int i = 0; i < 2; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
		dc.SelectObject(&B);
		for (int i = 0; i < 3; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
	}
	if (point.x > 250 && point.x < 300 && point.y > 310 && point.y < 360)
	{
		newRating = 3;
		GetDlgItem(IDC_Confirm)->EnableWindow(1);
		if (nItem == -1)
		{
			MessageBox(L"Please choose an teacher inorder to evaluate ", NULL, MB_OK);
			return;
		}
		dc.SelectObject(&A);
		for (int i = 0; i < 3; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
		dc.SelectObject(&B);
		for (int i = 0; i < 2; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
	}
	if (point.x > 300 && point.x < 350 && point.y > 310 && point.y < 360)
	{
		newRating = 4;
		GetDlgItem(IDC_Confirm)->EnableWindow(1);
		if (nItem == -1)
		{
			MessageBox(L"Please choose an teacher inorder to evaluate ", NULL, MB_OK);
			return;
		}
		dc.SelectObject(&A);
		for (int i = 0; i < 4; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
		dc.SelectObject(&B);
		pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
	}
	if (point.x > 350 && point.x < 400 && point.y > 310 && point.y < 360)
	{
		newRating = 5;
		GetDlgItem(IDC_Confirm)->EnableWindow(1);
		if (nItem == -1)
		{
			MessageBox(L"Please choose an teacher inorder to evaluate ", NULL, MB_OK);
			return;
		}
		dc.SelectObject(&A);
		for (int i = 0; i < 5; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
	}
	DeleteObject(B);
	DeleteObject(A);
	ReleaseDC(&dc);
}

void EvaluateDlg::AddListTable(CString &A)
{
	CString Info[4];
	SplitString(A, Info);
	int Index = ListView.InsertItem(TableSize, Info[0]);
	ListView.SetItemText(Index, 1, Info[1]);
	ListView.SetItemText(Index, 2, Info[2]);
	ListView.SetItemText(Index, 3, Info[3]);
	TableSize++;
}

LRESULT EvaluateDlg::MessageControl(WPARAM wParam, LPARAM lParam)
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
		case 16:
			nRating = flag2;
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


void EvaluateDlg::OnBnClickedDeleteBack()
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

	this->ShowWindow(SW_HIDE);
	delete CurEvaluate;
	CurEvaluate = NULL;
}


void EvaluateDlg::OnEnChangeSearch()
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


void EvaluateDlg::OnHdnItemclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

}


void EvaluateDlg::OnBnClickedConfirm()
{
	// TODO: Add your control notification handler code here

	CString Command = L"20\r\n1*&*";
	CString Rate = ListView.GetItemText(nItem, 3);
	int Rating = _ttoi(Rate);
	Command += ListView.GetItemText(nItem, 0) + L"*&*";
	int Point = (Rating * nRating + newRating) / (nRating + 1);
	Command += to_wstring(Point).c_str();
	Command += L"*&*\r\n";
	SendString(Command);
	ListView.SetItemText(nItem, 3, to_wstring(Point).c_str());
	GetDlgItem(IDC_Confirm)->EnableWindow(FALSE);
}


void EvaluateDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	nItem = ListView.GetNextItem(nItem, LVNI_SELECTED);
	CString Username = ListView.GetItemText(nItem, 0);
	CString Command = L"20\r\n0*&*";
	Command += Username + L"*&*\r\n";
	SendString(Command);
	CString Rate = ListView.GetItemText(nItem, 3);
	int Rating = _ttoi(Rate);
	CDC * pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	int bmw, bmh;
	CBitmap A;
	A.LoadBitmapW(IDB_STAR_GOLD);
	CBitmap B;
	B.LoadBitmapW(IDB_STAR);
	BITMAP bmap1;
	A.GetBitmap(&bmap1);
	bmw = bmap1.bmWidth; bmh = bmap1.bmHeight;
	int a = 100;
	if (Rating == 1)
	{
		dc.SelectObject(&A);
		pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
		dc.SelectObject(&B);
		for (int i = 0; i < 4; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
	}
	if (Rating == 2)
	{
		dc.SelectObject(&A);
		for (int i = 0; i < 2; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
		dc.SelectObject(&B);
		for (int i = 0; i < 3; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
	}
	if (Rating == 3)
	{
		dc.SelectObject(&A);
		for (int i = 0; i < 3; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
		dc.SelectObject(&B);
		for (int i = 0; i < 2; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
	}
	if (Rating == 4)
	{
		dc.SelectObject(&A);
		for (int i = 0; i < 4; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
		dc.SelectObject(&B);
		pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
	}
	if (Rating == 5)
	{

		dc.SelectObject(&A);
		for (int i = 0; i < 5; i++)
			pDC->TransparentBlt(a += 50, 310, bmw, bmh, &dc, 0, 0, bmw, bmh, RGB(255, 0, 0));
	}
	DeleteObject(B);
	DeleteObject(A);
	ReleaseDC(&dc);
}
