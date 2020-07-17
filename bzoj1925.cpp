
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
int n, p, dp[2][4205];
int main() {
	R(n), R(p);
	dp[0][1] = 1;
	int temp = 1;
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			dp[temp][j] = (dp[temp][j - 1] + dp[temp ^ 1][i - j + 1]) % p;
		}
		temp ^= 1;
	}
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += dp[temp ^ 1][i];
		ans %= p;
	}
	cout << ans * 2 % p;
}
