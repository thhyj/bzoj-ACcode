
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
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
	if (p)v = -v;
}
struct point {
	int x, y;
	point(int x , int y): x(x), y(y) {}
	point() {}
} p[500005];
point temp;
struct node {
	node *c[2];
	int kind;
	point p, r1, r2;
	node(int kind = 0):kind(0), c() {}
	node(int kind, point p) : kind(kind), p(p), r1(p), r2(p) {}
	inline void updata() {
		if (c[0]) {
			r1.x = min(r1.x, c[0]->r1.x);
			r1.y = min(r1.y, c[0]->r1.y);
			r2.x = max(r2.x, c[0]->r2.x);
			r2.y = max(r2.y, c[0]->r2.y);
		}
		if (c[1]) {
			r1.x = min(r1.x, c[1]->r1.x);
			r1.y = min(r1.y, c[1]->r1.y);
			r2.x = max(r2.x, c[1]->r2.x);
			r2.y = max(r2.y, c[1]->r2.y);
		}
	}
	inline int guji() {
		int ret = 0;
		if (temp.x < r1.x) ret += r1.x - temp.x;
		if (temp.x > r2.x) ret += temp.x - r2.x;
		if (temp.y < r1.y) ret += r1.y - temp.y;
		if (temp.y > r2.y) ret += temp.y - r2.y;
		return ret;
	}
} pool[500005 + 500005];
node *cur, *root;
int n, m;
bool flag;
inline bool cmp(const point &a, const point &b) {
	return flag ? (a.y < b.y || (a.y == b.y && a.x < b.x)) :
	       (a.x < b.x || (a.x == b.x && a.y < b.y));
}
inline bool getsplit(int l, int r) {
	double vx = 0, vy = 0, ax = 0, ay = 0;
	for (int i = l ; i <= r; ++i) ax += p[i].x, ay += p[i].y;
	ax /= r - l + 1, ay /= r - l + 1;
	for (int i = l; i <= r; ++i) {
		vx += (ax - p[i].x) * (ax - p[i].x), vy += (ay - p[i].y) * (ay - p[i].y);
	}
	return vx < vy;//鑻杞存柟宸ぇ鍒欒繑鍥?锛?鑻杞存柟宸ぇ鍒欒繑鍥?
}
inline void build(node *&x, int l, int r) {
	if (l > r) return;
	if (!x) x = ++cur;
	int mid = l + r >> 1;
	flag = getsplit(l, r);
	nth_element(p + l, p + mid, p + r + 1, cmp);
	*x = node(flag, p[mid]);
	build(x->c[0], l, mid - 1), build(x->c[1], mid + 1, r);
	x->updata();
}
int ans = INT_MAX;
#define getdis(a, b) (abs(a.x - b.x) + abs(a.y - b.y))
inline void query(node *x) {
	ans = min(ans, getdis(x->p, temp));
	int l =  x->c[0] ? x->c[0]->guji() : 0, r = x->c[1] ? x->c[1]->guji() : 0;
//	cout<<"l="<<l<<" r="<<r<<'\n';
	if (l < r) {
		if (x->c[0] && l < ans) query(x->c[0]);
		if (x->c[1] && r < ans) query(x->c[1]);
	} else {
		if (x->c[1] && r < ans) query(x->c[1]);
		if (x->c[0] && l < ans) query(x->c[0]);
	}
}
inline void insert(node *&x) {
	if (!x) {
		x = ++cur, *x = node((bool)rand(), temp); return;
	}
	if (x->kind ? (temp.y < x->p.y || (temp.y == x->p.y && temp.x < x->p.x)) :
	        (temp.x < x->p.x || (temp.x == x->p.x && temp.y < x->p.y)))  {
		insert(x->c[0]);
	} else insert(x->c[1]);
	x->updata();
}
int main() {
//	freopen("in.in", "r", stdin);
	cur = pool;
	R(n), R(m);
	for (int i = 1; i <= n ; ++i) {
		R(p[i].x), R(p[i].y);
	}
	build(root, 1, n);
	int t, x, y;
	for (int i = 1; i <= m; ++i) {
		R(t), R(temp.x), R(temp.y);
		if (t == 1) {
			insert(root);
		//	for (int i = 1; i <= (cur - pool); ++i) {
	//			printf("i = %d, kind = %d, r1.x = %d, r1.y = %d, r2.x = %d, r2.y = %d, p.x = %d, p.y = %d\n", i, (pool+i)->kind,(pool + i)->r1.x, (pool + i)->r1.y, (pool + i)->r2.x, (pool + i)->r2.y, (pool + i)->p.x, (pool + i)->p.y );
	//		}
		} else {
			ans = INT_MAX;
			query(root);
			printf("%d\n", ans);
		}
	}

}
