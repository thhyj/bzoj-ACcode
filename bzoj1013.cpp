
#include <bits/stdc++.h>
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
using namespace std;
int n;
double ma[15][15];
double a[15][15];
inline double getabs(double x) {
	return x >= 0 ? x : -x;
}
inline void gao() {
	int r;
	double t;
	for (int i = 1; i <= n; ++i) {
		r = i;
		for (int j = i ; j <= n; ++j) {
			if (getabs(a[j][i]) > getabs(a[r][i])) r = j;
		}
		if (r != i) for (int j = i; j <= n + 1; ++j) swap(a[i][j], a[r][j]);

		for (int j = i + 1; j <= n; ++j) {
			t = a[j][i] / a[i][i];
			for (int k = i; k <= n + 1; ++k) {
				a[j][k] -= a[i][k] * t;
			}
		}
	}
/*	for(int i =1 ; i<=n; ++i) {
		for(int j = 1; j <= n + 1; ++j) {
			printf("%lf ",a[i][j]);
		}
		puts("");
	}*/
	for (int i = n; i ; --i) {
		for (int j = n; j > i; --j) {
			a[i][n + 1] -= a[i][j] * a[j][n + 1];
		}
		a[i][n + 1] /= a[i][i];
	}
}
int main() {
//	freopen("in.in","r",stdin);
	R(n);
	for (int i = 1; i <= n + 1; ++i) {
		for (int j = 1; j <= n; ++j)
			{scanf("%lf", &ma[i][j]);} 
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			a[i][j] = (ma[i][j] - ma[n + 1][j]) * 2;
		}
		for (int j = 1; j <= n; ++j)
			a[i][n + 1] += ma[i][j] * ma[i][j] - ma[n + 1][j] * ma[n + 1][j];
	}
/*	for(int i =1 ; i<=n; ++i) {
		for(int j = 1; j <= n + 1; ++j) {
			printf("%lf ",a[i][j]);
		}
		puts("");
	}*/
/*	for(int i =1 ; i<=n; ++i) {
		for(int j = 1; j <= n + 1; ++j) {
			printf("a[%d][%d] = %lf\n", i, j, a[i][j]);
		}
	}*/
	gao();
	for (int i = 1; i < n; ++i) {
		printf("%.3lf ", a[i][n + 1]);
	}
	printf("%.3lf", a[n][n + 1]);
}
