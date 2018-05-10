# 说明
##一、运行环境

###1. 语言: c++ 11

### 2. 编译器(g++)版本



### 3. 编译命令

```bash
g++% -g -o %< -Wall -std=c++11
```

## 二、第一题

> 采用二叉链表存储表示，设计算法判断一个二叉树是否为完全二叉树

### 1. 测试

测试树🌲(输入为`test_tree_1`)

```
    a                a
   / \              / \
  b   c      和    b   c
 / \                  / \
d   e                d   e
```

测试结果如下

![Screen Shot 2018-05-10 at 11.27.38](/Users/cjhahaha/Desktop/Screen Shot 2018-05-10 at 11.27.38.png)

### 2. 算法说明

时间复杂度: O(n)

```cpp
bool is_complete_binary_tree(Node * root) {
    bool flag = false;
    queue<Node *> q;
    q.push(root);
    while (not q.empty()) {
        Node * cur = q.front();
        q.pop();

        if (cur -> r && ! cur -> l) return false;
        if (! cur -> l && ! cur -> r) flag = true;
        else if (flag && (cur -> l || cur -> r)) return false;

        if (cur -> l) q.push(cur -> l);
        if (cur -> r) q.push(cur -> r);
    }

    return true;
}
```

## 三、第二题

> 设森林采用二叉链表存储表示(孩子-兄弟表示法)，(1)设计非递归算法实现森林的中序遍历;(2)计算森林中的叶子结点数;(3) 计算森林中一共有几棵树;(4)求森林中第一棵树的高度。

```
    a                f
   / \              / \
  b   c            g   h
 / \                  / \
d   e                i   j
```



## 四、附加题

> 1. 实现二叉树先后遍历的非递归算法.
> 2. 树以双亲表示法存放，设计算法求树的高度

### 1. 测试

测试树🌲(输入为`test_tree_3`)

```
    a     
   / \   
  b   c        
 / \  
d   e   
```

输出结果

![Screen Shot 2018-05-10 at 11.24.13](/Users/cjhahaha/Desktop/Screen Shot 2018-05-10 at 11.24.13.png)

### 2. 算法说明

时间复杂度: O(n)

```cpp
void pre_order_traverse(Node * root) {  // 先序遍历
	stack< Node * > s;
	Node * p = root;

	while (not s.empty() || p) {
		while (p) {
			cout << p -> data;
			s.push(p);
			p = p -> l;
		}

		if (not s.empty()) {
			p = s.top();
			s.pop();
			p = p -> r;
		}
	}
}


void in_order_traverse(Node * root) {   // 中序遍历
	stack< Node * > s;
	Node * p = root;

	while (not s.empty() || p) {
		while (p) {
			s.push(p);
			p = p -> l;
		}

		if (not s.empty()) {
			p = s.top();
			s.pop();
			cout << p -> data;
			p = p -> r;
		}
	}
}


void post_order_traverse(Node * root) { // 后续遍历
	stack< Node * > s;
	Node * p = NULL, * pre = NULL;

	s.push(root);
	while (not s.empty()) {
		p = s.top();
		if ((p -> l == NULL && p -> r == NULL) || (p -> l == pre || p -> r == pre)) {
			s.pop(), pre = p;
			cout << p -> data;
		}
		else {
			if (p -> r) s.push(p -> r);
			if (p -> l) s.push(p -> l);
		}
	}
}	


int get_depth(Node * root) {           // 计算深度
	if (! root) return 0;

	Node * cur = NULL;
	int depth = 1, cur_d;
	queue< pair<Node *, int> > q;
	
	q.push(make_pair(root, 1));

    while (not q.empty()) {
        cur = q.front().first; 
		cur_d = q.front().second;
		q.pop();

		depth = max(depth, cur_d);

		if (cur -> l) q.push(make_pair(cur -> l, cur_d + 1));
		if (cur -> r) q.push(make_pair(cur -> r, cur_d + 1));
    }

	return depth;
}
```