#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXL = 100;

char str[MAXL], stack[MAXL];
int len;

void generate(int str_head, char * stack, int stack_head, string out_seq) {
	if (out_seq.length() == len) {
		cout << out_seq << endl;
		return;
	}

	if (str_head < len) {
		stack[stack_head] = str[str_head];
		generate(str_head + 1, stack, stack_head + 1, out_seq);
	}

	if (stack_head > 0) {
		char ch = stack[stack_head - 1];

		out_seq.push_back(stack[stack_head - 1]);
		generate(str_head, stack, stack_head - 1, out_seq);

		stack[stack_head - 1] = ch;
	}
}


int main() {
	strcpy(str, "ABCD");
	len = strlen(str);

	generate(0, stack, 0, "");
 }
