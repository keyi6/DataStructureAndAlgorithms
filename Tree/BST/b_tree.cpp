#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
struct Node {
	vector<T> key;
	vector< Node<T> * > p;

	/* constructor */
	Node() { key.clear(), p.clear(); }

	/* ostream */
	friend ostream & operator << (ostream & out, const Node<T> & node) {
		out << "( ";
		for (T _key: node.key) out << _key << " ";
		out << ")";
		return out;
	}
};


template<typename T>
class BTree {
	private:
		int m;
		Node<T> * root;

	public:
		/* constructor */
		BTree(int _m) { m = _m, root = NULL; }


		/* find data*/
		bool find_data(T data) {
			Node<T> * cur = root;
			typename vector<T>::iterator iter;

			while (cur) {
				   iter = lower_bound(cur -> key.begin(), cur -> key.end(), data);
				   if (* iter == data) return true;
				   cur = cur -> p[iter - cur -> key.begin() + 1];
			}

			return false;
		}

		/* insert data */
		bool insert_data(T data) {
			Node<T> * cur = root;
			typename vector<T>::iterator iter;

			while (cur) {
				   iter = lower_bound(cur -> key.begin(), cur -> key.end(), data);
				   if (* iter == data) return false;
				   cur = cur -> p[iter - cur -> key.begin() + 1];
			}

			
			return true;
		}

		/* debug use */
		void bfs() {
			Node<T> * cur, * father;
			queue< pair< Node<T> *, Node<T> * > > q;

			q.push(make_pair(root, (Node<T> * )NULL));
			while (not q.empty()) {
				cur = q.front().first, father = q.front().second;
				q.pop();

				cout << (* cur); if (father) cout << "   [father]" << (* father) << endl;

				for (Node<T> * _p: cur -> p)
					q.push(make_pair(_p, cur));
			}
		}
};


int main() {
	BTree<int> bt(3);
	bt.bfs();
}
