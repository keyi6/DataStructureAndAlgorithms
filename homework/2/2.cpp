#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define OVERFLOW -1
#define ERROR -2

struct LoopQueue {
	int * q, head, tail, k;

	LoopQueue(int _k) { // 新建的容量为k的循环队列
		k = _k;
		head = tail = 0;
		q = new int[k];
	}

	void push(int x) {
		if ((tail + 1) % k == head) exit(ERROR); // 满
		q[tail] = x;
		tail = (tail + 1) % k;
	}

	int top() {
		if (tail == head) exit(ERROR); // 空
		return q[head];
	}

	void pop() {
		if (tail == head) exit(ERROR); // 空
		head = (head + 1) % k;
	}
};


int main() {
	int k = 10;

}
