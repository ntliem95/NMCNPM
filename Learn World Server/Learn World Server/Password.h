#pragma once
#include<iostream>
#include<string>
using namespace std;

class PassWord
{
private:
	string _Pass;
public:
	PassWord();
	~PassWord();
	const string getPass() const;//tra ve _Pass
	bool Reset();//Reset Mat Khau.Phat Sinh mat khau moi
	bool IsValid() const;//Kiem tra mat khau co hop le khong(dung quy dinh hay k?)
	string DecodingPassword() const;//Giai ma password thanh password chinh xac cua nguoi dung
	string EncryptedPassword() const;//Ma Hoa Mat KHau cho ly do bao mat
	bool Update(string s);//Cap nhat mat khau
	bool operator==(const PassWord& obj) const;
	bool operator!=(const PassWord& obj) const;
	friend ostream& operator<<(ostream& os,const PassWord& obj);
	friend istream& operator>>(istream& is,PassWord& obj);
};