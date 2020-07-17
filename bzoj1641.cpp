
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
int n, m, t;
int ma[305][305];
int main () {
	R(n), R(m), R(t);
	int x, y, z;
	memset(ma, 127, sizeof(ma));
	for (int i = 1; i <= m; ++i) {
		R(x), R(y), R(z);
		ma[x][y] = z;
	}
	for (int i = 1; i <= n; ++i) {
		ma[i][i] = 0;
	}
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				ma[i][j] = min(max(ma[i][k], ma[k][j]), ma[i][j]);
			}
		}
	}
	for (int i = 1; i <= t; ++i) {
		R(x), R(y);
		if (ma[x][y] == 0x7f7f7f7f) {
			puts("-1");
		} else {
			printf("%d\n", ma[x][y]);
		}
	}
	return 0;
}
