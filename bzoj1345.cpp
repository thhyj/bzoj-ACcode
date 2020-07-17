
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
		ch  = getchar();
	}
	if (p) v = -v;
}
int n, a[1000010], st[1000010], top;
int main() {
	R(n);
	int x;
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		R(x);
		while (top && st[top] <= x) {
			if (st[top - 1] < x && top != 1) {
				ans += st[top - 1];
			} else ans += x;
			top--;
		}
		st[++top] = x;
	}
	while (top > 1) {
		ans += st[--top];
	}
	printf("%lld\n", ans);
	return 0;
}
