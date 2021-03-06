﻿#include "pch.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;



// 1.1 : ある文字列が、全て固有であるかどうかを判定するアルゴリズムを実装
// 1 / 189
// boolの配列ではなく32ビット整数で判定できる
bool isUniqueChars(string str)
{
	int checker = 0;
	for (int i = 0; i < str.length(); i++)
	{
		int val = str[i] - 'a' + 1;
		if (checker & (1 << val))
			return false;
		checker |= 1 << val;
	}
	return true;
}



// 1.2 : 2つの文字列が、片方が片方の並べ替えになっているかを判定
// 2 / 189
// 正解



// 1.3 : すべての空白文字を%20で置き換える
// 3 / 189
// 正解


// 1.4 : 文字列が回文の順列(回文を作成できる)であるかを調べる
// 4 / 189
// 整数を一つ使うだけで実装できる。
// 整数値から1減算したものとANDを取り、1ビットだけが1になっているかチェックする
bool checkExactlyOneBitSet(int bitVector)
{
	return (bitVector & (bitVector - 1)) == 0;
}
// 整数のiビット目を切り替える
int toggle(int bitVector, int index)
{
	if (index < 0) return bitVector;

	int mask = 1 << index;
	if ((bitVector & mask) == 0)
	{
		// 存在しない場合、そのビットを1にする
		bitVector |= mask;
	}
	else
	{
		// 存在する場合、そのビットを0にする
		bitVector &= ~mask;
	}

	return bitVector;

}
// 文字列に対するビットベクトルを作成する
int createBitVector(string pharse)
{
	int bitVector = 0;
	for (int i = 0; i < pharse.length(); i++)
	{
		int x = pharse[i] - 'a';
		bitVector = toggle(bitVector, x);
		
	}
	return bitVector;
}
// 呼び出す関数
bool isPermutationOfPalindrome(string pharse)
{
	int bitVector = createBitVector(pharse);
	// 偶数の文字のみ or 奇数が1個
	return bitVector == 0 || checkExactlyOneBitSet(bitVector);
}



// 1.5 : 文字列1に対して、文字の挿入・削除・置換を一度だけ行い、文字列2を作成できるか調べる
// 5 / 189
// 正解



// 1.6 : 文字列の連続する数を使って文字列を圧縮する。
// 6 / 189
// stringをjavaのStringBuilderっぽく使った回答。※自分の回答でほぼ正解
string compress(string str)
{
	string compressed;
	int countConsecutive = 0;
	for (int i = 0; i < str.length(); i++)
	{
		countConsecutive++;

		if (i + 1 >= str.length() || str[i] != str[i + 1])
		{
			compressed += str[i];
			compressed += '0' + countConsecutive;
			countConsecutive = 0;
		}
	}
	return compressed.length() < str.length() ? compressed : str;
}



// 難
// 1.7 : NxNの行列に描かれた画像を追加の領域なしで90度回転させる。
// 7 / 189
const int kNumRow = 4;
bool rotate(int matrix[][kNumRow])
{
	int n = kNumRow;
	for (int layer = 0; layer < n / 2; layer++)
	{
		int first = layer;
		int last = n - 1 - layer;
		for (int i = first; i < last; i++)
		{
			int offset = i - first;
			int top = matrix[first][i]; // 上端の端
			// 左端 -> 上端
			matrix[first][i] = matrix[last - offset][first];
			// 下端 -> 左端
			matrix[last - offset][first] = matrix[last][last - offset];
			// 右端 -> 下端
			matrix[last][last - offset] = matrix[i][last];
			// 上端 -> 右端
			matrix[i][last] = top;
		}
	}
	return true;
}

void print(int matrix[][kNumRow])
{
	for (int i = 0; i < kNumRow; i++)
	{
		for (int j = 0; j < kNumRow; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}



// 1.8 : MxNの行列について、要素が0であればその行と列をすべて0にする
// 8 / 189
void initMatrix(int matrix[][kNumRow])
{
	for (int i = 0; i < kNumRow; i++)
		for (int j = 0; j < kNumRow; j++)
			matrix[i][j] = i * kNumRow + j + 1;
}
void nullifyRow(int matrix[][kNumRow], int row)
{
	for (int j = 0; j < kNumRow; j++)
		matrix[row][j] = 0;
}
void nullifyCol(int matrix[][kNumRow], int col)
{
	for (int i = 0; i < kNumRow; i++)
		matrix[i][col] = 0;
}
void setZeros(int matrix[][kNumRow])
{
	int n = kNumRow;

	// 最初の行と列を0があるかのフラグに使用する
	bool rowHasZero = false;
	bool colHasZero = false;

	// 最初の行に0があるかチェック
	for(int j = 0; j < n; j++)
		if (matrix[0][j] == 0)
		{
			rowHasZero = true;
			break;
		}
	// 最初の列に0があるかチェック
	for(int i = 0; i < n; i++)
		if (matrix[i][0] == 0)
		{
			colHasZero = true;
			break;
		}

	// 残りの行列に0があるかチェック
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (matrix[i][j] == 0)
			{
				// 最初の行、列はどうせ0になるので、
				// そのエリアを活用することでメモリを節約できる。
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
	}

	// 行を0で埋める
	for (int i = 1; i < n; i++)
		if (matrix[i][0] == 0)
			nullifyRow(matrix, i);
	// 列を0で埋める
	for (int j = 1; j < n; j++)
		if (matrix[0][j] == 0)
			nullifyCol(matrix, j);

	// 必要なら最初の行と列を0で埋める
	if (rowHasZero) nullifyRow(matrix, 0);
	if (colHasZero) nullifyCol(matrix, 0);
}



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
	// 1.1
	cout << isUniqueChars("abcdefxyz") << endl;
	cout << isUniqueChars("abcdefxyza") << endl;
	cout << endl;

	// 1.2

	// 1.3

	// 1.4
	cout << isPermutationOfPalindrome("tactcoapapa") << endl;
	cout << isPermutationOfPalindrome("abba") << endl;
	cout << isPermutationOfPalindrome("acbxyz") << endl;
	cout << isPermutationOfPalindrome("ab") << endl;
	cout << endl;

	// 1.5

	// 1.6
	cout << compress("aabcccccaaa") << endl;
	cout << compress("abcd") << endl;
	cout << endl;

	// 1.7
	int matrix[kNumRow][kNumRow];
	initMatrix(matrix);
	print(matrix);
	rotate(matrix);
	print(matrix);
	cout << endl;

	// 1.8
	initMatrix(matrix);
	matrix[rand() % kNumRow][rand() % kNumRow] = 0;
	print(matrix);
	setZeros(matrix);
	print(matrix);

	// 1.9
	cout << isRotation("waterbottle", "erbottlewat");
	cout << endl;
}