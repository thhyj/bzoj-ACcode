
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
		v = (v + (v << 2) << 1) + (ch ^ '0');
		ch = getchar();
	}
	if (p)v = -v;
}
int n, m;
int k[200005], bl[200005], to[200005], st[200005];
int siz;
int temp, start;
inline void dfs(int x, int b) {
	while (bl[x] == b && x <= n) {
		x = x + k[x];
		++temp;
	}
	if (x <= n) {
		to[start] = x;
	} else {
		to[start] = n + 1;
	}
	st[start] = temp;
}
inline int query(int x) {
	int ret = 0;
	while (x <= n) {
		ret += st[x];
		x = to[x];
	}
	return ret;
}
inline void modify(int x, int y) {
	k[x] = y;
	if (bl[x + k[x]] != bl[x]) {
		to[x] = x + k[x], st[x] = 1;
	} else {
		to[x] = to[x + k[x]], st[x] = st[x + k[x]] + 1;
	}
	for (int i = x - 1; i >= bl[x] * siz; --i) {
		if (bl[i + k[i]] != bl[i]) {
			to[i] = i + k[i], st[i] = 1;
		} else {
			to[i] = to[i + k[i]], st[i] = st[i + k[i]] + 1;
		}
	}
}
int main () {
	R(n);
	siz = sqrt(n);
	for (int i = 1; i <= n; ++i) {
		R(k[i]);
		bl[i] = i / siz;
	}
	for (int i = 1; i <= n; ++i) {
		temp = 0;
		start = i;
		dfs(i, bl[i]);
	}
	int m;
	R(m);
	int kind;
	int x, y;
	for (int i = 1; i <= m; ++i) {
		R(kind);
		R(x);
		switch (kind) {
		case 1:
			printf("%d\n", query(x + 1));
			break;
		case 2:
			R(y);
			modify(x + 1, y);
		}
	}
	return 0;
}
