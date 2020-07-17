
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
	inline double v(double x) {
		return k * x + b;
	}
} tr[400005];
const int mod = 39989;
inline bool cmp(node &a, node &b, int x) {
	return a.v(x) > b.v(x) || (a.v(x) == b.v(x) && (a.id < b.id));
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
inline void insert(int x, int l, int r, int al, int ar, node now) {
	if (l >= al && r <= ar) {
		change(x, l, r, now);
		return;
	}
	int mid = l + r >> 1;
	if (al <= mid) insert(x << 1, l, mid, al, ar, now);
	if (ar > mid) insert(x << 1 | 1, mid + 1, r, al, ar, now);
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
	int lastans = 0, cnt = 0;
	for (int i = 1; i <= n; ++i) {
		R(kind);
		if (kind == 1) {
			R(x0), R(y0),R(x1), R(y1);
			x0 = (x0 + lastans - 1) % 39989 + 1;
			x1 = (x1 + lastans - 1) % 39989 + 1;
			y0 = (y0 + lastans - 1) % 1000000000 + 1;
			y1 = (y1 + lastans - 1) % 1000000000 + 1;
			node temp;
			temp.id = ++cnt;
			if (x0 > x1) swap(x1, x0), swap(y0, y1);
			if (x0 == x1) temp.k = 0, temp.b = max(y0, y1);
			else temp.k = ((double)y1 - y0) / ((double)x1 - x0), temp.b = (double)y0 - temp.k * (double) x0;
			insert(1, 1, 40000, x0, x1, temp);
		} else {
			R(k);
			k = (k + lastans - 1) % 39989 + 1;
			lastans = query(1, 1, 40000, k).id;
			printf("%d\n", lastans);
		}
	}
}
