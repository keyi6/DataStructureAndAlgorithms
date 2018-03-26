#define PRON "extend_kmp"
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxl = 2000000 + 5;

// extend[i]为满足S[i..i+z-1]==T[0..z-1]的最大的z值
// Next[i]为满足T[i..i+z-1]==T[0..z-1]的最大的z值
int Next[maxl], extend[maxl];

void get_Next(char * T, int len) {
	memset(Next, 0, sizeof Next);
	int temp = 0;
	while (temp < len - 1 && T[temp] == T[temp + 1]) temp ++;

	Next[0] = len, Next[1] = temp;
	for (int i = 2, a = 1, p, L, j; i < len; i ++) {
		p = a + Next[a] - 1, L = Next[i - a];
		if (i - 1 + L >= p) {
			j = max(p - i + 1, 0);
			while (i + j < len && T[i + j] == T[j]) j ++;
			Next[i] = j, a = i;
		}
		else Next[i] = L;
	}
}

void extend_kmp(char * S, char * T) {
	int slen = strlen(S), tlen = strlen(T), temp = 0;
	while (temp < min(slen, tlen) && S[temp] == T[temp]) temp ++;

	get_Next(T, tlen);

	extend[0] = temp;
	for (int i = 1, a = 0, p, L, j; i < slen; i ++) {
		p = a + extend[a] - 1, L = Next[i - a];
		if (i - 1 + L >= p) {
			j = max(p - i + 1, 0);
			while (i + j < slen && j < tlen && S[i + j] == T[j]) j ++;
			extend[i] = j, a = i;
		}
		else extend[i] = L;
	}
}

char a[maxl], b[maxl];

int main(){
	scanf("%s %s", a, b);
	extend_kmp(a, b);
	puts("Next");
	for (int i = 0; i <= strlen(b); i ++)
		printf("%d ", Next[i]);
	puts("\nExtend");
	for (int i = 0; i <= strlen(a); i ++)
		printf("%d ", extend[i]);
}
