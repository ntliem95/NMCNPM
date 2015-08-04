#pragma once
#include<iostream>
#include<vector>
#include"Database.h"
using namespace std;


class System//lop chuc nang. nhung chuc nang trong chuong trinh se duoc xu ly o day
{
private:
	DATABASE DATA;
public:
	System();
	~System();
	bool RegisterAccount();//Dang ky
	bool SignIn() const;//dang nhap
	bool SignOut() const;//Dang xuat
	bool ChangePassword();//thay doi pass nguoi dung
	bool ChangeInfo();//thay doi thong tin nguoi dung

	void SearchUser() const;//tool search nguoi dung
	void DisplayListUser(vector<Account*>& temp) const;//hien thi danh sach nguoi dung theo list
	void SortByUsr(vector<Account*>& temp) const;//Sap xep danh sach theo ten dang nhap
    void SortByNameUsr(vector<Account*>& temp) const;//Sap xep danh sach theo ten nguoi dung
    void SortByTypeUsr(vector<Account*>& temp) const;//Sap xep danh sach theo loai nguoi dung
    void SortByState(vector<Account*>& temp) const;//Sap xep danh sach theo tinh trang nguoi dung
	void SortBySex(vector<Account*>& temp) const;//Sap xep danh sach theo gioi tinh

	//chuc nang se duoc them vao day
};