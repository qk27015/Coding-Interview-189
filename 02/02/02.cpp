// 02.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
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
}