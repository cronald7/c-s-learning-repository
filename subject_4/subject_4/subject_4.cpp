//#include "pch.h"
#include <iostream>
#include <cstring>
#include <queue> // 此处使用语法糖queue类模板
#include <vector> // 使用语法糖vector类模板
#include <sstream>
//#include<stdio.h>
//#include <stdlib.h>
#include <cstdlib>
#include <cstdio> // 使用sprintf();语法糖
using namespace std;

vector<string> strGiven;
queue<string> strCommand;

void strStorage(char * s);
bool strProcess();
string strRecursion();
void myInsert(string s, int n, int x);
void myReset(string s, int n);
void myPrint(int n);
void myPrintall();
string myCopy(int n, int x, int l);
string myAdd(string s1, string s2);
string myFind(string s, int n);
string myRfind(string s, int n);

int string_to_int(string s) {
	string str;
	int str_num;

	str = s;
	istringstream is(s);
	is >> str_num;

	return str_num;
}

void myInsert(string s, int n, int x) {
	strGiven[n-1].insert(x, s);
}

void myReset(string s, int n) {
	strGiven[n-1].erase(0);
	strGiven[n-1].replace(0, 0, s, 0);
}

void myPrint(int n) {
	cout << strGiven[n-1] << endl;
}

void myPrintall() {
	for (int i = 0; i < strGiven.size(); i++) {
		cout << strGiven[i] << endl;
	}
}

string myCopy(int n, int x, int l) {
	string temp;
	temp.assign(strGiven[n-1], x, l);
	return temp;
}

string myAdd(string s1, string s2) {
	// 判断字符串中是否全是数字，使用ascii码进行判断
	// 0-9数字，其ascii码值为48-57，小于或大于这个数字的都不是数字
	for (int i = 0; i < s1.size(); i++) {
		if (s1.at(i) < '0' || s1.at(i) > '9') {
			return s1 + s2;
		}
	}
	for (int i = 0; i < s2.size(); i++) {
		if (s2.at(i) < '0' || s2.at(i) > '9') {
			return s1 + s2;
		}
	}
	// 否则全是数字
	long a = string_to_int(s1.c_str());
	long b = string_to_int(s2.c_str());
	//判断是否小于0或者大于99999
	char strNum[101];
	if (0 <= a && a <= 99999 && 0 <= b && b <= 99999) {
		long c = a + b;
		sprintf_s(strNum, "%d", c);
		return strNum;
	}
	else {
		return s1 + s2;
	}
}

string myFind(string s, int n) {
	int index = strGiven[n-1].find(s);
	char strNum[101];
	if (index != string::npos) {
		sprintf_s(strNum, "%d", index);
		return strNum;
	}
	else {
		sprintf_s(strNum, "%d", strGiven[n-1].size());
		return strNum;
	}
}

string myRfind(string s, int n) {
	int rindex = strGiven[n-1].rfind(s);
	char strNum[101];
	if (rindex != string::npos) {
		sprintf_s(strNum, "%d", rindex);
		return strNum;
	}
	else {
		sprintf_s(strNum, "%d", strGiven[n-1].size());
		return strNum;
	}
}

// 预处理命令行，使其以string字符串类型形式存储
void strStorage(char * s) {
	string str;
	// 此处可计算s中' '的数量估计命令中字符串个数
	/*
	int count=0;
	for (int i=0;s[i] != '\0';i++){
	    if (s[i] == ' ')
	        count+=1;
	}
	string * strCommand = new string[count]
	*/
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] != ' ') {
			str.push_back(s[i]);
		}
		else {
			strCommand.push(str);
			str.clear();
		}
	}
	// 记录最后一个命令行字符串
	strCommand.push(str);
}

// atoi const char *字符串转整数
// string类对象.c_str()返回传统const char *常量字符串
bool strProcess() {
	string str = strCommand.front();
	strCommand.pop();
	if (str == "insert") {
		string s = strRecursion();
		int n = string_to_int(strRecursion().c_str());
		int x = string_to_int(strRecursion().c_str());
		myInsert(s, n, x);
	}
	else if (str == "reset") {
		string s = strRecursion();
		int n = string_to_int(strRecursion().c_str());
		myReset(s, n);
	}
	else if (str == "print") {
		int n = string_to_int(strRecursion().c_str());
		myPrint(n);
	}
	else if (str == "printall") {
		myPrintall();
	}
	else if (str == "over") {
		return false;
	}
	return true;
}

string strRecursion() {
	string str = strCommand.front();
	strCommand.pop();
	if (str == "copy") {
		int n = string_to_int(strRecursion().c_str());
		int x = string_to_int(strRecursion().c_str());
		int l = string_to_int(strRecursion().c_str());
		return myCopy(n, x, l);
	}
	else if (str == "add") {
		string s1 = strRecursion();
		string s2 = strRecursion();
		return myAdd(s1, s2);
	}
	else if (str == "find") {
		string s = strRecursion();
		int n = string_to_int(strRecursion().c_str());
		return myFind(s, n);
	}
	else if (str == "rfind") {
		string s = strRecursion();
		int n = string_to_int(strRecursion().c_str());
		return myRfind(s, n);
	}
	else {
		return str;
	}
}

int main() {
	int n;
	// string strGiven;

	cin >> n;
	cin.get();

	// 这种方法用于输入也可以，但是a[20]这样的设置不够灵活
	/*string a[20];
	for (int i = 0; i < n; i++)
		cin >> a[i];*/

	/*while (cin >> strGiven)
		cout << strGiven << endl;*/
	// 直接定义个数未知的数组，会提示表达式必须有常量，使用new的方式则不会
	// 使用string类型数组，用于存储字符串
	// 使用动态内存设定字符存储器需要设定n，若将存储器设定为全局变量,n无法进行输入
	// vector模板对象也无法用string对象进行赋值
	//string *strGiven = new string[n];

	// >>不能用于输入const char *,只能用于输入char *，原因是istream不支持
	// 当定义strGiven为char *时，cin>>输入会直接使程序中止，具体原因要查找
	// 1.字符数组类型，按索引输入会限制字符串数量，不能全量将字符输入
	// 2.按整个字符数组输入，会出现这次输入将上次输入字符串覆盖的问题
	// 因此，char类型的数组一般不适用于多字符输入的情况，或者只能用于中转。
	for (int i = 0; i < n; i++) {
		string str;
		cin >> str;
		// 使用strGiven[i]有vector out of range 的报错
		// cin >> strGiven[i];
		strGiven.push_back(str);
	}
	cin.get();

	// insert copy 1 find 2 1 2 2 2;
	char command[501];
	while (cin.getline(command, 500)) {
		// 基于函数形参只是复制实参，需要定义一个全局变量才能保证所有的动作都作用在strCommand上
		// queue<string> strCommand;
		// 预处理命令字符串
		strStorage(command);
		bool flag = strProcess();
		if (!flag){
			break;
		}
	}
	return 0;
}