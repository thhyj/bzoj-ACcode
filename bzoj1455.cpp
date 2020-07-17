
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
int n;
int fa[1000005];
inline int getfather(int x) {
	return x == fa[x] ? x : fa[x] = getfather(fa[x]);
}
struct tree {
	int ls, rs, dis, v;
} tr[1000005];
struct shibing {
	int f, id;
} s[1000005];
bool killed[1000005];
inline int merge(int x, int y) {
	if (!x) return y;
	if (!y) return x;
	if (tr[x].v > tr[y].v) swap(x, y);
	tr[x].rs = merge(tr[x].rs, y);
	if (tr[tr[x].ls].dis < tr[tr[x].rs].dis) swap(tr[x].ls, tr[x].rs);
	tr[x].dis = tr[tr[x].rs].dis + 1;
	return x;
}
int main() {
	R(n);
	int x;
	tr[0].dis = -1;
	for (int i = 1; i <= n; ++i) {
		R(x), s[i].id = i, s[i].f = x;
		tr[i].v = x;
		fa[i] = i;
	}
	int m;
	R(m);
	char ch;
	int l, r, temp,p ,q;
	for (int i = 1; i <= m; ++i) {
		scanf("%c", &ch);
		switch (ch) {
		case 'M':
			R(l), R(r);
			if (killed[l] || killed[r]) continue;
			p = getfather(l), q = getfather(r);
			if(p == q) continue;
			fa[p] = fa[q] = merge(p, q);
			//	printf("fa[%d] = %d, fa[%d] = %d\n",l,fa[l],r,fa[r]);
			break;
		case 'K':
			R(x);
			if (killed[x]) {
				puts("0");
				break;
			} else {
				temp = getfather(x);
				printf("%d\n", tr[temp].v);
				killed[temp] = 1;
				fa[temp] = merge(tr[temp].ls, tr[temp].rs);
				fa[fa[temp]] = fa[temp];
			}
		}
	}
	return 0;
}
