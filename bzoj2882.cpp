
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
struct node {
	map<int, int> son;
	int fa, max;
	node(int max, int fa): max(max), fa(fa) {}
	node() {}
} tr[1200005];
int cur, root, last;
int n;
int s[600005];
inline int extend(int ch, int v) {
	int u = ++cur;
	tr[u] = node(tr[v].max + 1, 0);
	while (v && tr[v].son.find(ch) == tr[v].son.end()) tr[v].son[ch] = u, v = tr[v].fa;
	if (!v) {
		tr[u].fa = root;
	} else {
		int o = tr[v].son[ch];
		if (tr[v].max + 1 == tr[o].max) {
			tr[u].fa = o;
		} else {
			int ne = ++cur;
			tr[ne] = node(tr[v].max + 1, tr[o].fa);
			tr[ne].son = tr[o].son;
			tr[u].fa = tr[o].fa = ne;
			while (v && tr[v].son.find(ch) != tr[v].son.end() && tr[v].son[ch] == o )tr[v].son[ch] = ne, v = tr[v].fa;
		}
	}
	return u;
}
int main () {
	cur = root = last = 1;
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(s[i]);
		s[i + n] = s[i];
	}
	n <<= 1;
	for (int i = 1; i <= n; ++i ) {
		last = extend(s[i], last);
	}
	int now = 1;
	n >>= 1;
	for (int i = 1; i < n; ++i) {
		printf("%d ", tr[now].son.begin()->first);
		now = tr[now].son.begin()->second;
	}
	printf("%d", tr[now].son.begin()->first);
	return 0;
}
