
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
	if (p) v = -v;
}
struct point {
	int x, y, id;
	point(int x, int y): x(x), y(y) {}
	point() {}
} p[100005];
point temp;
struct node {
	node *c[2];
	int kind;
	point p, r1, r2;
	node(int kind = 0) : kind(0), c() {}
	node(int kind, const point &p): kind(kind), p(p), r1(p), r2(p), c() {}
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
	inline long long guji() {
		return max((long long)(r1.x - temp.x) * (long long)(r1.x - temp.x), (long long)(r2.x - temp.x) * (long long)(r2.x - temp.x)) +
		       max((long long)(r1.y - temp.y) * (long long)(r1.y - temp.y), (long long)(r2.y - temp.y) * (long long)(r2.y - temp.y));
	}

} pool[100005];
node *cur = pool;
bool flag;
inline bool cmp(const point &a, const point &b) {
	return flag ?
	       (a.y < b.y || (a.y == b.y && a.x < b.x))
	       : (a.x < b.x || (a.x == b.x && a.y < b.y));
}
struct zt {
	long long juli;
	int id;
	zt(long long juli, int id) : juli(juli), id(id) {}
	zt() {}
};
inline bool operator < (const zt &a, const zt &b) {
	return (a.juli > b.juli || (a.juli == b.juli && a.id < b.id));
}
priority_queue<zt>q;
inline bool getsplit(int l, int r) {
	double vx = 0, vy = 0, ax = 0, ay = 0;
	for (int i = l; i <= r; ++i) {
		ax += p[i].x, ay += p[i].y;
	}
	ax /= r - l + 1, ay /= r - l + 1;
	for (int i = l; i <= r; ++i) {
		vx += (p[i].x - ax) * (p[i].x - ax);
		vy += (p[i].y - ay) * (p[i].y - ay);
	}
	return vx < vy;
}

int n, k;
node *root;
inline void build(node *&x, int l, int r) {
	if (l > r) return;
	if (!x) x = ++cur;
//	cout<<"x="<<x<<'\n';
	int mid = l + r >> 1;
	flag = getsplit(l, r);
//	printf("l = %d, mid = %d, r = %d\n",l, mid, r);
//	cout<<"flag = "<<flag<<'\n';
//	for(int i = 1; i<=n; ++i) {
//	printf("p[%d].x = %d, p[%d].y = %d\n",i,p[i].x, i,p[i].y);
//	}

	nth_element(p + l, p + mid, p + r + 1, cmp);
//	sort(p + l, p + r + 1, cmp);
	*x = node(flag, p[mid]);
	build(x->c[0], l, mid - 1), build(x->c[1], mid + 1, r);
	x->updata();
}
#define getdis(a,b) ((long long)(a.x - b.x) * (long long)(a.x - b.x) + (long long)(a.y - b.y) * (long long)(a.y - b.y))
inline void query (node *x) {
	zt d = zt(getdis(temp, x->p), x->p.id);
//	printf("d.juli = %d, d.id = %d, q.top().juli = %d, q.top().id = %d\n",d.juli, d.id, q.top().juli, q.top().id);
	if (d.juli > q.top().juli || (d.juli == q.top().juli && d.id < q.top().id))q.pop(), q.push(d);
	long long l = x->c[0] ? x->c[0]->guji() : 0, r = x->c[1] ? x->c[1]->guji() : 0;
	if (l > r) {
		if (x->c[0] && l >= q.top().juli) query(x->c[0]);
		if (x->c[1] && r >= q.top().juli) query(x->c[1]);
	} else {
		if (x->c[1] && r >= q.top().juli) query(x->c[1]);
		if (x->c[0] && l >= q.top().juli) query(x->c[0]);
	}
}
int m;
int main () {
	//freopen("in.in", "r", stdin);
	R(n);
	for (int i = 1; i <= n; ++i)  {
		R(p[i].x), R(p[i].y);
		p[i].id = i;
	}
	R(m);
	build(root, 1, n);
	for (int i = 1; i <= m; ++i) {
		R(temp.x), R(temp.y); R(k);
		while (!q.empty())q.pop();
		for (int i = 1; i <= k; ++i) {
			q.push(zt(-1, 0));
		}
		query(root);			
		printf("%d\n", q.top().id);
		//puts("done");
	}
	return 0;
}
