
#include <bits/stdc++.h>
using namespace std;
inline void R (int &v) {
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
int n, x, y;
int b[100005], m[100005];
int main() {
	R(n), R(x), R(y);
	for (int i = 1; i <= n; ++i) {
		R(m[i]), R(b[i]);
	}
	sort(m + 1, m + n + 1);
	sort(b + 1, b + n + 1);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (m[i] > b[i]) {
			ans += (m[i] - b[i]) * y;
		}
		if (m[i] < b[i]) {
			ans += (b[i] - m[i]) * x;
		}
	}
	printf("%d\n", ans);
}
