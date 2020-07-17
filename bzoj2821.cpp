
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
const int N = 100005, M = 320;
int sum[M][N];
int f[M][M];
int bel[N];
int tsum[N];
int n, c, m;
int sz;
int a[N];
int cnt;
int l[M], r[M];
int main () {
	R(n), R(c), R(m);
	sz = sqrt(n);
	cnt = n / sz + 1;
	memset(l, 127, sizeof(l));
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
		bel[i] = i / sz + 1;
		l[bel[i]] = min(l[bel[i]], i);
		r[bel[i]] = max(r[bel[i]], i);
	}
	for (int i = 1; i <= cnt; ++i) {
		for (int j = 1; j <= c; ++j) {
			sum[i][j] = sum[i - 1][j];
		}
		for (int j = l[i]; j <= r[i]; ++j) {
			sum[i][a[j]]++;
		}
	}
//	for(int i = 1; i <= cnt; ++i) {
//		for(int j = 1; j <= c; ++j) {
//			printf("sum[%d][%d] = %d\n",i,j,sum[i][j]);
//		}
//	}
	int temp = 0;
	for (int i = 1; i <= cnt; ++i) {
//		printf("l[%d] = %d, r[%d] = %d\n", i, l[i], i, r[i]);
		for (int j = 1; j <= c; ++j) {
			tsum[j] = 0;
		}
		temp = 0;
		for (int j = i; j <= cnt; ++j) {
			for (int k = l[j]; k <= r[j]; ++k) {
				if (++tsum[a[k]] != 1) (tsum[a[k]] & 1) ? (temp--) : (temp++);
			}
			f[i][j] = temp;
		//	printf("f[%d][%d] = %d\n",i,j,f[i][j]);
		}
	}
	int x, y;
	int ans = 0;
	int L1, R1;
	memset(tsum, 0, sizeof(tsum));
	for (int i = 1; i <= m; ++i) {
		R(x), R(y);
		x = (x + ans) % n + 1, y = (y + ans) % n + 1;
		ans = 0;
		if (x > y) swap(x, y);
		L1 = bel[x], R1 = bel[y];
		if (L1 == R1) {
			for (int j = x; j <= y; ++j) {
				tsum[a[j]] = 0;
			}
			for (int j = x; j <= y; ++j) {
				if (++tsum[a[j]] != 1) (tsum[a[j]] & 1) ? (ans--) : (ans++);
			}
			printf("%d\n", ans);
			continue;
		}
		ans = f[L1 + 1][R1 - 1];
		for (int j = x; j <= r[L1]; ++j) 
			tsum[a[j]] = sum[R1 - 1][a[j]] - sum[L1][a[j]];
		for (int j = l[R1]; j <= y; ++j) 
			tsum[a[j]] = sum[R1 - 1][a[j]] - sum[L1][a[j]];
		for (int j = x; j <= r[L1]; ++j) {
			if (++tsum[a[j]] != 1) (tsum[a[j]] & 1) ? (ans--) : (ans++);
		}
		for (int j = l[R1]; j <= y; ++j) 
			if (++tsum[a[j]] != 1) (tsum[a[j]] & 1) ? (ans--) : (ans++);
		printf("%d\n", ans);
	}
}
