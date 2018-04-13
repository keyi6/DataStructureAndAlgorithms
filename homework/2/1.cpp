#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}


void move(int * a, int len, int k) { // 循环右移k(k>0)位
    k %= len;
    if (k == 0) return;

    int temp;                        // 只允许使用一个元素大小的附加存储
    for (int i = 0, j; i < gcd(k, len); i ++) {
        temp = a[i];
        j = i;
        do {
            j = (j + k) % len;
            swap(a[j], temp);
        } while (j != i);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8}, len = 8;

    move(arr, len, 6);
    cout << "Result" << endl;
    for (int i = 0; i < len; i ++)
        cout << arr[i] << " ";
    cout << endl;
}
