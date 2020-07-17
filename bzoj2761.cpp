
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
	static char ch;
	bool p = 0;
	v = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
int t, n;
map<int , bool>ma;
int main () {
	R(t);
	while (t--) {
		R(n);
		int x;
		ma.clear();
		R(x);
		if (!ma[x]) {
			printf("%d", x);
			ma[x] = 1;
		}
		for (int i = 2; i <= n; ++i) {
			R(x);
			if (!ma[x]) {
				printf(" %d", x);
				ma[x] = 1;
			}
		}
		if (t)
			puts("");
	}
	return 0;
}
