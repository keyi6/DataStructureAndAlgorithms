#define is_num(x) ('0' <= (x) && (x) <= '9')
#include <stack>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

int judge_priority(char ch1, char ch2) {
	if ((ch1 == '+' || ch1 == '-') && (ch2 == '+' || ch2 == '-')) return 0;
	if ((ch1 == '+' || ch1 == '-') && (ch2 == '*' || ch2 == '/')) return 1;
	if ((ch1 == '*' || ch1 == '/') && (ch2 == '*' || ch2 == '/')) return 0;
	if ((ch1 == '*' || ch1 == '/') && (ch2 == '+' || ch2 == '-')) return 0;
	if (ch1 == '(') return 1;
	return 0;
}


void covert_to_RPN(string exp) {
	stack<char> s;

	for (char ch: exp) {
		if (is_num(ch) || ch == '.')
			putchar(ch);
		else if (ch == '(' || s.empty())
			s.push(ch);
		else if (ch == ')') {
			while (not s.empty()) {
				putchar(s.top());
				s.pop();
				
				if (s.top() == '(') {
					s.pop();
					break;
				}
			}
		}	
		else {
			int t = judge_priority(s.top(), ch);
			if (t == 1) s.push(ch);
			else {
				while (not s.empty() && judge_priority(s.top(), ch) == 0) {
					putchar(s.top());
					s.pop();
				}

				s.push(ch);
			}
		}
	
	}
	while (not s.empty()) { putchar(s.top()); s.pop(); }
	putchar(10);
}


int main() {
	covert_to_RPN("(3*5+3-2+32)*6+4/5");
}
