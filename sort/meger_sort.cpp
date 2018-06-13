#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;

int temp[20];

void merge(int * a, int l, int m, int r) {
	int i = l, j = m + 1, k = l;

	while (i <= m && j <= r) {
		if (a[i] > a[j])
			temp[k ++] = a[j ++];
		else
			temp[k ++] = a[i ++];
	}

	while (i <= m)
		temp[k ++] = a[i ++];
	while (j <= r)
		temp[k ++] = a[j ++];

	for (int i = 0; i < k; i ++)
		a[i] = temp[i];
}

void merge_sort(int * a, int l, int r) {
	if (l < r) {
		int m = (l + r) >> 1;
		merge_sort(a, l, m);
		merge_sort(a, m + 1, r);

		merge(a, l, m, r);
	}
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

	merge_sort(a, 0, n - 1);

	cout << "[after] ";
	for (int i = 0; i < n; i ++)
		cout << a[i] << " ";
	cout << endl;
}
