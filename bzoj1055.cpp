
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
int W, I, N, G;
int ma[4][4][4];
int n, a[205];
int dp[205][205][4];
int main() {
	R(W), R(I), R(N), R(G);
	char ch;
	int x, y;
	for (int i = 1; i <= W; ++i) {
		do {
			ch = getchar();
		} while (!isupper(ch));
		switch (ch) {
		case 'W' : x = 0; break;
		case 'I' : x = 1; break;
		case 'N' : x = 2; break;
		case 'G' : x = 3; break;
		}
		do {
			ch = getchar();
		} while (!isupper(ch));
		switch (ch) {
		case 'W' : y = 0; break;
		case 'I' : y = 1; break;
		case 'N' : y = 2; break;
		case 'G' : y = 3; break;
		}
		ma[x][y][0] = 1;
	}
	for (int i = 1; i <= I; ++i) {
		do {
			ch = getchar();
		} while (!isupper(ch));
		switch (ch) {
		case 'W' : x = 0; break;
		case 'I' : x = 1; break;
		case 'N' : x = 2; break;
		case 'G' : x = 3; break;
		}
		do {
			ch = getchar();
		} while (!isupper(ch));
		switch (ch) {
		case 'W' : y = 0; break;
		case 'I' : y = 1; break;
		case 'N' : y = 2; break;
		case 'G' : y = 3; break;
		}
		ma[x][y][1] = 1;
	}
	for (int i = 1; i <= N; ++i) {
		do {
			ch = getchar();
		} while (!isupper(ch));
		switch (ch) {
		case 'W' : x = 0; break;
		case 'I' : x = 1; break;
		case 'N' : x = 2; break;
		case 'G' : x = 3; break;
		}
		do {
			ch = getchar();
		} while (!isupper(ch));
		switch (ch) {
		case 'W' : y = 0; break;
		case 'I' : y = 1; break;
		case 'N' : y = 2; break;
		case 'G' : y = 3; break;
		}
		ma[x][y][2] = 1;
	}
	for (int i = 1; i <= G; ++i) {
		do {
			ch = getchar();
		} while (!isupper(ch));
		switch (ch) {
		case 'W' : x = 0; break;
		case 'I' : x = 1; break;
		case 'N' : x = 2; break;
		case 'G' : x = 3; break;
		}
		do {
			ch = getchar();
		} while (!isupper(ch));
		switch (ch) {
		case 'W' : y = 0; break;
		case 'I' : y = 1; break;
		case 'N' : y = 2; break;
		case 'G' : y = 3; break;
		}
		ma[x][y][3] = 1;
	}
	char s[205];
	scanf("%s", s);
	n = strlen(s);
	for (int i = 0; i < n; ++i) {
		switch (s[i]) {
		case 'W' : a[i + 1] = 0; break;
		case 'I' : a[i + 1] = 1; break;
		case 'N' : a[i + 1] = 2; break;
		case 'G' : a[i + 1] = 3; break;
		}
	}
	for (int i = 1; i <= n; ++i) {
		dp[i][i][a[i]] = 1;
	}
	for (int i = n; i; --i) {
		for (int j = i; j <= n; ++j) {
			for (int k = 0; k < 4; ++k) {
				if (dp[i][j][k]) continue;
				for (int o = i; o < j; ++o) {
					for (int t = 0; t < 4; ++t) {
						if (!dp[i][o][t]) continue;
						for (int u = 0; u < 4; ++u) {
							if ((!dp[o + 1][j][u]) || (!ma[t][u][k])) continue;
							dp[i][j][k] |=  dp[i][o][t] && dp[i][o][t];
						}
					}
				}
			}
		}
	}
	bool pd = 0;
	if (dp[1][n][0]) cout << 'W', pd = 1;
	if (dp[1][n][1]) cout << 'I', pd = 1;
	if (dp[1][n][2]) cout << 'N', pd = 1;
	if (dp[1][n][3]) cout << 'G', pd = 1;
	if(!pd) {
		puts("The name is wrong!");
	}
	return 0;
}
