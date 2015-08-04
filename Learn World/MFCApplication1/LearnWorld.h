
// MFCApplication1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <string>
#include "Label.h"
#include "CommandButton.h"
using namespace std;

// CMFCApplicatian1App:
// See MFCApplication1.cpp for the implementation of this class
//

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

class Date//ngay
{
public:
	unsigned int iDay, iMonth, iYear;//ngay,thang,nam
public:
	Date(){}
	~Date(){}
	const unsigned int getDay() const;//Tra ve ngay
	const unsigned int getMon() const;//Tra ve thang
	const unsigned int getYear() const;//Tra ve nam
	bool IsValid(const unsigned int &day, const unsigned int &mon, const unsigned int &year) const;//kiem tra tinh hop le cua ngay thang
	bool IsLeapYear(const unsigned int &year) const;//Kiem tra nam nhuan
	Date CurrentTime() const;//Lay gio he thong
	bool UpDate(const unsigned int &day, const unsigned int &mon, const unsigned int &year);//Cap nhat ngay thang
	bool operator==(const Date& obj) const;
	bool operator!=(const Date& obj) const;
	bool operator>(const Date& obj) const;
	bool operator>=(const Date& obj) const;
	bool operator<=(const Date& obj) const;
	bool operator<(const Date& obj) const;
	friend ostream& operator<<(ostream& os, const Date& obj);
	friend istream& operator>>(istream& is, Date& obj);
};
class Account
{

public :
	int type;
	CString ID;
	CString UserName;
	CString Pass;
	CString Name;//ho ten
	Date Db;//ngay sinh
	CString Gender;//gioi tinh
	CString Add;//dia chi
	CString Phone;//dien thoai lien lac
};
#define PORT 1507
#define WM_SOCKET WM_USER + 15

extern CMFCApplication1App theApp;

extern SOCKET * CurSocket;

extern Account CurAccount;
static 	CString ServerIP;
extern int isServerOnline;
extern int PreDlg_Of_ForgotPass; // 0 = Sigin , 1 = Admin , 2 = Teacher , 3 = User
extern int PreDlg_Of_EditInfo;
extern int PreDlg_Of_Evalute; //0 = admin , 1 = User;
extern int PreviousSkill; // 0 = write , 1 = Listen , 2 = speak , 3 = read
extern int ViewRateMode; // 0 = Teacher , 1 = User
extern int CheckSkill; //0 = Write , 1 = Listen , 2 = Speak , 3 = Read
static struct sockaddr_in ServerAddress;


static void SplitFlag(CString src, CString des[2])
{
	int p1, p2;

	p1 = src.Find(_T("\r\n"), 0);
	des[0] = src.Mid(0, p1);

	p2 = src.Find(_T("\r\n"), p1 + 1);
	des[1] = src.Mid(p1 + 2, p2 - (p1 + 2));

}

static void SplitString(CString src, CString des[10])
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
			p[i] = src.Find(_T("*&*"), p[i - 1] + 1);
			if (p[i] == -1)
				return;
			des[i] = src.Mid(p[i - 1] + 3, p[i] - (p[i - 1] + 3));
		}

	}
}


static void SendString(CString s)
{
	int Len = s.GetLength();
	Len += Len;
	PBYTE sendBuff = new BYTE[1000];
	memset(sendBuff, 0, 1000);
	memcpy(sendBuff, (PBYTE)(LPCTSTR)s, Len);
	send(*CurSocket, (char*)&Len, sizeof(Len), 0);
	send(*CurSocket, (char*)sendBuff, Len, 0);
	delete sendBuff;
};

static int RecvString(CString &s)
{
	int	buffLength;
	PBYTE buffer = new BYTE[1000];
	memset(buffer, 0, 1000);
	recv(*CurSocket, (char*)&buffLength, sizeof(int), 0);
	recv(*CurSocket, (char*)buffer, buffLength, 0);
	TCHAR* ttc = (TCHAR*)buffer;
	s = ttc;

	if (s.GetLength() == 0)
		return -1;
	return 0;
};

static char* ConvertToChar(const CString &s)
{
	int nSize = s.GetLength();
	char *temp = new char[nSize + 1];
	memset(temp, 0, nSize + 1);
	wcstombs(temp, s, nSize + 1);
	return temp;
};


static int StartSocket(HWND hwnd)
{
	ServerIP = "127.0.0.1";
	if (CurSocket == NULL)
		CurSocket = new SOCKET;
	WSADATA wsaData = { 0 };
	int iResult = 0;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		MessageBox(hwnd,L"WSAStartup failed: %d\n", NULL, MB_OK);
		return 0;
	}

	*CurSocket = socket(AF_INET, SOCK_STREAM, 0);
	hostent* host = NULL;
	if (*CurSocket == INVALID_SOCKET)
	{
		MessageBox(hwnd,_T("socket() failed"), _T("ERROR"), 0);
		return 0;
	}
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(PORT);

	char* cIP = ConvertToChar(ServerIP);

	ServerAddress.sin_addr.s_addr = inet_addr(cIP);

	if (ServerAddress.sin_addr.s_addr == INADDR_NONE)
	{
		host = (gethostbyname(cIP));
		if (host == NULL)
		{
			MessageBox(hwnd,_T("Can't connect to server."), _T("ERROR"), 0);
		}
		CopyMemory(&ServerAddress.sin_addr, host->h_addr_list[0],
			host->h_length);
		return 0;
	}
	int err = connect(*CurSocket, (struct sockaddr*)&ServerAddress, sizeof(ServerAddress));
	if (err == SOCKET_ERROR){
		//MessageBox(hwnd,_T("Can't connect to server. Please try later"), _T("ERROR"), 0);
		return 0;
	}
	return 1;
};

