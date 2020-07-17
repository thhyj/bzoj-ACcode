
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
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
int st[10000005], top, n;
int main() {
	R(n);
	int x, y;
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		R(y), R(x);
		while (top && st[top] > x) {
			//++ans;
			--top;
		}
		if (st[top] != x) {
			++ans;
		}
		st[++top] = x;
	}
	printf("%d\n", ans);
	return 0;
}
