#include "pch.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

// 1.1 ある文字列が、全て固有であるかどうかを判定するアルゴリズムを実装
// 1 / 189
bool isUniqueStr(string str)
{
	const int kMaxChar = 255;
	int numChar[kMaxChar];
	for (int i = 0; i < kMaxChar; i++) numChar[i] = 0;

	for (int i = 0; i < str.length(); i++)
	{
		numChar[str[i]]++;
	}

	for (int i = 0; i < kMaxChar; i++)
	{
		if (numChar[i] > 1) return false;
	}
	return true;
}



// 1.2 2つの文字列が、片方が片方の並べ替えになっているかを判定
// 2 / 189
bool isPermutation(string s1, string s2)
{
	const int N = 100;
	char array1[N];
	char array2[N];
	strcpy_s(array1, N, s1.c_str());
	strcpy_s(array2, N, s2.c_str());

	sort(array1, array1 + s1.length());
	sort(array2, array2 + s2.length());

	return !strcmp(array1, array2);
}



int main()
{
	// 1.1
	cout << isUniqueStr("abcdefxyz") << endl;
	cout << isUniqueStr("abcdefxyza") << endl;
	cout << endl;

	// 1.2
	cout << isPermutation("abcdef", "fedacb") << endl;
	cout << isPermutation("abcccca", "abxxxxa") << endl;
	cout << endl;

	return 0;
}