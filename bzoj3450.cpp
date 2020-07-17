
#include <bits/stdc++.h>
using namespace std;
inline void R (int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-')p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
int n;
double a;
int main () {
	R(n);
	char ch;
	do {
		ch = getchar();
	} while (ch != 'o' && ch != '?' && ch != 'x');
	switch (ch) {
	case 'o': a = 1; break;
	case 'x': a = 0; break;
	case '?': a = 0.5; break;
	}
	double prex =  a, nowx, nowxx = a;
	for (int i = 2; i <= n; ++i) {
		do {
			ch = getchar();
		} while (ch != 'o' && ch != '?' && ch != 'x');
		switch (ch) {
		case 'o': a = 1; break;
		case 'x': a = 0; break;
		case '?': a = 0.5; break;
		}
		nowx = (prex + 1) * a;
		nowxx += (prex + prex + 1) * a;
		prex = nowx;
	}
	printf("%0.4f\n", nowxx);
	return 0;
}
