
#include <bits/stdc++.h>
using namespace std;
const int maxn = 20005, maxm = 1000005;
inline void R(int &v) {
	static char ch;
	bool p = 0;
	v = 0;
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
int s[maxn], rk[maxn], sa[maxn], height[maxn], c[maxm];
int n;
inline void getsa(int m) {
	int i, j , k, *x = rk , *y = height;
	for (i = 0; i < n; ++i)c[x[i] = s[i]]++;
	for (i = 1; i < m; ++i) c[i] += c[i - 1];
	for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
	for (k = 1; k < n; k <<= 1) {
		j = 0;
		for (i = n - k; i < n; ++i) y[j++] = i;
		for (i = 0; i < n; ++i) if (sa[i] >= k)y[j++] = sa[i] - k;
		for (i = 0; i < m; ++i)c[i] = 0;
		for (i = 0; i < n; ++i)c[x[y[i]]]++;
		for (i = 1; i < m; ++i) c[i] += c[i - 1];
		for (i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		x[sa[0]] = j = 1;
		for (i = 1; i < n; ++i) {
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? j : ++j;
		}
		if (j == n) break;
		m = j + 1;
	}
	for (i = 0; i < n; ++i)rk[sa[i]] = i;
	for (i = k = 0; i < n; ++i) {
		if (rk[i]) {
			j = sa[rk[i] - 1];
			for (k ? --k : 0; s[i + k] == s[j + k]; ++k);
			height[rk[i]] = k;
		}
	}
}
int q[20005];
int main() {
	int k;
	//freopen("sais.in", "r", stdin);
	R(n), R(k);
	for (int i = 0; i < n; ++i) {
		R(s[i]);
	}
	getsa(maxm);
	--k;
	int ql = 1, qr = ql + k - 1, l = 1, r = 0;
	int ans = 0, mi = 1e9;

	for (int i = ql ; i <= qr; ++i) {
		while (r >= l && height[q[r]] > height[i])--r;
		q[++r] = i;
	}
			ans = max(ans, height[q[l]]);

	ql++, qr++;
	for (; qr <= n; ++ql, ++qr) {
		while (r >= l && q[l] < ql)++l;
		while (r >= l && height[q[r]] > height[qr])--r;
		q[++r] = qr;
		ans = max(ans, height[q[l]]);
	}
	printf("%d\n", ans);
}
