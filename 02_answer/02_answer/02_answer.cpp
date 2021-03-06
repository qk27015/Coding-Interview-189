// 02_answer.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;



class Node {

public:
	Node * next;
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
// 正解



// 2.2 後ろからK番目を返す
// 11 / 189
// 一応正解だが、リストの要素数を数えているので効率が悪い
// 再帰的な解法
Node *nthToLast(Node *head, int k, int &i)
{
	if (head == NULL)
		return NULL;
	Node *nd = nthToLast(head->next, k, i);
	i = i + 1;
	if (i == k)
		return head;
	return nd;
}
Node *nthToLast(Node *head, int k)
{
	int i = 0;
	return nthToLast(head, k, i);
}



// 2.3 他のノードにアクセスせず、中間の要素を削除
// 12 / 189
// 正解



// 2.4 ある数xより小さいものが前に来るようにする
// 13 / 189
// 間違い。正解は2つのリストを作る方法
Node *partition(Node *node, int x)
{
	Node *beforeStart = NULL;
	Node *beforeEnd = NULL;
	Node *afterStart = NULL;
	Node *afterEnd = NULL;

	while (node != NULL)
	{
		Node *next = node->next;
		node->next = NULL;
		if (node->data < x)
		{
			if (beforeStart == NULL)
			{
				beforeStart = node;
				beforeEnd = beforeStart;
			}
			else
			{
				beforeEnd->next = node;
				beforeEnd = node;
			}
		}
		else
		{
			if (afterStart == NULL)
			{
				afterStart = node;
				afterEnd = afterStart;
			}
			else
			{
				afterEnd->next = node;
				afterEnd = node;
			}
		}
		node = next;
	}

	if (beforeStart == NULL)
		return afterStart;

	beforeEnd->next = afterStart;
	return beforeStart;
}



// 2.5 各ノードの数が1桁の数、その和をもとめ連結リストを作り返す
// 14 / 189
// 桁数の違う数にも対応できていたので正解



// 2.6 連結リストが回文になっているかを調べる
// 15 / 189
// 正解



// 2.7 2つのリストが共通かどうかを判定する
// 16 / 189
// 問題文の意味がわからないのでパスした
// 回答は以下
class Result
{
public:
	Node *tail;
	int size;
	Result(Node *tail, int size)
	{
		this->tail = tail;
		this->size = size;
	}
};

Result *getTailAndSize(Node *list)
{
	if (list == NULL) return NULL;

	int size = 1;
	Node *current = list;
	while (current->next != NULL)
	{
		size++;
		current = current->next;
	}
	return new Result(current, size);
}

Node *getKthNode(Node *head, int k)
{
	Node *current = head;
	while (k > 0 && current != NULL)
	{
		current = current->next;
		k--;
	}
	return current;
}

Node *findIntersection(Node *list1, Node *list2)
{
	if (list1 == NULL || list2 == NULL) return NULL;

	Result *result1 = getTailAndSize(list1);
	Result *result2 = getTailAndSize(list2);

	// 末尾が異なれば、交わりは無し
	if (result1->tail != result2->tail) return NULL;

	Node *shorter = result1->size < result2->size ? list1 : list2;
	Node *longer = result1->size < result2->size ? list2 : list1;
	// 長さの差の分だけ、長い方のポインタを進める
	longer = getKthNode(longer, abs(result1->size - result2->size));
	// ぶつかるまで両方のポインタを進める
	while (shorter != longer)
	{
		shorter = shorter->next;
		longer = longer->next;
	}
	
	return longer;
}



// 2.8 循環するループのリストが与えられたとき、循環する最初の部分を返す
// 17 / 189
// 正解



int main()
{
	// 2.2
	Node *head = new Node(0);
	head->append(1);
	head->append(2);
	head->append(3);
	head->append(4);
	Node *back = nthToLast(head, 2);
	cout << "[" << back->data << "]" << endl;
	cout << endl << endl;

	// 2.4
	head = new Node(3);
	head->append(5);
	head->append(8);
	head->append(5);
	head->append(10);
	head->append(2);
	head->append(1);
	Node *part = partition(head, 5);
	printNode(part);
	cout << endl << endl;

	// 2.7
	Node *head1 = new Node(3);
	head1->append(1);
	head1->append(5);
	head1->append(9);
	head1->append(7);
	head1->append(2);
	head1->append(1);
	Node *head2 = new Node(4);
	head2->append(6);
	nthToLast(head2, 1)->next = nthToLast(head1, 3);
	Node *intersection = findIntersection(head1, head2);
	cout << intersection->data << endl;

    return 0;
}

