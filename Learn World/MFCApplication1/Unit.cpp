// Unit.cpp : implementation file
//

#include "stdafx.h"
#include "LearnWorld.h"
#include "Unit.h"
#include "afxdialogex.h"
#include "ChooseSkill.h"
#include "Listen1.h"
#include "Read1.h"
#include "Speak1.h"
#include "Write1.h"
// Unit dialog
Unit * CurUnit = NULL;
IMPLEMENT_DYNAMIC(Unit, CDialogEx)

Unit::Unit(CWnd* pParent /*=NULL*/)
	: CDialogEx(Unit::IDD, pParent)
{

	EnableAutomation();

}

Unit::~Unit()
{
}

void Unit::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void Unit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UNIT1, Unit1);
	DDX_Control(pDX, IDC_UNIT2, Unit2);
	DDX_Control(pDX, IDC_UNIT3, Unit3);
	DDX_Control(pDX, IDC_UNIT4, Unit4);
	DDX_Control(pDX, IDC_UNIT5, Unit5);
}


BEGIN_MESSAGE_MAP(Unit, CDialogEx)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_UNIT1, &Unit::OnBnClickedUnit1)
	ON_BN_CLICKED(IDC_UNIT2, &Unit::OnBnClickedUnit2)
	ON_BN_CLICKED(IDC_UNIT3, &Unit::OnBnClickedUnit3)
	ON_BN_CLICKED(IDC_UNIT4, &Unit::OnBnClickedUnit4)
	ON_BN_CLICKED(IDC_UNIT5, &Unit::OnBnClickedUnit5)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Unit, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IUnit to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {7CFB4A91-B51C-48E7-839D-E822E2B9AFC5}
static const IID IID_IUnit =
{ 0x7CFB4A91, 0xB51C, 0x48E7, { 0x83, 0x9D, 0xE8, 0x22, 0xE2, 0xB9, 0xAF, 0xC5 } };

BEGIN_INTERFACE_MAP(Unit, CDialogEx)
	INTERFACE_PART(Unit, IID_IUnit, Dispatch)
END_INTERFACE_MAP()

void Unit::LoadNote()
{
	switch (PreviousSkill)
	{
	case 0:
		this->SetWindowTextW(L"Writing");
		Unit1.SetNote(L"You rented a car recently, but were not satisfied with it.Write a letter of complaint to the rental agency.");
		Unit2.SetNote(L"You have just received a letter from an overseas university saying that your IELTS band score of 6 is too low for admission to any of its Master’s Courses(you need 6.5) .Write a letter to the admissions officer");
		Unit3.SetNote(L"The Internet has dramatically altered our lives over the past few decades.Although some of these changes have been negative, the overall effect of this technology has been positive.");
		Unit4.SetNote(L"Fast food is now universally in most countries and is becoming increasingly popular. Some feel that this is a positive trend, while others do not.");
		Unit5.SetNote(L"International tourism is now more common than ever before. Some feel that this is a positive trend, while others do not.");
		break;
	case 1:
		this->SetWindowTextW(L"Listening");
		Unit1.SetNote(L"You are goint to hear the conversation between Don and Jenny about their plan for the future");
		Unit2.SetNote(L"You are going to hear Debbie giving some advices about health and fitness to nurses");
		Unit4.SetNote(L"You are going to hear a lecturer talking about journalism practised by people who are not professional journalists");
		Unit5.SetNote(L"You are going to hear two students talking about a project on human relationships");
		Unit3.SetNote(L"");
		break;
	case 2:
		this->SetWindowTextW(L"Speaking");
		Unit1.SetNote(L"Describe a place that can be good to relax (not home)");
		Unit2.SetNote(L"Describe a change that will improve your local area");
		Unit3.SetNote(L"Describe a small and successful company you know.");
		Unit4.SetNote(L"Describe an age/stage you enjoyed in your life.");
		Unit5.SetNote(L"Describe a time that a child did something that made you laugh");
		break;
	case 3:
		this->SetWindowTextW(L"Reading");
		Unit2.SetNote(L"ORGANIC FOOD : WHY ? by Rob Lyons and Jan Bowman");
		Unit3.SetNote(L"WHY DONT BABIES TALK LIKE ADULTS ? KIDS DO FROM 'GOO-GOO' TO TALKATIVE ONE STEP AT A TIME by Joshua Hartshorne");
		Unit4.SetNote(L"THE WORLD WIDE WEB FROM IT ORIGINS");
		Unit5.SetNote(L"THE TRUTH ABOUT LYING by Dan Roberts");
		break;
	}
}
// Unit message handlers
BOOL Unit::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect B;
	GetWindowRect(m_rect);
	LoadNote();
	//B.SetRect(m_rect.left, m_rect.top, m_rect.right, 1000);
	//m_rect = B;
	m_nScrollPos = 0;


	return TRUE;
}

void Unit::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
	/*	closesocket(*CurSocket);
		AfxGetApp()->m_pMainWnd = CurStudent;
		StartSocket(CurStudent->m_hWnd);
		WSAAsyncSelect(*CurSocket, CurStudent->m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
		CurStudent->ShowWindow(SW_SHOWDEFAULT);
		this->ShowWindow(SW_HIDE);*/
	}
	CDialogEx::OnSysCommand(nID, lParam);
}

void Unit::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here.
	m_nCurHeight = cy;
	int nScrollMax;
	if (cy < m_rect.Height())
	{
		nScrollMax = m_rect.Height() - cy;
	}
	else
		nScrollMax = 0;

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL; // SIF_ALL = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nScrollMax;
	si.nPage = si.nMax / 10;
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, TRUE);
}

void Unit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default.
	int nDelta;
	int nMaxPos = m_rect.Height() - m_nCurHeight;

	switch (nSBCode)
	{
	case SB_LINEDOWN:
		if (m_nScrollPos >= nMaxPos)
			return;
		nDelta = min(nMaxPos / 100, nMaxPos - m_nScrollPos);
		break;

	case SB_LINEUP:
		if (m_nScrollPos <= 0)
			return;
		nDelta = -min(nMaxPos / 100, m_nScrollPos);
		break;

	case SB_PAGEDOWN:
		if (m_nScrollPos >= nMaxPos)
			return;
		nDelta = min(nMaxPos / 10, nMaxPos - m_nScrollPos);
		break;

	case SB_THUMBPOSITION:
		nDelta = (int)nPos - m_nScrollPos;
		break;

	case SB_PAGEUP:
		if (m_nScrollPos <= 0)
			return;
		nDelta = -min(nMaxPos / 10, m_nScrollPos);
		break;

	default:
		return;
	}
	m_nScrollPos += nDelta;
	SetScrollPos(SB_VERT, m_nScrollPos, TRUE);
	ScrollWindow(0, -nDelta);
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}



void Unit::OnBnClickedUnit1()
{
	// TODO: Add your control notification handler code here
	if (PreviousSkill == 0)
	{
		if (CurWrite1 != NULL)
		{
			delete CurWrite1;
			CurWrite1 = NULL;
		}
		CurWrite1 = new Write1;
		CurWrite1->Create(IDD_WRITING1, NULL);
		AfxGetApp()->m_pMainWnd = CurWrite1;
		CurWrite1->ShowWindow(SW_SHOWDEFAULT);
		CurChooseSkills->ShowWindow(SW_HIDE);
		CurUnit = this;
	}
	if (PreviousSkill == 1)
	{
		if (CurListen1 != NULL)
		{
			delete CurListen1;
			CurListen1 = NULL;
		}
		CurListen1 = new Listen1;
		CurListen1->Create(IDD_LISTEN1, NULL);
		AfxGetApp()->m_pMainWnd = CurListen1;
		CurListen1->ShowWindow(SW_SHOWDEFAULT);
		CurChooseSkills->ShowWindow(SW_HIDE);
		CurUnit = this;
	}
	if (PreviousSkill == 2)
	{
		if (CurSpeak1 != NULL)
		{
			delete CurSpeak1;
			CurSpeak1 = NULL;
		}
		CurSpeak1 = new Speak1;
		CurSpeak1->Create(IDD_SPEAK1, NULL);
		AfxGetApp()->m_pMainWnd = CurSpeak1;
		CurSpeak1->ShowWindow(SW_SHOWDEFAULT);
		CurChooseSkills->ShowWindow(SW_HIDE);
		CurUnit = this;
	}
	if (PreviousSkill == 3)
	{
		if (CurRead1 != NULL)
		{
			delete CurRead1;
			CurRead1 = NULL;
		}
		CurRead1 = new Read1;
		CurRead1->Create(IDD_READING1, NULL);
		AfxGetApp()->m_pMainWnd = CurRead1;
		CurRead1->ShowWindow(SW_SHOWDEFAULT);
		CurChooseSkills->ShowWindow(SW_HIDE);
		CurUnit = this;
	}
}


void Unit::OnBnClickedUnit2()
{
	// TODO: Add your control notification handler code here
	if (PreviousSkill == 0)
	{

	}
	if (PreviousSkill == 1)
	{

	}
	if (PreviousSkill == 2)
	{

	}
	if (PreviousSkill == 3)
	{

	}
}


void Unit::OnBnClickedUnit3()
{
	// TODO: Add your control notification handler code here
	if (PreviousSkill == 0)
	{

	}
	if (PreviousSkill == 1)
	{

	}
	if (PreviousSkill == 2)
	{

	}
	if (PreviousSkill == 3)
	{

	}
}


void Unit::OnBnClickedUnit4()
{
	// TODO: Add your control notification handler code here
	if (PreviousSkill == 0)
	{

	}
	if (PreviousSkill == 1)
	{

	}
	if (PreviousSkill == 2)
	{

	}
	if (PreviousSkill == 3)
	{

	}
}


void Unit::OnBnClickedUnit5()
{
	// TODO: Add your control notification handler code here
	if (PreviousSkill == 0)
	{

	}
	if (PreviousSkill == 1)
	{

	}
	if (PreviousSkill == 2)
	{

	}
	if (PreviousSkill == 3)
	{

	}
}
