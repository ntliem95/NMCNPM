
// Learn World ServerDlg.h : header file
//

#pragma once
#include <fstream>
#include "Administrator.h"
#include "Database.h"
#include "Date.h"
#include "Lesson.h"
#include "Mail.h"
#include "Password.h"
#include "System.h"
#include "Teacher.h"
#include "User.h"
#include <vector>
// CLearnWorldServerDlg dialog
class CLearnWorldServerDlg : public CDialogEx
{
// Construction
public:
	CLearnWorldServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LEARNWORLDSERVER_DIALOG };

	protected:
		void OnOK()
		{

		}
		BOOL PreTranslateMessage(MSG* pMsg)
		{
			switch (pMsg->message)
			{
			case WM_KEYDOWN:

				switch (pMsg->wParam)
				{
				case VK_ESCAPE:
				case VK_CANCEL: return true;

				}
				break;
			}

			return CDialog::PreTranslateMessage(pMsg);
		}
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	LRESULT DatabaseManage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedStart();
	void DisconnectClient(); // Close connection to all Client
	void SendString(SOCKET SK, CString Message); // Send to Client
	int RecvString(SOCKET SK, CString &Message); // Recieve from Client
	char* ConvertToChar(const CString &s);

	void LoadData();
	void SaveData();

	void OnSignIn(SOCKET SK,CString Content);
	void OnRegister(SOCKET SK, CString Content);
	void OnForgotPass(SOCKET SK, CString Content);
	void OnSignOut(SOCKET SK, CString Content);
	void OnEditInfo(SOCKET SK, CString Content);
	void OnAddTeacher(SOCKET SK, CString Content);
	void OnCreateTable(SOCKET SK, CString Content);
	void OnSearchAccount(SOCKET SK, CString Content);
	void OnDeleteAccount(SOCKET SK, CString Content);
	void OnDeactivateAccount(SOCKET SK, CString Content);
	void OnActivateAccount(SOCKET SK, CString Content);
	void OnSearchTeacher(SOCKET SK, CString Content);
	void OnSearchUser(SOCKET SK, CString Content);
	void OnEvaluateTeacher(SOCKET SK, CString Content);


	void SplitFlag(CString src, CString des[2]);
	void SplitString(CString src, CString des[10]);
	int msgType;
	int buffLength,t,lenguser,flagsend,kq, count_sock;
	int first_send;

	int NumberOfClient;
	SOCKET Server, Player; //flag,sclient;
	SOCKET ClientSocket[100]; //User Socket Array
	struct sockaddr_in ServerAddress;

	vector<User> UserList;
	vector<int> UserOnline;
	vector<Administrator> AdminList;
	vector<int> AdminOnline;
	vector<Teacher> TeacherList;
	vector<int> TeacherOnline;
	vector<CString> DeactivatedAccount;
	int UserLength, AdminLength, TeacherLength;

};
#define PORT 1507
#define WM_SOCKET WM_USER + 15