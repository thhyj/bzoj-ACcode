
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
int n, ans[1000005], st[1000005], top, h[1000005];
int main() {
	R(n);
	int x;
	for (int i = 1; i <= n; ++i) {
		R(h[i]);
	}
	for (int i = 1; i <= n; ++i) {
		while (top && h[st[top]] < h[i]) {
			ans[st[top]] = i;
			--top;
		}
		st[++top] = i;
	}
	for(int i = 1; i<=n; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
