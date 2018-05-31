#include <ctime>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

void quick_sort(int * a, int l, int r) {
	if (l >= r) return;

	int base = a[l], i = l, j = r;
	while (i < j) {
		while (a[j] > base && i < j) j --;
		while (a[i] < base && i < j) i ++;

		if (i < j)
			swap(a[i], a[j]);
	}

	swap(a[l], a[i]);

	quick_sort(a, l, i - 1);
	quick_sort(a, i + 1, r);
}

int main() {
	int a[20], n = 15;
	
	srand(time(NULL));
	for (int i = 0; i < n; i ++)
		a[i] = rand() % 30;

	cout << "[before] ";
	for (int i = 0; i < n; i ++)
		cout << a[i] << " ";
	cout << endl;

	quick_sort(a, 0, n - 1);

	cout << "[after] ";
	for (int i = 0; i < n; i ++)
		cout << a[i] << " ";
	cout << endl;
}
