// 02.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;



class Node {

public:
	Node *next;
	int data;

	Node(int d)
	{
		next = NULL;
		data = d;
	}

	void append(int d)
	{
		Node *end = new Node(d);
		Node *n = this;
		while (n->next != NULL)
		{
			n = n->next;
		}
		n->next = end;
	}
};

Node *deleteNode(Node *head, int d)
{
	Node *n = head;

	if (n->data == d) return head->next;

	while (n->next != NULL)
	{
		if (n->next->data == d)
		{
			n->next = n->next->next;
			return head;
		}
		n = n->next;
	}
	return head;
}

void printNode(Node *head)
{
	Node *n = head;
	while (n != NULL)
	{
		cout << n->data << endl;
		n = n->next;
	}
}



// 2.1 一時的なバッファを使用せず、ソートされていない連結リストから重複する要素を削除
// 10 / 189
void deleteDuplication(Node *head)
{
	for (Node *i = head; i != NULL; i = i->next)
	{
		for (Node *j = head; j != NULL; j = j->next)
		{
			if (i->data == j->data && i != j)
				deleteNode(head, j->data);
		}
	}
}



// 2.2 後ろからK番目を返す
// 11 / 189
Node *getBackNode(int k, Node *head)
{
	int cnt = 0;
	for (Node *n = head; n != NULL; n = n->next) cnt++;
	int diffByLead = cnt - k;
	Node *n = head;
	for (int i = 0; i < diffByLead; i++) n = n->next;
	return n;
}



// 2.3 他のノードにアクセスせず、中間の要素を削除
// 12 / 189
void deleteAssignedNode(Node *n)
{
	n->data = n->next->data;
	n->next = n->next->next;
}



// 2.4 ある数xより小さいものが前に来るようにする
// 13 / 189
void swapNode(Node *n1, Node *n2)
{
	Node *n = n1;
	n1 = n2;
	n2 = n;
}
void punctuate(int x, Node *head)
{
	Node *n = head;
	while (n != NULL)
	{
		// ここでアルゴリズムが思いつかないのでパス
	}
}



// 2.5 各ノードの数が1桁の数、その和をもとめ連結リストを作り返す
// 14 / 189
Node *sumNode(Node *head1, Node *head2)
{
	int base = 1;
	int num1 = 0;
	for (Node *n = head1; n != NULL; n = n->next, base *= 10)
	{
		num1 += n->data * base;
	}
	base = 1;
	int num2 = 0;
	for (Node *n = head2; n != NULL; n = n->next, base *= 10)
	{
		num2 += n->data * base;
	}
	
	int sum = num1 + num2;
	int digit = log(sum) / log(10) + 1;
	Node *head3 = new Node(sum / (int)pow(10, digit-1));
	sum %= (int)pow(10, digit - 1); digit--;
	for (; digit > 0; digit--)
	{
		head3->append(sum / (int)pow(10, digit - 1));
		sum %= (int)pow(10, digit - 1);
	}

	return head3;
}



// 2.6 連結リストが回文になっているかを調べる
// 15 / 189
bool isParotum(Node *head)
{
	string str;
	for (Node *n = head; n != NULL; n = n->next)
	{
		str += n->data + '0';
	}

	string s = str;
	reverse(str.begin(), str.end());
	

	return !strcmp(s.c_str(), str.c_str());
}



// 2.7 2つのリストが共通かどうかを判定する
// 16 / 189
// 問題文の意味がわからないのでパス



// 2.8 循環するループのリストが与えられたとき、循環する最初の部分を返す
// 17 / 189
Node *isLoop(Node *head)
{
	Node *usagi = head, *kame = head;
	for (int i = 0; i < 100; i++)
	{
		usagi = usagi->next->next;
		kame = kame->next;
		if (usagi == kame)
			return usagi;
	}

	return NULL;
}



int main()
{
	Node *head = new Node(0);

	// 2.1
	head->append(1);
	head->append(2);
	head->append(1);
	printNode(head);
	cout << endl;
	deleteDuplication(head);
	printNode(head);
	cout << endl << endl;

	// 2.2
	head->append(3);
	head->append(4);
	head->append(5);
	head->append(6);
	printNode(head);
	Node *back = getBackNode(2, head);
	cout << "[" <<  back->data << "]" << endl;
	cout << endl << endl;

	// 2.3
	printNode(head);
	cout << endl;
	deleteAssignedNode(getBackNode(2, head));
	printNode(head);
	cout << endl << endl;

	// 2.4

	// 2.5
	Node *head1 = new Node(7);
	head1->append(1);
	head1->append(6);
	Node *head2 = new Node(5);
	head2->append(9);
	head2->append(2);
	head2->append(1);
	Node *head3 = sumNode(head1, head2);
	printNode(head3);
	cout << endl << endl;

	// 2.6
	cout << isParotum(head) << endl;
	cout << endl << endl;

	// 2.7

	// 2.8
	Node *n = getBackNode(2, head);
	n->next = getBackNode(4, head);
	n = isLoop(head);
	cout << n->data << endl;
}