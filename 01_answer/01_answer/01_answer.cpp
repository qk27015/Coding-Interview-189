#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

// 1.9 : isSubstringメゾットを一度だけ使ってs2がs1を回転させたものか判定する。
// 9 / 189

// s2がs1の部分文字列であるかを返す
bool isSubstring(string s1, string s2)
{
	int pos = s1.find(s2[0]);
	if (pos == string::npos) return false;

	string cmp = string(&s1[pos], s2.length());
	return !strcmp(cmp.c_str(), s2.c_str());
}

// 回転させたものか判定する
bool isRotation(string s1, string s2)
{
	if (s1.length() == s2.length() && s1.length() > 0)
	{
		// 回転させたs2は、s1を2つ連結させたs1s1の部分文字列である
		return isSubstring(s1 + s1, s2);
	}
	return false;
}

int main()
{
	cout << isRotation("waterbottle", "erbottlewat");
	cout << endl;
}