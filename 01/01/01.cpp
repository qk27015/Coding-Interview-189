#include "pch.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

// 1.1 : ある文字列が、全て固有であるかどうかを判定するアルゴリズムを実装
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



// 1.2 : 2つの文字列が、片方が片方の並べ替えになっているかを判定
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



// 1.3 : すべての空白文字を%20で置き換える
// 3 / 189
string encode(string str)
{
	vector<char> v;
	
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			v.push_back('%'); v.push_back('2'); v.push_back('0');
		}
		else
			v.push_back(str[i]);
	}
	
	string result(v.begin(), v.end());
	return result;
}



// 1.4 : 文字列が回文の順列(回文を作成できる)であるかを調べる
// 4 / 189
bool isPalindrome(string str)
{
	const int kMaxChar = 255;
	int numChar[kMaxChar];
	for (int i = 0; i < kMaxChar; i++) numChar[i] = 0;

	for (int i = 0; i < str.length(); i++)
	{
		numChar[str[i]]++;
	}

	int numOdd = 0, numEven = 0;
	for (int i = 0; i < kMaxChar; i++)
	{
		if (numChar[i] % 2 == 1 && numChar[i] != 0)
			numOdd++;
		if (numChar[i] % 2 == 0 && numChar[i] != 0)
			numEven++;
	}

	if (numOdd == 1)
		return true;
	if (numOdd == 0 && numEven > 0)
		return true;
	return false;
}



// 1.5 : 文字列1に対して、文字の挿入・削除・置換を一度だけ行い、文字列2を作成できるか調べる
// 5 / 189
bool canReplace(string s1, string s2);
bool canDelete(string s1, string s2);

bool canCreate(string s1, string s2)
{
	if (s1.length() == s2.length())
		return canReplace(s1, s2);
	if (s1.length() - 1 == s2.length())
		return canDelete(s1, s2);
	if (s1.length() + 1 == s2.length())
		return canDelete(s2, s1);
	return false;
}

bool canReplace(string s1, string s2)
{
	int cntDiffChar = 0;
	for (int i = 0; i < s1.length(); i++)
	{
		if (s1[i] != s2[i])
			cntDiffChar++;
	}
	return cntDiffChar < 2;
}

bool canDelete(string s1, string s2)
{
	bool *canFlagArray = (bool *)malloc(sizeof(bool) * s2.length());
	for (int i = 0; i < s2.length(); i++)
		canFlagArray[i] = false;

	for (int i = 0; i < s2.length(); i++)
	{
		for (int j = 0; j < s1.length(); j++)
		{
			if (s1[j] == s2[i])
			{
				canFlagArray[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < s2.length(); i++)
	{
		if (canFlagArray[i] == false) return false;
	}
	return true;
}



// 1.6 : 文字列の連続する数を使って文字列を圧縮する。
// 6 / 189
string compression(string str)
{
	vector<char> v;
	for (int i = 0; i < str.length(); i++)
	{
		v.push_back(str[i]);

		int charCnt = 1;
		bool isContinuous = true;
		while (isContinuous)
		{
			int j = i + 1;
			if (j < str.length() && str[i] == str[j])
			{
				charCnt++;
				i++;
			}
			else
				isContinuous = false;
		}
		v.push_back('0' + charCnt);
	}

	string compressed = string(v.begin(), v.end());

	return compressed.length() < str.length() ? compressed : str;
}



// 1.7 : NxNの行列に描かれた画像を追加の領域なしで90度回転させる。
// 7 / 189
// 追加領域なしのアルゴリズムが思いつかない。パス



// 1.8 : MxNの行列について、要素が0であればその行と列をすべて0にする
// 8 / 189
// 問題の意味がわからない。パス



// 1.9 : isSubstringメゾットを一度だけ使ってs2がs1を回転させたものか判定する。
// 9 / 189
// 問題の意味がわからない。パス



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

	// 1.3
	cout << encode("a bc") << endl;
	cout << endl;

	// 1.4
	cout << isPalindrome("tactcoapapa") << endl;
	cout << isPalindrome("abba") << endl;
	cout << isPalindrome("acbxyz") << endl;
	cout << isPalindrome("ab") << endl;
	cout << endl;

	// 1.5
	cout << canCreate("ple", "pale") << endl;
	cout << canCreate("pale", "ple") << endl;
	cout << canCreate("pale", "bale") << endl;
	cout << canCreate("pale", "bake") << endl;
	cout << endl;

	// 1.6
	cout << compression("aabcccccaaa") << endl;
	cout << compression("abcd") << endl;
	cout << endl;

	return 0;
}