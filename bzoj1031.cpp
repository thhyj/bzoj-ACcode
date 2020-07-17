
#include <bits/stdc++.h>
using namespace std;
char s[200005];
int rk[200005], sa[200005], height[200005], c[200005], n;
inline void gao(int m) {
	int *x = rk, *y = height, i, j, k;
	for (i = 0; i < n; ++i)c[x[i] = s[i]]++;
	for (i = 1; i < m; ++i) c[i] += c[i - 1];
	for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
	for (k = 1; k < n; k <<= 1) {
		j = 0;
		for (i = n - k; i < n; ++i) y[j++] = i;
		for (i = 0; i < n; ++i) if (sa[i] >= k) y[j++] = sa[i] - k;
		for (i = 0; i < m; ++i) c[i] = 0;
		for (i = 0; i < n; ++i)c[x[y[i]]]++;
		for (i = 1; i < m; ++i) c[i] += c[i - 1];
		for (i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		x[sa[0]] = j = 1;
		for (i = 1; i < n; ++i) {
			x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? j : ++j;
		}
		if (j == n) break;
		m = j + 1;
	}
}
int main () {
	scanf("%s", s);
	n = strlen(s);
	for (int i = n; i < n + n; ++i) {
		s[i] = s[i - n];
	}
	n = strlen(s);
	gao(128);
	n /= 2;
	int j = 0;
	for (int i = 0; i < n; ++i) {
		while (sa[j] >= n) ++j;
		putchar(s[sa[j] + n - 1]);
		++j;
	}
	return 0;
}
