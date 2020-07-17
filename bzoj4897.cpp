
#include <bits/stdc++.h>
using namespace std;
int g[52][52];
int f[52][52][52][52];
int b[52], gg[52];
int A, B;
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
int n;
struct shu {
	int zhi, id;
} a[52];
inline bool cmp(const shu &a, const shu &b) {
	return a.zhi < b.zhi;
}
int main() {
	R(n);
	R(A), R(B);
	for (int i = 1; i <= n; ++i) {
		R(a[i].zhi);
		a[i].id = i;
	}
	sort(a + 1, a + n + 1, cmp);
	int tot = 0;
	for (int i = 1; i <= n;) {
		int j = i + 1;
		while (j <= n && a[j].zhi == a[i].zhi) ++j;
		gg[++tot] = a[i].zhi;
		for (int k = i; k < j; ++k) {
			b[a[k].id] = tot;
		}
		i = j;
	}
//	for(int i = 1; i <= n; ++i) {
//	//}
	memset(g, 31, sizeof(g));
	memset(f, 31, sizeof(f));
	for (int i = 1; i <= n; ++i) {
		f[i][i][b[i]][b[i]] = 0;
		g[i][i] = A;
		g[i + 1][i] = 0;
	}
	g[n + 1][n] = 0;
	int tx, ty;
	for (int len = 2; len <= n; ++len) {
		for (int l = 1, r; (r = l + len - 1) <= n; ++l) {
			f[l][r][b[r]][b[r]] = g[l][r - 1];
			for (int i = l; i < r; ++i) {
				for (int j = 1; j <= tot; ++j) {
					for (int k = j; k <= tot; ++k) {
						int tj = min(j, b[r]), tk = max(k, b[r]);
						f[l][r][tj][tk] = min(f[l][r][tj][tk], f[l][i][j][k] + g[i + 1][r - 1]);
				//		printf("t[%d][%d][%d][%d] = %d t[%d][%d][%d][%d] = %d\n", l, r, tj, tk, f[l][r][tj][tk], l, i, j, k, f[l][i][j][k]);
				//		getchar();
					}
				}
			}
			for (int i = l; i <= r; ++i) {
				for (int j  = 1; j <= tot; ++j) {
					for (int k = j ; k <= tot; ++k) {
						g[l][r] = min(g[l][r], f[l][i][j][k] + g[i + 1][r] + A + B * (gg[k] - gg[j]) * (gg[k] - gg[j]));
					}
				}
			}
			//printf("g[%d][%d] = %d\n", l, r, g[l][r]);
		}
	}
	printf("%d\n", g[1][n]);
}
