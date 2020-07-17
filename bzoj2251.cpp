
#include <bits/stdc++.h>
using namespace std;
const int maxn = 6005;
int sa[maxn], rk[maxn], height[maxn], n, c[maxn];
char s[maxn];
inline void getsa(int m) {
	int i, j, k, *x = rk, *y = height;
	for (i = 0; i < n; ++i) c[x[i] = s[i]]++;
	for (i = 1; i < m; ++i) c[i] += c[i - 1];
	for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
	for (k = 1; k < n; k <<= 1) {
		j = 0;
		for (i = n - k; i < n; ++i) y[j++] = i;
		for (i = 0; i < n; ++i) if (sa[i] >= k) y[j++] = sa[i] - k;
		for (i = 0; i < m; ++i) c[i] = 0;
		for (i = 0; i < n; ++i) c[x[y[i]]]++;
		for (i = 1; i < m; ++i) c[i] += c[i - 1];
		for (i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		x[sa[0]] = j = 1;
		for (i = 1; i < n; ++i) x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? j : ++j;
		if (j == n) break;
		m = j + 1;
	}
	for (i = 0; i < n; ++i)
	{
		rk[sa[i]] = i;	/* code */
	}
	for (i = k = 0; i < n; ++i)
	{
		if (rk[i]) {
			j = sa[rk[i] - 1];
			for (k ? --k : 0; s[i + k] == s[j + k]; ++k);
			height[rk[i]] = k;
		}
	}
}
int main() {
	//freopen("sais.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", s);
	n = strlen(s);
	//printf("n=%d\n", n);
	getsa(128);
/*	for (int i = 0; i < n; ++i)
	{
		printf("%d ", sa[i]);
	}
	puts("");
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", rk[i]);
	}
	puts("");
	printf("n=%d\n", n);

	for (int i = 0; i < n; ++i)
	{
		printf("%d ", height[i]);
	}
	puts("");*/
		height[0] = 0;
	int cnt = 0;
	for (int k = 0; k < n; ++k) {
	//	printf("height[%d]=%d, n-sa[%d]=%d\n", k, height[k], k, n - sa[k]);
		for (int i = height[k]; i < n - sa[k]; ++i) {
			cnt = 1;
			for (int j = k + 1; j < n && height[j] > i; ++j)++cnt;
			if(cnt>1)
			printf("%d\n", cnt);
		}
	}
}
