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

测试树🌲

```
    a                a
   / \              / \
  b   c      和    b   c
 / \                  / \
d   e                d   e
```

测试结果如下

![image-20180510103108433](/var/folders/px/t13qgjr56kn3s2_v51964wpw0000gn/T/abnerworks.Typora/image-20180510103108433.png)

![image-20180510103135672](/var/folders/px/t13qgjr56kn3s2_v51964wpw0000gn/T/abnerworks.Typora/image-20180510103135672.png)

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