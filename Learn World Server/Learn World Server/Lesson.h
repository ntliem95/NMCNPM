#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"Date.h"
using namespace std;
class Lesson// cac khoa hoc trong he thong
{
private:
	string Teacher_ID;//id giao vien quan ly
	string Lesson_ID;//id cua lesson
	vector<string> User_ID;//list id cac user tham gi lesson nay
	Date _Start;//ngay bat dau
	Date _End;//ngay bat dau
	bool isActive;//khoa hoc van con hoat dong
};