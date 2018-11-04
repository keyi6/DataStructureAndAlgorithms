#define PRON "select_Kth_element"
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;


int partion(vector<int>& a, int l, int r) {
	int i = l, j = r;
	int base = a[i];

	while (i < j) {
		while (a[j] >= base && i < j) j --;
		a[i] = a[j];

		while (a[i] <= base && i < j) i ++;
		a[j] = a[i];
	}

	a[i] = base;

	return i;
}

int findK(vector<int>& a, int l, int r, int k) {
	if (l == r) return a[l];

	int mid = partion(a, l, r);
	int len1 = mid - l + 1;

	if (k <= len1)
		return findK(a, l, mid, k);
	else
		return findK(a, mid + 1, r, k - len1);
}

int main() {
	vector<int> nums = {3,2,3,1,2,4,5,5,6};
	int k = 4;

	cout << findK(nums, 0, nums.size() - 1, k) << endl;
}
