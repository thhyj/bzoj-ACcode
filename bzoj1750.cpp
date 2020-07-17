
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
int dp[1005][35][2];
int main() {
	int n, p;
	R(n), R(p);
	int kind;
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		R(kind);
		dp[i][0][0] = dp[i - 1][0][0] + (kind == 1);
		dp[i][0][1] = dp[i - 1][0][1] + (kind == 2);
		for (int j = 1; j <= p; ++j) {
			dp[i][j][0] = max(dp[i - 1][j - 1][1], dp[i - 1][j][0]) + (kind == 1);
			dp[i][j][1] = max(dp[i - 1][j - 1][0], dp[i - 1][j][1]) + (kind == 2);
			ans = max(ans, max(dp[i][j][0], dp[i][j][1]));
		}
	}
	printf("%d\n", ans);
}
