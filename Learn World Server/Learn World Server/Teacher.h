#pragma once
#include"Account.h"
#include<vector>
using namespace std;


class System;
class Lesson;
class Teacher:public Account//lop giao vien.Dung cac ham trong class System de ho tro thuc hien cac ham trong class
{
public:
	Teacher(){}
	~Teacher(){}
	CString Rating;
	CString NumberOfRating;
	bool LoadInfo() { return 1; }//Lay thong tin nguoi dung tu co so du lieu
	bool SaveInfo() const{ return 1; }//Luu thong tin nguoi dung vao co so du lieu
	void DisplayInfo() const{}//Hien thong tin nguoi dung

	bool SentFeedback(System &Sys) const;// gui phan hoi
	bool ViewMail(System &Sys) const;//xem thu

	bool ViewListLessonTeaching(System &Sys) const;//xem phieu danh sach cac lesson dang quan ly
private:
	vector<string> List_Lesson_ID;//id cac khoa hoc quan ly
};