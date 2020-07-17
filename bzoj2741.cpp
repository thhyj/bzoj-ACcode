
#include <bits/stdc++.h>
#define F(i,j,n) for(int i=j;i<=n;i++)
#define D(i,j,n) for(int i=j;i>=n;--i)
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
inline void R (long long &v) {
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
int n, m, tot, block, num;
int a[20000], rt[20000], pos[20000], f[400][22000];
struct trie {
	int son[2], id;
} tr[800000];
inline void insert(int pre, int k, int x) {
	int now = rt[k] = ++tot; tr[tot].id = k;
	for (int i = 30; i >= 0; --i) {
		int j = (x >> i) & 1;
		tr[now].son[j ^ 1] = tr[pre].son[j ^ 1];
		tr[now].son[j] = ++tot; tr[tot].id = k;
		now = tr[now].son[j]; pre = tr[pre].son[j];
	}
}
inline int query(int l, int r, int x) {
	int ans = 0, tmp = rt[r];
	for (int i = 30; i >= 0; --i) {
		if (tr[tmp].id < l) break;
		int j = ((x >> i) & 1) ^ 1;
		if (tr[tr[tmp].son[j]].id >= l) ans |= (1 << i);
		else j ^= 1;
		tmp = tr[tmp].son[j];
	}
	return ans;
}
int main()
{
	R(n); R(m);
	block = sqrt(n);
	num = n / block + (n % block != 0);
	for (int i = 1; i <= n; ++i) {
		pos[i] = (i - 1) / block + 1;
	}
	tr[0].id = -1; insert(rt[0], 0, 0);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
		a[i] = a[i - 1] ^ a[i];
	}
	for (int i = 1; i <= n; ++i) {
		insert(rt[i - 1], i, a[i]);
	}
	for (int i = 1; i <= num; ++i) {
		for (int j = (i - 1) * block + 1; j <= n; ++j) {
			f[i][j] = max(f[i][j - 1], query((i - 1) * block + 1, j, a[j]));
		}
	}
	int ans = 0;
	while (m--) {
		long long l, r, x, y;
		R(x), R(y);
		l = ((long long)ans + x) % n + 1; r = ((long long)ans + y) % n + 1;
		if (l > r) swap(l, r);
		ans = 0; l--;
		if (pos[l] == pos[r]) {
			for (int i = l; i <= r; ++i) {
				ans = max(ans, query(l, r, a[i]));
			}
		}
		else {
			ans = f[pos[l] + 1][r];
			for (int i = l; i <= pos[l] * block; ++i) {
				ans = max(ans, query(l, r, a[i]));
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
