
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
int n, m;
int b[205], c[205], q[20005], w[20005], dp[20005];
int main () {
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(b[i]);
	}
	for (int i = 1; i <= n; ++i) {
		R(c[i]);
	}
	R(m);
	memset(dp, 63, sizeof(dp));
	dp[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < b[i]; ++j) {
			int head = 1, tail = 0;
			for (int k = j; k <= m; k += b[i]) {
				while (head <= tail && w[head] < k - c[i] * b[i]) ++head;
				while (head <= tail && dp[k] - (k - w[head]) / b[i] <= q[tail]) --tail;
				q[++tail] = dp[k];
				w[tail] = k;
				dp[k] = min(dp[k], q[head] + (k - w[head]) / b[i]);
			}
		}
	}
	printf("%d", dp[m]);
	return 0;
}
