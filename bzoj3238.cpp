
#include <bits/stdc++.h>
using namespace std;
char s[500005];
int sa[500005], rk[500005], height[500005], c[500005];
int n;
inline void getsa(int m) {
	int i , j , k, *x = rk, *y = height;
	for (i = 0; i < n; ++i) c[x[i] = s[i]]++;
	for (i = 1; i < m; ++i) c[i] += c[i - 1];
	for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
	for (k = 1; k < n; k <<= 1) {
		j = 0;
		for (i = n - k; i < n; ++i) y[j++] = i;
		for (i = 0; i < n; ++i) if (sa[i] >= k) y[j++] = sa[i] - k;
		for (i = 0; i < m; ++i)c[i] = 0;
		for (i = 0; i < n; ++i) c[x[y[i]]]++;
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
	for (i = 0; i < n; ++i) rk[sa[i]] = i;
	for (i = k = 0; i < n; ++i) {
		if (rk[i]) {
			j = sa[rk[i] - 1];
			for (k ? --k : 0; s[i + k] == s[j + k]; ++k);
			height[rk[i]] = k;
		}
	}
}
int st[500005], top;
long long ans;
inline void solve() {
	long long temp = 0;
	for (int i = 1; i <= n ; ++i) {
		while (top && height[st[top]] >= height[i]) {
			temp -= ((long long)st[top] - st[top - 1]) * height[st[top]];
			top--;
		}
		st[++top] = i;
	//	for(int i = 1; i<=top;++i) {
	//		printf("st[%d] = %d\n", i, st[i]);
	//	}
		temp += (st[top] - st[top - 1]) * height[st[top]];
		ans += temp;
	}
//	printf("%d\n",ans);
	ans = -2 * ans;
	ans += (long long)n * (n + 1) * (n - 1) / 2;
}
int main() {
	//freopen("in.in", "r", stdin);
	scanf("%s", s);
	n = strlen(s);
	getsa(128);
//	for (int i = 0; i < n; ++i) {
//		printf("%d ", sa[i] + 1);
//	}
//	puts("");
//	for (int i = 1; i < n; ++i) {
//		printf("%d ", height[i] );
//	}
//	puts("");
	solve();
	printf("%lld\n", ans);
}
