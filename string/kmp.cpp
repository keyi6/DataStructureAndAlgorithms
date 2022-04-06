#include <string>
#include <iostream>
using namespace std;

const int maxn = 1000 + 10;


inline int kmp(string S, string T) {
	int lenS = S.length(), lenT = T.length(), next[maxn]; // next[i]为满足T[i-z+1..i] == T[0..z-1]的最大的z

	next[0] = -1;
	for (int i = 1, j = -1; i < lenT; i ++) {
		while (j >= 0 && T[j + 1] != T[i]) j = next[j];
		if (T[j + 1] == T[i]) j ++;
		next[i] = j;
	}

	for (int i = 0, j = -1; i < lenS; i ++) {
		while (j >= 0 && T[j + 1] != S[i]) j = next[j];
		if (T[j + 1] == S[i]) j ++;
		if (j == lenT - 1) return i - lenT + 1;			  // finsih
	}

	return -1;
}

int main(){
	string a = "dsad123123123ds4tfdf1213";
	string b = "123123123";

	cout << kmp(a, b) << endl;
}

