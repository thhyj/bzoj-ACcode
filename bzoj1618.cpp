
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
int dp[60005], p[105], c[105];
int inf;
int n, h;
int main() {
	memset(dp, 127, sizeof(dp));
	inf = dp[0];
	R(n), R(h);
	for (int i = 1; i <= n ; ++i) {
		R(p[i]), R(c[i]);
	}
	dp[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = p[i]; j <= h + c[i]; ++j) {
			if (dp[j - p[i]] != inf) dp[j] = min(dp[j], dp[j - p[i]] + c[i]);
		}
	}
	int ans = inf;
	for (int i = h; i <= h + 5000; ++i) {
		ans = min(dp[i], ans);
	}
	printf("%d\n",ans);
}
