
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
int n, q;
int h[50005];
int stmax[50005][20], stmin[50005][20];
int Log[50005];
inline void ST() {
	for (int j = 1; 1 << j <= n; ++j) {
		for (int i = 1; i + (1 << j) - 1<= n; ++i) {
			stmax[i][j] = max(stmax[i][j - 1], stmax[i + (1 << j - 1)][j - 1]);
			stmin[i][j] = min(stmin[i][j - 1], stmin[i + (1 << j - 1)][j - 1]);
		}
	}
//	for(int j = 1; j <= n; ++j) {
//		for (int i = 1; i <= 3; ++i) {
//			printf("stmax[%d][%d] = %d, stmin[%d][%d] = %d\n",j, i, stmax[j][i],j, i, stmin[j][i]);
//		}
//	}
	Log[1] = 0;
	for (int i = 2; i <= n; ++i) {
		Log[i] = Log[i >> 1] + 1;
	}
}
inline int querymax(int l, int r) {
//	printf("l = %d, Log[r - l + 1] = %d, r - (1 << Log[r - l + 1]) + 1 = %d\n",
//	l,Log[r - l + 1],r - (1 << Log[r - l + 1]) + 1);
	return max(stmax[l][Log[r - l + 1]], stmax[r - (1 << Log[r - l + 1]) + 1][Log[r - l + 1]]);
}
inline int querymin(int l, int r) {
	return min(stmin[l][Log[r - l + 1]], stmin[r - (1 << Log[r - l + 1]) + 1][Log[r - l + 1]]);
}
int main () {
	R(n);
	R(q);
	for (int i = 1; i <= n; ++i) {
		R(h[i]);
		stmax[i][0] = stmin[i][0] = h[i];
	}
	ST();
	int x, y;
	for (int i = 1; i <= q; ++i) {
		R(x), R(y);
		printf("%d\n", querymax(x, y) - querymin(x, y));
	}
	return 0;
}
