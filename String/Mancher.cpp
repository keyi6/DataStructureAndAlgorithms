#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2e6 + 10;

int len, id, ans, p[MAXN];
char c, s[MAXN];

inline int Manacher() {
	len = strlen(s), ans = id = 0;
	for (int i = len; i >= 0; i --) s[i * 2 + 2] = s[i], s[i * 2 + 1] = '#';
	s[0] = '!', len = len * 2 + 1;
	for (int i = 2; i < len; i ++) { 
		p[i] = p[id] + id > i ? min(p[id] + id - i, p[2 * id - i]) : 1; 
		while (s[i + p[i]] == s[i - p[i]]) p[i] ++;
		if (p[i] + i > p[id] + id) id = i;
		ans = max(ans, p[i]);
	}
	return ans - 1;
}

int main() { 
	while (~scanf("%s", s))
		printf("%d\n", Manacher());		
}
