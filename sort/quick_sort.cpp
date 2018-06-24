#define DEBUG true
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;

void quick_sort(int * a, int l, int r) {
	if (l >= r) return;

	int base = a[l], i = l, j = r;
	while (i < j) {
		while (a[j] >= base && i < j) j --;
		a[i] = a[j];

		while (a[i] <= base && i < j) i ++;
		a[j] = a[i];
	}

	a[i] = base;
	if (DEBUG) {
		for (int i = l; i <= r; i ++)
			cout << a[i] << " ";
		cout << endl;
	}

	quick_sort(a, l, i - 1);
	quick_sort(a, i + 1, r);
}

int main() {
	int a[20] = {4, 1, 3, 2, 6, 5, 7}, n = 7;

	/*
	srand(time(NULL));
	for (int i = 0; i < n; i ++)
		a[i] = i + 1;//rand() % 30;
	*/

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
