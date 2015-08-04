#pragma once
#include"Account.h"
#include<vector>
using namespace std;


class System;

class Administrator:public Account// lop admin.Dung cac ham trong class System de ho tro thuc hien cac ham trong class
{
public:
	Administrator()
	{

	}
	~Administrator()
	{

	}
	bool LoadInfo() { return 1; };//Lay thong tin nguoi dung tu co so du lieu
	bool SaveInfo() const { return 1; }//Luu thong tin nguoi dung vao co so du lieu
	void DisplayInfo() const{}//Hien thong tin nguoi dung

	//bool AddNewTeacher(System& Sys) const;//them giao vien
	//bool AddNewAdmin(System& Sys) const;//bo nhiem them admin

	////void SortByUsr(vector<Account*>& temp) const;//Sap xep danh sach theo ten dang nhap
 //  // void SortByNameUsr(vector<Account*>& temp) const;//Sap xep danh sach theo ten nguoi dung
 //  // void SortByTypeUsr(vector<Account*>& temp) const;//Sap xep danh sach theo loai nguoi dung
 //  // void SortByState(vector<Account*>& temp) const;//Sap xep danh sach theo tinh trang nguoi dung
	////void SortBySex(vector<Account*>& temp) const;//Sap xep danh sach theo gioi tinh

	//bool Deactivated(System& Sys) const;//Cam hoat dong mot tai khoan
	//bool ActiveUser(System& Sys) const;//cho phep hoat dong tai khoan
	//bool DeleteAcc(System& Sys) const;//xoa mot tai khoan
	//bool ResetPass(System& Sys) const;//Reset pass mot tai khoan
	//bool ViewFeedback(System& Sys) const;//Xem feedback cua nguoi dung
	//bool SentMail(System& Sys) const;//gui mail cho nguoi dung
	//bool ViewInfoUser(System& Sys) const;//Xem thong tin nguoi dung(thong tin ca nhan,ki luc muon sach)
};