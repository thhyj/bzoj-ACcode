
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
	double b, k;
	int id;
	node(double b, double k, int id): b(b), k(k), id(id) {}
	node() {
	}
	inline double v(int x) {
		return k * (x - 1) + b;
	}
} tr[400005];
inline bool cmp(node &a, node &b, int x) {
	return a.v(x) > b.v(x);
}
inline void change(int x, int l, int r, node now) {
	if (!tr[x].id) {tr[x] = now; return;}
	if (cmp(now, tr[x], l)) {
		swap(tr[x], now);
	}
	if (tr[x].v(r) > now.v(r)) return;
	int mid = l + r >> 1;
	double m = (now.b - tr[x].b) / (tr[x].k - now.k);
	if (m <= mid) change(x << 1, l, mid, tr[x]), tr[x] = now;
	else change(x << 1 | 1, mid + 1, r, now);
}
inline node query(int x, int l, int r, int pos) {
	if (l == r) {
		return tr[x];
	}
	int mid = l + r >> 1;
	node ret;
	if (pos <= mid) ret = query(x << 1, l, mid, pos);
	else ret = query(x << 1 | 1, mid + 1, r, pos);
//	printf("ret.id = %d\n", ret.id);
	if (cmp(ret, tr[x], pos)) return ret;
	else return tr[x];
}
int main() {
	int n;
	int kind, x0, x1, y1, y0, k;
	R(n);
	double lastans = 0;
	int cnt = 0;
	char ch[15];
	for (int i = 1; i <= n; ++i) {
		scanf("%s", ch);
		if (ch[0] == 'P') {
			node temp;
			scanf("%lf%lf", &temp.b, &temp.k);
			temp.id = ++cnt;
			change(1, 1, 50000, temp);
		} else {
			R(k);
			lastans = query(1, 1, 50000, k).v(k);
			printf("%lld\n", (long long)(lastans / 100));
		}
	}
}
