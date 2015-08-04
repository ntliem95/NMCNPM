
// Learn World ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Learn World Server.h"
#include "Learn World ServerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLearnWorldServerDlg dialog



CLearnWorldServerDlg::CLearnWorldServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLearnWorldServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLearnWorldServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLearnWorldServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_START, &CLearnWorldServerDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_DISCONNECT, &CLearnWorldServerDlg::OnBnClickedDisconnect)
	ON_MESSAGE(WM_SOCKET, &CLearnWorldServerDlg::DatabaseManage)
END_MESSAGE_MAP()

void CLearnWorldServerDlg::OnPaint()
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

HCURSOR CLearnWorldServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLearnWorldServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		DisconnectClient();
	}
	CDialogEx::OnSysCommand(nID, lParam);
}

BOOL CLearnWorldServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	LoadData();
	NumberOfClient = 0;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLearnWorldServerDlg::LoadData()
{
	CString B;
	CString temp;
	FILE *fStream1;
	errno_t e = _tfopen_s(&fStream1, _T("Admin.txt"), _T("rt,ccs=UNICODE"));
	if (e != 0) return ; // failed..CString sRead;
	CStdioFile f1(fStream1);  // open the file from this stream
	f1.ReadString(temp);
	AdminLength = _wtoi(temp);
	for (int i = 0; i < AdminLength; i++)
	{
		Administrator A;
		f1.ReadString(A._User);
		f1.ReadString(A._Pass);
		f1.ReadString(A._Name);
		f1.ReadString(temp);
		A._Db.iDay = _wtoi(temp);
		f1.ReadString(temp);
		A._Db.iMonth = _wtoi(temp);
		f1.ReadString(temp);
		A._Db.iYear = _wtoi(temp);
		f1.ReadString(A._Gender);
		f1.ReadString(A._Add);
		f1.ReadString(A._Phone);
		AdminList.push_back(A);
	}
	f1.Close();

	FILE *fStream2;
	errno_t e1 = _tfopen_s(&fStream2, _T("User.txt"), _T("rt,ccs=UNICODE"));
	if (e1 != 0) return; // failed..CString sRead;
	CStdioFile f2(fStream2);  // open the file from this stream
	f2.ReadString(temp);
	UserLength = _wtoi(temp);
	for (int i = 0; i < UserLength; i++)
	{
		User A;
		f2.ReadString(A._User);
		f2.ReadString(A._Pass);
		f2.ReadString(A._Name);
		f2.ReadString(temp);
		A._Db.iDay = _wtoi(temp);
		f2.ReadString(temp);
		A._Db.iMonth = _wtoi(temp);
		f2.ReadString(temp);
		A._Db.iYear = _wtoi(temp);
		f2.ReadString(A._Gender);
		f2.ReadString(A._Add);
		f2.ReadString(A._Phone);
		f2.ReadString(A.Rating);
		UserList.push_back(A);
	}
	f2.Close();

	FILE *fStream3;
	errno_t e2 = _tfopen_s(&fStream3, _T("Teacher.txt"), _T("rt,ccs=UNICODE"));
	if (e2 != 0) return; // failed..CString sRead;
	CStdioFile f3(fStream3);  // open the file from this stream
	f3.ReadString(temp);
	TeacherLength = _wtoi(temp);
	for (int i = 0; i < TeacherLength; i++)
	{
		Teacher A;
		f3.ReadString(A._User);
		f3.ReadString(A._Pass);
		f3.ReadString(A._Name);
		f3.ReadString(temp);
		A._Db.iDay = _wtoi(temp);
		f3.ReadString(temp);
		A._Db.iMonth = _wtoi(temp);
		f3.ReadString(temp);
		A._Db.iYear = _wtoi(temp);
		f3.ReadString(A._Gender);
		f3.ReadString(A._Add);
		f3.ReadString(A._Phone);
		f3.ReadString(A.Rating);
		f3.ReadString(A.NumberOfRating);
		TeacherList.push_back(A);
	}
	f3.Close();

	FILE *fStream4;
	errno_t e3 = _tfopen_s(&fStream4, _T("Deactivated.txt"), _T("rt,ccs=UNICODE"));
	if (e3 != 0) return; // failed..CString sRead;
	CStdioFile f4(fStream4);  // open the file from this stream
	f4.ReadString(temp);
	int N = _wtoi(temp);
	for (int i = 0; i < N; i++)
	{
		CString A;
		f4.ReadString(A);
		DeactivatedAccount.push_back(A);
	}
	f4.Close();
}

void CLearnWorldServerDlg::SaveData()
{
	CString B;
	wstring temp;
	FILE *fStream1;
	errno_t e = _tfopen_s(&fStream1, _T("Admin.txt"), _T("wt,ccs=UNICODE"));
	if (e != 0) return ; // failed..CString sRead;
	CStdioFile f1(fStream1);  // open the file from this stream
	temp = to_wstring(AdminList.size());
	f1.WriteString(temp.c_str());
	f1.WriteString(L"\n");
	for (int i = 0; i < AdminList.size(); i++)
	{
		f1.WriteString(AdminList[i]._User + L"\n");
		f1.WriteString(AdminList[i]._Pass + L"\n");
		f1.WriteString(AdminList[i]._Name + L"\n");
		f1.WriteString(to_wstring(AdminList[i]._Db.iDay).c_str());
		f1.WriteString(L"\n");
		f1.WriteString(to_wstring(AdminList[i]._Db.iMonth).c_str() );
		f1.WriteString(L"\n");
		f1.WriteString(to_wstring(AdminList[i]._Db.iYear).c_str() );
		f1.WriteString(L"\n");
		f1.WriteString(AdminList[i]._Gender + L"\n");
		f1.WriteString(AdminList[i]._Add + L"\n");
		f1.WriteString(AdminList[i]._Phone + L"\n");
	}
	f1.Close();

	FILE *fStream2;
	errno_t e1 = _tfopen_s(&fStream2, _T("User.txt"), _T("wt,ccs=UNICODE"));
	if (e1 != 0) return; // failed..CString sRead;
	CStdioFile f2(fStream2);  // open the file from this stream
	temp = to_wstring(UserList.size());
	f2.WriteString(temp.c_str());
	f2.WriteString(L"\n");
	for (int i = 0; i < UserList.size(); i++)
	{
		f2.WriteString(UserList[i]._User + L"\n");
		f2.WriteString(UserList[i]._Pass + L"\n");
		f2.WriteString(UserList[i]._Name + L"\n");
		f2.WriteString(to_wstring(UserList[i]._Db.iDay).c_str());
		f2.WriteString(L"\n");
		f2.WriteString(to_wstring(UserList[i]._Db.iMonth).c_str());;
		f2.WriteString(L"\n");
		f2.WriteString(to_wstring(UserList[i]._Db.iYear).c_str());
		f2.WriteString(L"\n");
		f2.WriteString(UserList[i]._Gender + L"\n");
		f2.WriteString(UserList[i]._Add + L"\n");
		f2.WriteString(UserList[i]._Phone + L"\n");
		f2.WriteString(UserList[i].Rating + L"\n");
	}
	f2.Close();

	FILE *fStream3;
	errno_t e2 = _tfopen_s(&fStream3, _T("Teacher.txt"), _T("wt,ccs=UNICODE"));
	if (e2 != 0) return; // failed..CString sRead;
	CStdioFile f3(fStream3);  // open the file from this stream
	temp = to_wstring(TeacherList.size());
	f3.WriteString(temp.c_str());
	f3.WriteString(L"\n");
	for (int i = 0; i < TeacherList.size(); i++)
	{
		f3.WriteString(TeacherList[i]._User + L"\n");
		f3.WriteString(TeacherList[i]._Pass + L"\n");
		f3.WriteString(TeacherList[i]._Name + L"\n");
		f3.WriteString(to_wstring(TeacherList[i]._Db.iDay).c_str());
		f3.WriteString(L"\n");
		f3.WriteString(to_wstring(TeacherList[i]._Db.iMonth).c_str());;
		f3.WriteString(L"\n");
		f3.WriteString(to_wstring(TeacherList[i]._Db.iYear).c_str());
		f3.WriteString(L"\n");
		f3.WriteString(TeacherList[i]._Gender + L"\n");
		f3.WriteString(TeacherList[i]._Add + L"\n");
		f3.WriteString(TeacherList[i]._Phone + L"\n");
		f3.WriteString(TeacherList[i].Rating + L"\n");
		f3.WriteString(TeacherList[i].NumberOfRating + L"\n");
	}
	f3.Close();

	FILE *fStream4;
	errno_t e3 = _tfopen_s(&fStream4, _T("Deactivated.txt"), _T("wt,ccs=UNICODE"));
	if (e3 != 0) return; // failed..CString sRead;
	CStdioFile f4(fStream4);  // open the file from this stream
	temp = to_wstring(DeactivatedAccount.size());
	f4.WriteString(temp.c_str());
	f4.WriteString(L"\n");
	for (int i = 0; i < DeactivatedAccount.size(); i++)
	{
		f4.WriteString(DeactivatedAccount[i] + L"\r\n");
	}
	f4.Close();
}

void CLearnWorldServerDlg::DisconnectClient()
{
	//xuất và send thông báo

	//
	AdminOnline.clear();
	TeacherOnline.clear();
	UserOnline.clear();
	for (int i = 0; i < NumberOfClient; i++)
	{
		closesocket(ClientSocket[i]);
	}
	NumberOfClient = 0;
	closesocket(Server);
}

void CLearnWorldServerDlg::OnBnClickedStart()
{
	// TODO: Add your control notification handler code here
	NumberOfClient = 0;
	UpdateData();
	int on = 1;
	Server = socket(AF_INET, SOCK_STREAM, 0);
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(PORT);
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	setsockopt(Server, SOL_SOCKET, SO_REUSEADDR, (char*)on, sizeof(on));

	bind(Server, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));

	listen(Server, SOMAXCONN); //SOMAXCONN

	int err = WSAAsyncSelect(Server, m_hWnd, WM_SOCKET, FD_READ | FD_ACCEPT | FD_CLOSE);
	if (err) MessageBox((LPCTSTR)"Cant call WSAAsyncSelect");
}

void CLearnWorldServerDlg::OnBnClickedDisconnect()
{
	// TODO: Add your control notification handler code here
	int check;
	check = MessageBox(L"Are you sure you want to disconnect Server ?\nThis will cause ALL clients lose connection to server", L"Warning", MB_YESNO);
	if (check == IDYES)
		DisconnectClient();
}

char* CLearnWorldServerDlg::ConvertToChar(const CString &s)
{
	int nSize = s.GetLength();
	char *pAnsiString = new char[nSize + 1];
	memset(pAnsiString, 0, nSize + 1);
	wcstombs(pAnsiString, s, nSize + 1);
	return pAnsiString;
}

void CLearnWorldServerDlg::SendString(SOCKET sk, CString Message)
{
	int Len = Message.GetLength();
	Len += Len;
	PBYTE sendBuff = new BYTE[1000];
	memset(sendBuff, 0, 1000);
	memcpy(sendBuff, (PBYTE)(LPCTSTR)Message, Len);
	send(sk, (char*)&Len, sizeof(Len), 0);
	send(sk, (char*)sendBuff, Len, 0);
	delete sendBuff;
}

int CLearnWorldServerDlg::RecvString(SOCKET sk, CString &Message)
{
	PBYTE buffer = new BYTE[1000];
	memset(buffer, 0, 1000);
	recv(sk, (char*)&buffLength, sizeof(int), 0);
	recv(sk, (char*)buffer, buffLength, 0);
	TCHAR* ttc = (TCHAR*)buffer;
	Message = ttc;

	if (Message.GetLength() == 0)
		return -1;
	return 0;

}

void CLearnWorldServerDlg::SplitFlag(CString src, CString des[2])
{
	int p1, p2;

	p1 = src.Find(_T("\r\n"), 0);
	des[0] = src.Mid(0, p1);

	p2 = src.Find(_T("\r\n"), p1 + 1);
	des[1] = src.Mid(p1 + 2, p2 - (p1+2));

}

void CLearnWorldServerDlg::SplitString(CString src, CString des[10])
{
	int p[10];

	for (int i = 0; i < 10; i++)
	{
		if (i == 0)
		{
			p[i] = src.Find(_T("*&*"), 0);
			if (p[i] == -1)
				return;
			des[i] = src.Mid(0, p[i]);
		}
		else
		{
			p[i] = src.Find(_T("*&*"), p[i-1] + 1);
			if (p[i] == -1)
				return;
			des[i] = src.Mid(p[i-1] + 3, p[i] - (p[i-1] + 3));
		}
			
	}
}

void CLearnWorldServerDlg::OnSignIn(SOCKET SK ,CString Content)
{
	CString Command;
	wstring day, month, year;
	CString Info[10]; //0 = User , 1 = Pass
	SplitString(Content, Info);
	int check = -1; // -2 = online , -1 = wrong info , 0 = admin, 1 = teacher , 2 = user
	int post = -1;
	for (int i = 0; i < AdminList.size(); i++)
		if (Info[0].Compare(AdminList[i]._User) == 0 && Info[1].Compare(AdminList[i]._Pass) == 0)
		{
			for (int j = 0; j < AdminOnline.size(); j++)
			{
				if (i == AdminOnline[j])
				{
					check = -2;
					goto mark;
				}
			}
			post = i;
			check = 0;
			goto mark;
		}
	for (int i = 0; i < TeacherList.size(); i++)
		if (Info[0].Compare(TeacherList[i]._User) == 0 && Info[1].Compare(TeacherList[i]._Pass) == 0)
		{
			for (int j = 0; j < DeactivatedAccount.size(); j++)
				if (TeacherList[i]._User.Compare(DeactivatedAccount[j]) == 0)
				{
					check = -3;
					goto mark;
				}
			for (int j = 0; j < TeacherOnline.size(); j++)
			{
				if (i == TeacherOnline[j])
				{
					check = -2;
					goto mark;
				}
			}
			post = i;
			check = 1;
			goto mark;
		}
	for (int i = 0; i < UserList.size(); i++)
		if (Info[0].Compare(UserList[i]._User) == 0 && Info[1].Compare(UserList[i]._Pass) == 0)
		{
			for (int j = 0; j < DeactivatedAccount.size(); j++)
				if (UserList[i]._User.Compare(DeactivatedAccount[j]) == 0)
				{
					check = -3;
					goto mark;
				}
			for (int j = 0; j < UserOnline.size(); j++)
			{
				if (i == UserOnline[j])
				{
					check = -2;
					goto mark;
				}
			}
			post = i;
			check = 2;
			goto mark;
		}
	mark:
	switch (check)
	{
	case -3: // Deactivated
		Command = L"-1\r\n-1\r\n";
		break;
	case -2: // Online
		Command = L"-1\r\n0\r\n";
		break;
	case -1: // Wrong pass or User
		Command = L"-1\r\n1\r\n";
		break;
	case 0: // Admin
		AdminOnline.push_back(post);
		day = to_wstring(AdminList[post]._Db.iDay);
		month = to_wstring(AdminList[post]._Db.iMonth);
		year = to_wstring(AdminList[post]._Db.iYear);
		Command = L"1507\r\n" + AdminList[post]._User  +L"*&*" + AdminList[post]._Pass + L"*&*";
		Command += AdminList[post]._Name + L"*&*" + day.c_str() + L"*&*" + month.c_str() + L"*&*" + year.c_str() + L"*&*" + AdminList[post]._Gender + L"*&*" + AdminList[post]._Add + L"*&*" + AdminList[post]._Phone + L"*&*\r\n";
		SendString(SK, Command);
		Command = L"1\r\n0\r\n";
		break;
	case 1: // Teacher
		TeacherOnline.push_back(post);

		day = to_wstring(TeacherList[post]._Db.iDay);
		month = to_wstring(TeacherList[post]._Db.iMonth);
		year = to_wstring(TeacherList[post]._Db.iYear);
		Command = L"1507\r\n" + TeacherList[post]._User +L"*&*" + TeacherList[post]._Pass + L"*&*";
		Command += TeacherList[post]._Name + L"*&*" + day.c_str() + L"*&*" + month.c_str() + L"*&*" + year.c_str() + L"*&*" + TeacherList[post]._Gender + L"*&*" + TeacherList[post]._Add + L"*&*" + TeacherList[post]._Phone + L"*&*\r\n";
		SendString(SK, Command);
		Command = L"1\r\n1\r\n";
		break;
	case 2: // User
		UserOnline.push_back(post);

		day = to_wstring(UserList[post]._Db.iDay);
		month = to_wstring(UserList[post]._Db.iMonth);
		year = to_wstring(UserList[post]._Db.iYear);
		Command = L"1507\r\n" + UserList[post]._User +L"*&*" + UserList[post]._Pass + L"*&*";
		Command += UserList[post]._Name + L"*&*" + day.c_str() + L"*&*" + month.c_str() + L"*&*" + year.c_str() + L"*&*" + UserList[post]._Gender + L"*&*" + UserList[post]._Add + L"*&*" + UserList[post]._Phone + L"*&*\r\n";
		SendString(SK, Command);
		Command = L"1\r\n2\r\n";
		
		break;
	}
	SendString(SK, Command);
}

void CLearnWorldServerDlg::OnRegister(SOCKET SK, CString Content)
{
	CString Command;
	wstring day, month, year;
	CString Info[10]; //Array of String contain Account Info
	SplitString(Content, Info);
	int check = 0; // -1 = trùng , 0 = ok
	int post = -1;
	for (int i = 0; i < AdminList.size(); i++)
		if (Info[0].Compare(AdminList[i]._User) == 0)
		{
			check = -1;
			goto mark;
		}
	for (int i = 0; i < TeacherList.size(); i++)
		if (Info[0].Compare(TeacherList[i]._User) == 0 )
		{
			check = -1;
			goto mark;
		}
	for (int i = 0; i < UserList.size(); i++)
		if (Info[0].Compare(UserList[i]._User) == 0)
		{
			check = -1;
			goto mark;
		}
mark :
	if (check == -1)
	{
		Command = "-1\r\n2\r\n";
	}
	else
	{
		User A;
		A._User = Info[0];
		A._Pass = Info[1];
		A._Name = Info[3];
		A._Db.iDay = _ttoi(Info[4]);
		A._Db.iMonth = _ttoi(Info[5]);
		A._Db.iYear = _ttoi(Info[6]);
		A._Gender = Info[7];
		A._Add = Info[8];
		A._Phone = Info[9];
		UserList.push_back(A);
		post = UserList.size() - 1;
		Command = L"1507\r\n" + UserList[post]._User  +L"*&*" + UserList[post]._Pass + L"*&*";
		Command += UserList[post]._Name + L"*&*" + day.c_str() + L"*&*" + month.c_str() + L"*&*" + year.c_str() + L"*&*" + UserList[post]._Gender + L"*&*" + UserList[post]._Add + L"*&*" + UserList[post]._Phone + L"*&*\r\n";
		SendString(SK, Command);
		Command = L"1\r\n2\r\n";
		UserOnline.push_back(post);
	}
	SendString(SK, Command);
}

void CLearnWorldServerDlg::OnForgotPass(SOCKET SK, CString Content)
{
	CString Command;
	CString Info[10]; //0 = flag , flag == 0 => 1 = UserNam , 2 = Phone
						//		 , flag == 1 => 1 = UserName , 2 = Pass
	SplitString(Content, Info);
	int flag = _ttoi(Info[0]);
	int check = 0; // 0 = not found , 1 = found Adnin , 2 = found User , 3 = found Teacher
	int post = -1;
	for (int i = 0; i < AdminList.size(); i++)
		if (Info[1].Compare(AdminList[i]._User) == 0)
		{
			post = i;
			check = 1;
			goto mark;
		}
	for (int i = 0; i < TeacherList.size(); i++)
		if (Info[1].Compare(TeacherList[i]._User) == 0)
		{
			post = i;
			check = 2;
			goto mark;
		}
	for (int i = 0; i < UserList.size(); i++)
		if (Info[1].Compare(UserList[i]._User) == 0)
		{
			post = i;
			check = 3;
			goto mark;
		}
mark:
	if (flag == 0) // Confirm Usernam and Phone
	{
		if (check == 0)
		{
			Command = "-1\r\n0\r\n";
			SendString(SK, Command);
			return;
		}
		if (AdminList[post]._Phone.Compare(Info[2]) == 0 
			|| TeacherList[post]._Phone.Compare(Info[2]) == 0 
			|| UserList[post]._Phone.Compare(Info[2]) == 0) 
		{
			Command = "0\r\n0\r\n";
			SendString(SK, Command);
			return;
		}
		Command = "-1\r\n1\r\n";
		SendString(SK, Command);
		return;
	}
	if (flag == 1)
	{
		if (check == 1) // Admin
		{
			AdminList[post]._Pass = Info[2];
		}
		if (check == 2) // Teacher
		{
			TeacherList[post]._Pass = Info[2];
		}
		if (check == 3) // User
		{
			UserList[post]._Pass = Info[2];
		}
		Command = "0\r\n1\r\n";
		SendString(SK, Command);
		return;
	}
}

void CLearnWorldServerDlg::OnSignOut(SOCKET SK, CString Content)
{
	CString Command;
	wstring day, month, year;
	CString Info[10]; //0 = Flag , 1 = Username
	SplitString(Content, Info);
	int check = -1; // -2 = online , -1 = wrong info , 0 = admin, 1 = teacher , 2 = user
	int post = -1;
	if (_ttoi(Info[0]) == 0) // Admin
	{
		for (int i = 0; i < AdminList.size(); i++)
			if (AdminList[i]._User.Compare(Info[1]) == 0)
			{
				post = i;
				break;
			}
		for (int i = 0; i < AdminOnline.size(); i++)
			if (AdminOnline[i] == post)
			{
				AdminOnline.erase(AdminOnline.begin() + i);
				return;
			}
	}
	if (_ttoi(Info[0]) == 1) // Teacher
	{
		for (int i = 0; i < TeacherList.size(); i++)
			if (TeacherList[i]._User.Compare(Info[1]) == 0)
			{
				post = i;
				break;
			}
		for (int i = 0; i < TeacherOnline.size(); i++)
			if (TeacherOnline[i] == post)
			{
				TeacherOnline.erase(TeacherOnline.begin() + i);
				return;
			}
	}
	if (_ttoi(Info[0]) == 2) // Student
	{
		for (int i = 0; i < UserList.size(); i++)
			if (UserList[i]._User.Compare(Info[1]) == 0)
			{
				post = i;
				break;
			}
		for (int i = 0; i < UserOnline.size(); i++)
			if (UserOnline[i] == post)
			{
				UserOnline.erase(UserOnline.begin() + i);
				return;
			}
	}
	//SendString(SK, Command);

}

void CLearnWorldServerDlg::OnEditInfo(SOCKET SK, CString Content)
{
	CString Command;
	wstring day, month, year;
	CString Info[10]; //0 = Username
	SplitString(Content, Info);
	int check = -1; // 0 = admin, 1 = teacher , 2 = user
	int post = -1;
	for (int i = 0; i < AdminList.size() ; i++)
		if (AdminList[i]._User.Compare(Info[0]) == 0)
		{
			AdminList[i]._Name = Info[1];
			AdminList[i]._Db.iDay = _ttoi(Info[2]);
			AdminList[i]._Db.iMonth = _ttoi(Info[3]);
			AdminList[i]._Db.iYear = _ttoi(Info[4]);
			AdminList[i]._Gender = Info[5];
			AdminList[i]._Add = Info[6];
			AdminList[i]._Phone = Info[7];		
			return;
		}
	for (int i = 0; i < TeacherList.size(); i++)
		if (TeacherList[i]._User.Compare(Info[0]) == 0)
		{
			TeacherList[i]._Name = Info[1];
			TeacherList[i]._Db.iDay = _ttoi(Info[2]);
			TeacherList[i]._Db.iMonth = _ttoi(Info[3]);
			TeacherList[i]._Db.iYear = _ttoi(Info[4]);
			TeacherList[i]._Gender = Info[5];
			TeacherList[i]._Add = Info[6];
			TeacherList[i]._Phone = Info[7];
			return;
		}
	for (int i = 0; i < UserList.size(); i++)
		if (UserList[i]._User.Compare(Info[0]) == 0)
		{
			UserList[i]._Name = Info[1];
			UserList[i]._Db.iDay = _ttoi(Info[2]);
			UserList[i]._Db.iMonth = _ttoi(Info[3]);
			UserList[i]._Db.iYear = _ttoi(Info[4]);
			UserList[i]._Gender = Info[5];
			UserList[i]._Add = Info[6];
			UserList[i]._Phone = Info[7];
			return;
		}
}

void CLearnWorldServerDlg::OnAddTeacher(SOCKET SK, CString Content)
{
	CString Command;
	wstring day, month, year;
	CString Info[10]; //0 = Username
	SplitString(Content, Info);
	int check = -1; // 0 = admin, 1 = teacher , 2 = user
	int post = -1;
	for (int i = 0; i < TeacherList.size(); i++)
		if (TeacherList[i]._User.Compare(Info[0]) == 0)
		{
			SendString(SK, L"-1\r\n");
			return;
		}

	Teacher A;
	A._User = Info[0];
	A._Pass = Info[1];
	A._Name = Info[2];
	A._Db.iDay = _ttoi(Info[3]);
	A._Db.iMonth = _ttoi(Info[4]);
	A._Db.iYear = _ttoi(Info[5]);
	A._Gender = Info[6];
	A._Add = Info[7];
	A._Phone = Info[8];
	A.Rating = L"0";
	A.NumberOfRating = L"0";
	TeacherList.push_back(A);
}

void CLearnWorldServerDlg::OnCreateTable(SOCKET SK, CString Content)
{
	
	CString Command;
	CString temp;
	int check = _ttoi(Content);
	if (check == 1)
	{
		for (int i = 0; i < TeacherList.size(); i++)
		{
				Command = L"15\r\n";
				Command += TeacherList[i]._User + L"*&*";
				Command += TeacherList[i]._Name + L"*&*";
				Command += TeacherList[i]._Phone + L"*&*";
				Command += TeacherList[i].Rating + L"*&*";
				Command += L"\r\n";
				SendString(SK, Command);
		}
	}
	if (check == 2)
	{
		for (int i = 0; i < UserList.size(); i++)
		{
				Command = L"15\r\n";
				Command += UserList[i]._User + L"*&*";
				Command += UserList[i]._Name + L"*&*";
				Command += UserList[i]._Phone + L"*&*";
				Command += UserList[i].Rating + L"*&*";
				Command += L"\r\n";
				SendString(SK, Command);
		}
	}
	if (check == 0)
	{
		for (int i = 0; i < TeacherList.size(); i++)
		{
			Command = L"15\r\n";
			Command += TeacherList[i]._User + L"*&*";
			Command += L"Teacher*&*";
			temp = L"Active";
			for (int j = 0; j < DeactivatedAccount.size(); j++)
				if (TeacherList[i]._User.Compare(DeactivatedAccount[j]) == 0)
				{
					temp = L"Deactivated";
					break;
				}
			Command += temp + L"*&*\r\n";
			SendString(SK, Command);
		}
		for (int i = 0; i < UserList.size(); i++)
		{
			Command = L"15\r\n";
			Command += UserList[i]._User + L"*&*";
			Command += L"Student*&*";
			temp = L"Active";
			for (int j = 0; j < DeactivatedAccount.size(); j++)
				if (UserList[i]._User.Compare(DeactivatedAccount[j]) == 0)
				{
					temp = L"Deactivated";
					break;
				}
			Command += temp + L"*&*\r\n";
			SendString(SK, Command);
		}
	}
}

void CLearnWorldServerDlg::OnSearchAccount(SOCKET SK, CString Content)
{
	CString Command;
	Command = L"-15\r\n";
	SendString(SK, Command);
	for (int i = 0; i < TeacherList.size(); i++)
	{
		if (TeacherList[i]._User.Find(Content, 0) != -1)
		{
			Command = L"15\r\n";
			Command += TeacherList[i]._User + L"*&*";
			Command += L"Teacher*&*";
			Command += TeacherList[i]._Name + L"*&*";
			Command += L"\r\n";
			SendString(SK, Command);
		}
	}
	for (int i = 0; i < UserList.size(); i++)
	{
		if (UserList[i]._User.Find(Content, 0) != -1)
		{
			Command = L"15\r\n";
			Command += UserList[i]._User + L"*&*";
			Command += L"Student*&*";
			Command += UserList[i]._Name + L"*&*";
			Command += L"\r\n";
			SendString(SK, Command);
		}
	}
}

void CLearnWorldServerDlg::OnDeleteAccount(SOCKET SK, CString Content)
{
	for (int i = 0; i < TeacherList.size(); i++)
	{
		if (TeacherList[i]._User.Compare(Content) == 0)
		{
			TeacherList.erase(TeacherList.begin() + i);
			return;
		}
	}
	for (int i = 0; i < UserList.size(); i++)
	{
		if (UserList[i]._User.Compare(Content) == 0)
		{
			UserList.erase(UserList.begin() + i);
			return;
		}
	}
}

void CLearnWorldServerDlg::OnDeactivateAccount(SOCKET SK, CString Content)
{
	for (int i = 0; i < TeacherList.size(); i++)
	{
		if (TeacherList[i]._User.Compare(Content) == 0)
		{
			DeactivatedAccount.push_back(TeacherList[i]._User);
			return;
		}
	}
	for (int i = 0; i < UserList.size(); i++)
	{
		if (UserList[i]._User.Compare(Content) == 0)
		{
			DeactivatedAccount.push_back(UserList[i]._User);
			return;
		}
	}
}

void CLearnWorldServerDlg::OnActivateAccount(SOCKET SK, CString Content)
{
	for (int i = 0; i < TeacherList.size(); i++)
		if (TeacherList[i]._User.Compare(Content) == 0)
			for (int j = 0; j < DeactivatedAccount.size(); j++)
				if (Content.Compare(DeactivatedAccount[j]) == 0)
				{
					DeactivatedAccount.erase(DeactivatedAccount.begin() + j);
					return;
				}
	for (int i = 0; i < UserList.size(); i++)
		if (UserList[i]._User.Compare(Content) == 0)
			for (int j = 0; j < DeactivatedAccount.size(); j++)
				if (Content.Compare(DeactivatedAccount[j]) == 0)
				{
					DeactivatedAccount.erase(DeactivatedAccount.begin() + j);
					return;
				}
}

void CLearnWorldServerDlg::OnSearchTeacher(SOCKET SK, CString Content)
{
	CString Command;
	Command = L"-15\r\n";
	SendString(SK, Command);
	for (int i = 0; i < TeacherList.size(); i++)
	{
		if (TeacherList[i]._User.Find(Content, 0) != -1)
		{
			Command = L"15\r\n";
			Command += TeacherList[i]._User + L"*&*";
			Command += TeacherList[i]._Name + L"*&*";
			Command += TeacherList[i]._Phone + L"*&*";
			Command += TeacherList[i].Rating + L"*&*";
			Command += L"\r\n";
			SendString(SK, Command);
		}
	}
}

void CLearnWorldServerDlg::OnSearchUser(SOCKET SK, CString Content)
{
	CString Command;
	Command = L"-15\r\n";
	SendString(SK, Command);
	for (int i = 0; i < UserList.size(); i++)
	{
		if (UserList[i]._User.Find(Content, 0) != -1)
		{
			Command = L"15\r\n";
			Command += UserList[i]._User + L"*&*";
			Command += UserList[i]._Name + L"*&*";
			Command += UserList[i]._Phone + L"*&*";
			Command += UserList[i].Rating + L"*&*";
			Command += L"\r\n";
			SendString(SK, Command);
		}
	}
}

void  CLearnWorldServerDlg::OnEvaluateTeacher(SOCKET SK, CString Content)
{
	CString Command;
	CString Info[10]; //0 = Username
	SplitString(Content, Info);
	if (_ttoi(Info[0]) == 0)
	{
		for (int i = 0; i < TeacherList.size(); i++)
		{
			if (Info[1].Compare(TeacherList[i]._User) == 0)
			{
				Command = L"16\r\n";
				Command += TeacherList[i].NumberOfRating + L"\r\n";
				SendString(SK,Command);
			}
		}
	}
	else
	{
		for (int i = 0; i < TeacherList.size(); i++)
		{
			if (Info[1].Compare(TeacherList[i]._User) == 0)
			{
				int nRating = _ttoi(TeacherList[i].NumberOfRating);
				TeacherList[i].NumberOfRating = to_wstring(nRating + 1).c_str();
				TeacherList[i].Rating = Info[2];
			}
		}
		SaveData();
	}
}

LRESULT CLearnWorldServerDlg::DatabaseManage(WPARAM wParam, LPARAM lParam)
{
	CString Command;
	if (WSAGETSELECTERROR(lParam))
	{
		// Display the error and close the socket
		closesocket(wParam);
	}
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
	{
		ClientSocket[NumberOfClient] = accept(wParam, NULL, NULL);
		NumberOfClient++;
		break;
	}
	case FD_READ:
	{
		int post = -1, dpos = -1;

		for (int i = 0; i<NumberOfClient; i++)
		{
			if (ClientSocket[i] == wParam)
			{
				if (i<NumberOfClient)
					post = i;
			}
		}
		CString strResult[2];
		CString temp;
		if (RecvString(wParam, temp) < 0)
			break;
		SplitFlag(temp, strResult);
		int flag = _ttoi(strResult[0]);
		
		switch (flag)
		{
			case -1 : // Logout
				OnSignOut(wParam, strResult[1]);
				break;
			case 0://Login
				OnSignIn(wParam ,strResult[1]);
				break;
			case 1://Register
				OnRegister(wParam, strResult[1]);
				SaveData();
				break;
			case 2://Forgot password
				OnForgotPass(wParam, strResult[1]);
				SaveData();
				break;
			case 3:// Edit Information
				OnEditInfo(wParam, strResult[1]);
				SaveData();
				break;
			case 4: // Add Teacher
				OnAddTeacher(wParam,strResult[1]);
				SaveData();
				break;
			case 13: // Search Teacher
				OnSearchTeacher(wParam, strResult[1]);
				break;
			case 14: // Search User
				OnSearchUser(wParam, strResult[1]);
				break;
			case 15: // Get user list to create table
				OnCreateTable(wParam, strResult[1]);
				break;
			case 16: // Search Username for Delete / Deactivated / Activate
				OnSearchAccount(wParam, strResult[1]);
				break;
			case 17: // Delete Account
				OnDeleteAccount(wParam, strResult[1]);
				SaveData();
				break;
			case 18: // Deactivate Account
				OnDeactivateAccount(wParam, strResult[1]);
				SaveData();
				break;
			case 19: // Activate Account
				OnActivateAccount(wParam, strResult[1]);
				SaveData();
				break;
			case 20: //Rate teacher
				OnEvaluateTeacher(wParam, strResult[1]);
				break;
		}
		break;
	}

	case FD_CLOSE:
	{
		//MessageBox(L"Client closed connection", NULL, MB_OK);
		UpdateData();
		int post = -1;
		for (int i = 0; i<NumberOfClient; i++)
		{
			if (ClientSocket[i] == wParam)
			{
				if (i<NumberOfClient)
					post = i;
			}
		}
		closesocket(wParam);
		for (int j = post; j < NumberOfClient; j++)
		{
			ClientSocket[post] = ClientSocket[post + 1];
		}
		
		NumberOfClient--;
		UpdateData(FALSE);
		if (NumberOfClient == 0);
		break;
	}

	}
	return 0;
}