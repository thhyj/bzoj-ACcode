
#include <bits/stdc++.h>
using namespace std;
int main () {
	char *a = new char();
	srand((int)(&a));
	puts("100000 100");
	for(int i = 1; i <= 100000; ++i) {
		putchar((char)(rand()%26 + 'a'));
	}
	return 0;
}
