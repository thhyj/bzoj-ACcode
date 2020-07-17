
#include <bits/stdc++.h>
using namespace std;
inline void  R (int &v) {
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
char s[205];
char ch[35][25];
int len[35];
bool f[205][205][35][25], c[205][205];
int dp[205];
int m;
int main() {
	scanf("%s", s + 1);
	int n;
	m = strlen(s + 1);
	R(n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", ch[i] + 1);
		len[i] = strlen(ch[i] + 1);
	}
	for (int i = m; i ; --i) {
		for (int j = i; j <= m; ++j) {
			for (int  k = 1; k <= n; ++k) {
				f[i][i - 1][k][0] = 1;
				for (int l = 1; l <= len[k]; ++l) {
					f[i][j][k][l] = (f[i][j - 1][k][l - 1] && s[j] == ch[k][l]);
					for (int o = i; o < j; ++o) {
						f[i][j][k][l] |= f[i][o][k][l] && c[o + 1][j];
					}
				}
			}
			for (int k = 1; k <= n && (!c[i][j]); ++k) {
				c[i][j] |= f[i][j][k][len[k]];
			}
		}
	}
	for (int i = 1; i <= m; ++i) {
		dp[i] = dp[i - 1] + 1;
		for (int j = 1; j <= i; ++j) if (c[j][i]) dp[i] = min(dp[i], dp[j - 1]);
	}
	printf("%d\n", dp[m]);
}
