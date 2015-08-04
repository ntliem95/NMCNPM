#pragma once
#include"Administrator.h"
#include"Teacher.h"
#include"User.h"
#include"Mail.h"
#include"Lesson.h"


class DATABASE//lop co so du lieu.Luu thong tin can thiet cua co so du lieu vao chuong trinh.Tuy vao co so du lieu dc chon se phat trien them class
{
private:
	vector<Lesson*> List_Lesson;
	vector<Mail*> List_Mail;
	vector<Account*> List_Account;
public:
	bool LoadDatabase();// load du lieu tu database
	bool SaveDatabase();// luu du lieu thay doi vao lai database
	vector<Lesson*>& getListLesson();
	vector<Mail*>& getListMail();
	vector<Account*>& getListAccount();
};