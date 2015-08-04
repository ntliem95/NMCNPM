#pragma once
#include<iostream>
#include<string>
#include"Date.h"
#include"Password.h"
#include "afxdialogex.h"
#include "stdafx.h"
using namespace std;


class Account//thong tin tai khoan
{
public:
	CString _User;//ten dang nhap
	CString _Pass;//mat khau
	CString _Name;//ho ten
	Date _Db;//ngay sinh
	CString _Gender;//gioi tinh
	CString _Add;//dia chi
	CString _Phone;//dien thoai lien lac
public:
	Account(){}
	virtual ~Account() {}
    bool UpdateInfo(CString newID,CString newName,Date newDb,CString newGender,CString newAdd,CString newPhone)//Cap nhat thong tin
	{
		_Name = newName;
		_Db = newDb;
		_Gender = newGender;
		_Add = newAdd;
		_Phone = newPhone;
	}
	bool UpdatePassWord(CString newPass)//Thay doi mat khau
	{
		_Pass = newPass;
	}
	CString getPhone(CString s) const//Lay dien thoai
	{
		return _Phone;
	}
    CString getUsr() const//Lay ten dang nhap
	{
		return _User;
	}
	CString getSex() const//Lay gioi tinh
	{
		return _Gender;
	}
	CString getAdd() const//Lay dia chi
	{
		return _Add;
	}
	CString getName() const//Lay ten
	{
		return _Name;
	}
	Date getBir() const//Lay ngay sinh
	{
		return _Db;
	}
	CString getPass() const//lay mat khau
	{
		return _Pass;
	}
	virtual void DisplayInfo() const = 0;//Hien thong tin nguoi dung
	virtual bool SaveInfo() const = 0;//Luu thong tin nguoi dung vao co so du lieu
	virtual bool LoadInfo() = 0;//Lay thong tin nguoi dung tu co so du lieu
};