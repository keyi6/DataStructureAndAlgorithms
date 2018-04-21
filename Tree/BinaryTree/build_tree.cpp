#include <queue>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    char data;
    Node * l, * r;

    Node(char _data = ' ') { data = _data; l = r = NULL; }
};


void bfs(Node * root) {
    queue<Node *> q;
    q.push(root);
    while (not q.empty()) {
        Node * cur = q.front();
        q.pop();

        cout << cur -> data;

        if (cur -> l) q.push(cur -> l);
        if (cur -> r) q.push(cur -> r);
    }
}


void pre_order_dfs(Node * root) {
    if (!root) return;

    cout << root -> data;
    if (root -> l) pre_order_dfs(root -> l);
    if (root -> r) pre_order_dfs(root -> r);
}


void in_order_dfs(Node * root) {
    if (!root) return;
    
    if (root -> l) in_order_dfs(root -> l);
    cout << root -> data;
    if (root -> r) in_order_dfs(root -> r);
}


void post_order_dfs(Node * root) {
    if (!root) return;
    
    if (root -> l) post_order_dfs(root -> l);
    if (root -> r) post_order_dfs(root -> r);
    cout << root -> data;
}


void build_tree_with_pre_order_and_in_order(Node * & root, string pre_order, string in_order) {
    int len = pre_order.length(), root_idx = 0;
    if (len == 0) return;
    root = new Node(pre_order[0]);
    if (len == 1) return;

    while (in_order[root_idx] != pre_order[0] && root_idx < len)
        root_idx ++;

    string l_in_order = in_order.substr(0, root_idx),
           r_in_order = in_order.substr(root_idx + 1, len - root_idx - 1);
    string l_pre_order = pre_order.substr(1, root_idx),
           r_pre_order = pre_order.substr(root_idx + 1, len - root_idx - 1);

    build_tree_with_pre_order_and_in_order(root -> l, l_pre_order, l_in_order);
    build_tree_with_pre_order_and_in_order(root -> r, r_pre_order, r_in_order);
}


void build_tree_with_in_order_and_post_order(Node * & root, string in_order, string post_order) {
    int len = post_order.length(), root_idx = 0;
    if (len == 0) return;
    root = new Node(post_order[len - 1]);
    if (len == 1) return;

    while (in_order[root_idx] != post_order[len - 1] && root_idx < len)
        root_idx ++;

    string l_in_order = in_order.substr(0, root_idx),
           r_in_order = in_order.substr(root_idx + 1, len - root_idx - 1);
    string l_post_order = post_order.substr(0, root_idx),
           r_post_order = post_order.substr(root_idx, len - root_idx - 1);

    build_tree_with_in_order_and_post_order(root -> l, l_in_order, l_post_order);
    build_tree_with_in_order_and_post_order(root -> r, r_in_order, r_post_order);
}

int main() {
    string pre_order = "EABDCFHGIKJ",
           in_order =  "ABCDEFGHIJK";
    Node * root = NULL;
    build_tree_with_pre_order_and_in_order(root, pre_order, in_order);

    cout << "[bfs order]  ";
    bfs(root);
    cout << endl;

    cout << "[post order] ";
    post_order_dfs(root);
    cout << endl << endl;

    // =================

    string post_order = "dgbehifca";
           in_order = "dbgaecihf";
    root = NULL;
    build_tree_with_in_order_and_post_order(root, in_order, post_order);

    cout << "[bfs order]  ";
    bfs(root);
    cout << endl;

    cout << "[pre order]  ";
    pre_order_dfs(root);
    cout << endl << endl;
}
