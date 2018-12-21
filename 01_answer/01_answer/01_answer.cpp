#include "pch.h"
#include <iostream>
#include <string>
using namespace std;



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