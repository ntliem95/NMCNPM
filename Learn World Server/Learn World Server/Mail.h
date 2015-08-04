#pragma once
#include<iostream>
#include<string>
#include"Date.h"
using namespace std;
class Mail// tin nhan trong he thong
{
private:
	string Mail_ID;//id cua mail
	string Sender_ID;//id cua nguoi gui
	string Receiver_ID;//id cua nguoi nhan
	Date DAY_SEND;//ngay gui
	bool State;//nguoi nhan da xem thu hay chua?
};