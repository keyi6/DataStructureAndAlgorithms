#include <cstdio>

void merge(int l, int m, int r) {
	int i = l, j = m + 1, k = l;

	while (i <= m && j <= r) {
		if (a[i] > a[j]) {
			tem[k ++] = a[j ++];
			ans += m - i + 1;
		}
		else 
			tem[k ++] = a[i ++];
	}

	while (i <= m)
		tem[k ++] = a[i ++];
	while (j <= r)
		tem[k ++] = a[j ++];

	for (int i = 0; i < n; i ++)
		a[i] = tem[i]
}

void MergeSort(int l, int r) {
	if (l < r) {
		int m = (l + r) >> 1;
		MergeSort(l, m);
		MergeSort(m + 1, r);

		merge(l, m, r);
	}

}

int main(){  
}  
