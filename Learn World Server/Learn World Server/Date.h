#pragma once
#include<iostream>
#include<time.h>
using namespace std;


class Date//ngay
{
public:
	unsigned int iDay,iMonth,iYear;//ngay,thang,nam
public:
	Date(){}
	~Date(){}
	const unsigned int getDay() const;//Tra ve ngay
	const unsigned int getMon() const;//Tra ve thang
	const unsigned int getYear() const;//Tra ve nam
	bool IsValid(const unsigned int &day,const unsigned int &mon,const unsigned int &year) const;//kiem tra tinh hop le cua ngay thang
	bool IsLeapYear(const unsigned int &year) const;//Kiem tra nam nhuan
	Date CurrentTime() const;//Lay gio he thong
	bool UpDate(const unsigned int &day,const unsigned int &mon,const unsigned int &year);//Cap nhat ngay thang
	bool operator==(const Date& obj) const;
	bool operator!=(const Date& obj) const;
	bool operator>(const Date& obj) const;
	bool operator>=(const Date& obj) const;
	bool operator<=(const Date& obj) const;
	bool operator<(const Date& obj) const;
	friend ostream& operator<<(ostream& os,const Date& obj);
	friend istream& operator>>(istream& is,Date& obj);
};