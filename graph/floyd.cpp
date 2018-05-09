#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;

void floyd(int vex_num, int** g, int** dis) {
	for (int i = 0; i < vex_num; i ++)
		for (int j = 0; j < vex_num; j ++)
			dis[i][j] = g[i][j] ? 1 : INF;

	for (int k = 0; k < vex_num; k ++)
		for (int i = 0; i < vex_num; i ++)
			for (int j = 0; j < vex_num; j ++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}


int main() {

}
