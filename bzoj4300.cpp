
#include <bits/stdc++.h>
using namespace std;
inline void R (int &v) {
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
priority_queue<int> dui[32];
#define bin(x) (1<<x)
int n, a[100005];
int ans[100005];
int main() {
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
	}
	for (int i = n; i; --i) {
		for (int j = 0; j <= 30; ++j) {
			if (!(bin(j)&a[i])) continue;
			ans[i] = max((dui[j].size() ? dui[j].top() : 0) + 1, ans[i]);
		}
		for (int j = 0; j <= 30; ++j) {
			if (!(bin(j)&a[i]))continue;
			dui[j].push(ans[i]);
		}
	}
	int daan = 0;
	for (int i = 1; i <= n; ++i) {
		daan = max(daan, ans[i]);
	}
	printf("%d\n", daan);
}
