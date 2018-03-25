#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


struct Node {
	int v;
	Node * next;

	Node(int _v = 0) { // constructor
		v = _v, next = NULL;
	}
};


void traverse(Node * head) {
	Node * p = head;

	printf("current link list\n");
	while (p) {
		cout << p -> v;
		if (p -> next)
			cout << " -> ";
		else 
			cout << endl;
		p = p -> next;
	}
}

Node * insertInFront(int v, Node * head) {
	Node * new_node = new Node(v);

	new_node -> next = head;
	head = new_node;

	return head;
}

Node * insertInEnd(int v, Node * head) {
	Node * new_node = new Node(v);

	if (!head)
		return head = new_node;

	Node * temp = head;
	while (temp -> next)
		temp = temp -> next;

	temp -> next = new_node;

	return head;
}

Node * insertSorted(int v, Node * head) {
	Node * new_node = new Node(v);
	Node * temp = head;

	while (temp -> next && temp -> next -> v < v)
		temp = temp -> next;

	new_node -> next = temp -> next;
	temp -> next = new_node;

	return head;
}

int findByIndex(int idx, Node * head) {
	Node * temp = head;
	while (temp -> next && -- idx)
		temp = temp -> next;

	if (idx)
		return -1;
	return temp -> v;
}

int findByValue(int v, Node * head) {
	Node * temp = head;
	int ret = 0;

	while (temp) {
		ret ++;
		if (temp -> v == v)
			return ret;

		temp = temp -> next;
	}

	return -1;
}

Node * deleteByIndex(int idx, Node * head) {
	if (idx < 1) {
		puts("NO SUCH NODE!!!");
		return head;
	}

	if (idx == 1)
		return head = head -> next;

	-- idx;
	Node * temp = head;
	while (temp -> next && -- idx)
		temp = temp -> next;

	if (idx) {
		puts("NO SUCH NODE!!!");
		return head;
	}

	temp -> next = temp -> next -> next;

	return head;
}

Node * deleteByValue(int val, Node * head) {
	Node * temp = head;

	while (temp -> next) {
		if (temp -> next -> v == val) {
			temp -> next = temp -> next -> next;
			return head;
		}

		temp = temp -> next;
	}

	puts("NO SUCH NODE!!!");
	return head;
}

Node * merge(Node * heada, Node * headb) {
	Node * ta = heada, * tb = headb, * headc = NULL;

	int v;
	while (ta || tb) {
		if (ta == NULL) {
			v = tb -> v;
			tb = tb -> next;
		}
		else if (tb == NULL) {
			v = ta -> v;
			ta = ta -> next;
		}
		else {
			if (ta -> v < tb -> v) {
				v = ta -> v;
				ta = ta -> next;
			}
			else {
				v = tb -> v;
				tb = tb -> next;
			}
		} 

		headc = insertInEnd(v, headc);
	}

	return headc;
}

int main() {
}
