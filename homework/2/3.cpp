#include <iostream>
#include <algorithm>
using namespace std;

#define ERROR -2
const int MAX_DEPTH = 10;

template<typename T>
struct LoopQueue {
	T * q;
	int head, tail, k;

	LoopQueue(int _k) {				   // 新建的容量为k的循环队列
		k = _k;
		head = tail = 0;
		q = new T[k];
	}

	bool empty() {					   // 空
		return head == tail;
	}

	bool full() {					   // 满
		return (tail + 1) % k == head;
	}

	void push(T x) {				   // 把x入队
		if (full()) exit(ERROR);
		q[tail] = x;
		tail = (tail + 1) % k;
	}

	T front() {						   // 获取队头元素
		if (empty()) exit(ERROR);	   // 空
		return q[head];
	}

	void pop() {					   // 弹出队头
		if (empty()) exit(ERROR);	   // 空
		head = (head + 1) % k;
	}
};


struct Node {
	char data;
	Node * l, * r;

	Node(char _data = ' ') {
		data = _data;
		l = r = NULL;
	}
};

int bfs(Node * head) {					 // 返回宽度
	LoopQueue< pair<Node *, int> > q(5); // 容量为10的循环队列

	q.push(make_pair(head, 0));

	int width[MAX_DEPTH];
	memset(width, 0, sizeof width);

	int depth;
	Node * cur;
	while (not q.empty()) {
		cur = q.front().first;
		depth = q.front().second;
		q.pop();

		width[depth] ++;

		if (cur -> l) q.push(make_pair(cur -> l, depth + 1));
		if (cur -> r) q.push(make_pair(cur -> r, depth + 1));
	}

	int max_width = 0;
	for (int i = 0; i < MAX_DEPTH; i ++)
		max_width = max(max_width, width[i]);

	return max_width;
}

Node * build_test_tree() {				  // 随便建一棵树
	Node * head = new Node('A');
	head -> l = new Node('B');
	head -> l -> l = new Node('C');
	head -> l -> r = new Node('D');
	head -> r = new Node('E');
	head -> r -> l = new Node('F');
	head -> r -> r = new Node('G');

	return head;
}


int main() {
	Node * head = build_test_tree();
	cout << "result\n" << bfs(head) << endl;
}
