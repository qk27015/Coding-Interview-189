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



int main()
{
	Node *head = new Node(0);
	head->append(1);
	head->append(2);

	deleteNode(head, 1);

	Node *n = head;
	while (n != NULL)
	{
		cout << n->data << endl;
		n = n->next;
	}
}