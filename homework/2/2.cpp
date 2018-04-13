#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ERROR -2

template<typename T>
struct LoopQueue {
	T * q;
	int head, tail, k;

	LoopQueue(int _k) {                // 新建的容量为k的循环队列
		k = _k;
		head = tail = 0;
		q = new T[k];
	}

	bool empty() {                     // 空
		return head == tail;
	}

	bool full() {                      // 满
		return (tail + 1) % k == head;
	}

	void push(T x) {                   // 把x入队
		if (full()) exit(ERROR);
		q[tail] = x;
		tail = (tail + 1) % k;
	}

	T front() {                        // 获取队头元素
		if (empty()) exit(ERROR);      // 空
		return q[head];
	}

	T end() { // 获取队尾元素
		if (empty()) exit(ERROR);      // 空
		return q[(tail - 1 + k) % k];
	}

	void pop() {                       // 弹出队头
		if (empty()) exit(ERROR);      // 空
		head = (head + 1) % k;
	}
};

void k_fibbonachi(int k, int MAX) {
	LoopQueue<int> q(k + 1);

	// init
	for (int i = 0; i < k - 1; i ++)
		q.push(0);
	q.push(1);

	int t;
	do {
		t = q.end() * 2 - q.front();
		q.pop();
		q.push(t);
	} while (t < MAX);


	cout << "result" << endl;
	for (int i = 0; i < k; i ++)
		cout << q.q[i] << " ";
	cout << endl;
}

int main() {
	k_fibbonachi(3, 10);
}
