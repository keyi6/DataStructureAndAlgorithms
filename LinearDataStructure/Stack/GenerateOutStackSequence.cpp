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

	if (str_head < len) {                                       // if thers exists element nerver in stack
		stack[stack_head] = str[str_head];                      // push this element into stack
		generate(str_head + 1, stack, stack_head + 1, out_seq);
	}

	if (stack_head > 0) {                                       // if stack is not empty
		char ch = stack[stack_head - 1];                        // make backup

		out_seq.push_back(stack[stack_head - 1]);               // pop head element
		generate(str_head, stack, stack_head - 1, out_seq);

		stack[stack_head - 1] = ch;                             // restore
	}
}


int main() {
	strcpy(str, "ABCD");
	len = strlen(str);

	generate(0, stack, 0, "");
 }
