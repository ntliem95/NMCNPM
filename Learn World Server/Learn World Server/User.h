#pragma once
#include"Account.h"
#include<vector>
using namespace std;


class System;
class Lesson;
class User:public Account// lop hoc vien.Dung cac ham trong class System de ho tro thuc hien cac ham trong class
{
public:
	User(){}
	~User(){}
	CString Rating;
	bool LoadInfo(){
		return 1;
	}//Lay thong tin nguoi dung tu co so du lieu
	bool SaveInfo() const{
		return 1;
	}//Luu thong tin nguoi dung vao co so du lieu
	void DisplayInfo() const{}//Hien thong tin nguoi dung

	bool RegisterALesson(System &Sys);//dang ky tham gia vao lesson
	bool DropOutALesson(System &Sys) ;//Roi khoi 1 lesson
	bool SentFeedback(System &Sys) const;// gui phan hoi
	bool ViewMail(System &Sys) const;//xem thung thu

	bool ViewListLessonJoining(System &Sys) const;//xem phieu danh sach cac lesson ma hoc vien dang ky
private:
	vector<string> List_Lesson_ID;//id cac khoa hoc tham gia
};