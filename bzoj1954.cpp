
#include<bits/stdc++.h>
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
int n;
struct node {
	int to, length;
	node(int to, int length): to(to), length(length) {}
	node() {}
};
std::vector<node> q[100005];
inline void create(int x, int y, int z) {
	q[x].push_back(node(y, z));
	q[y].push_back(node(x, z));
}
int d[100005];
inline void dfs(int x, int f) {
	node *p;
	for (int i = 0; i < q[x].size(); ++i) {
		p = &q[x][i];
		if (p->to != f) {
			d[p->to] = d[x] ^ p->length;
			dfs(p->to, x);
		}
	}
}
int ans;
struct trie {
	int son[2];
} tr[6200005];
int tot;
inline void build(int x) {
	int t;
	int now = 0;
	for (int i = 30; i >= 0; --i) {
		t = (x >> i) & 1;
		if (!tr[now].son[t]) {
			tr[now].son[t] = ++tot;
		}
		now = tr[now].son[t];
	}
}
inline int query(int x) {
	int t;
	int now = 0, ret = 0;
	for (int i = 30; i >= 0; --i) {
		t = ((x >> i) & 1);
		if (tr[now].son[t^1]) {
			ret += 1 << i;
			now = tr[now].son[t^1];
		} else now = tr[now].son[t];
	}
	return ret;
}
int main() {
	R(n);
	int x, y, z;
	for (int i = 1; i < n; ++i) {
		R(x), R(y); R(z);
		create(x, y, z);
	}
	dfs(1, 1);
	for (int i = 1; i <= n; ++i) {
//		printf("d[%d] = %d\n",i,d[i]);
		build(d[i]);
	}
	for (int i = 1; i <= n; ++i) {
		ans = max(ans, query(d[i]));
	}
	printf("%d\n", ans);
	return 0;
}
