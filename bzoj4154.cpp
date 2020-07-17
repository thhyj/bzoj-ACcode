
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
#define x1 ashkjig
#define y1 sagagga
#define x2 asdjlik
#define y2 afahlio
int x1, y1, x2, y2;
struct point {
	int x, y, v;
	point (int x, int y) : x(x), y(y) {}
	point() {}

} p[200005];
vector<int> q[100005];
int now;
inline bool pd(const point &a) {
	return a.x >= x1 && a.x <= x2 && a.y >= y1 && a.y <= y2;
}
struct node {
	node *c[2];
	int kind, sum, siz, tag, color;
	point p, r1, r2;
	node(int kind, point p): kind(kind), p(p), r1(p), r2(p), c(), sum(p.v), siz(1), tag(0), color(1) {}
	node(): c() {
	}
	inline void updata() {
		sum = p.v;
		siz = 1;
		if (c[0]) {
			r1.x = min(r1.x, c[0]->r1.x);
			r1.y = min(r1.y, c[0]->r1.y);
			r2.x = max(r2.x, c[0]->r2.x);
			r2.y = max(r2.y, c[0]->r2.y);
			sum += c[0]->sum;
			siz += c[0]->siz;
		}
		if (c[1]) {
			r1.x = min(r1.x, c[1]->r1.x);
			r1.y = min(r1.y, c[1]->r1.y);
			r2.x = max(r2.x, c[1]->r2.x);
			r2.y = max(r2.y, c[1]->r2.y);
			sum += c[1]->sum;
			siz += c[1]->siz;
		}
	}
	inline int check() {
		if (r1.x >= x1 && r2.x <= x2 && r1.y >= y1 && r2.y <= y2) {
			return 1;
		} else {
			if (r1.x > x2 || r2.x < x1 || r1.y > y2 || r2.y < y1) {
				return -1;
			}
			return 0;
		}
	}
};
struct memorypool {
	node buf[200005], *tail;
	node *st[200005];
	int top;
	memorypool() : top(0), tail(buf) {}
	inline node *New() {
		return top ? st[--top] : tail++;
	}
	inline void Delete(node *p) {
		st[top++] = p;
		*p = node();
	}
} pool;
inline long long sqr(int a) {
	return (long long)a * a;
}
inline bool getsplit(int l, int r) {
	double vx = 0, vy = 0, ax = 0, ay = 0;
	for (int i = l; i <= r; ++i) {
		ax += p[i].x, ay += p[i].y;
	}
	ax /= r - l + 1, ay /= r - l + 1;
	for (int i = l; i <= r ; ++i) {
		vx += sqr(p[i].x - ax), vy += sqr(p[i].y - ay);
	}
	return vx < vy;			// 切Y为1， 切X为0
}
node *root;
bool flag;
point temp;
inline bool cmp(const point &a, const point &b) {
	return flag ? (a.y < b.y || (a.y == b.y && a.x < b.x)) :
	       (a.x < b.x || (a.x == b.x && a.y < b.y));
}
inline void build(node *&x, int l, int r) {
	if (l > r) return;
	if (!x) x = pool.New();
	flag = getsplit(l, r);
	int mid = l + r >> 1;
	nth_element(p + l, p + mid, p + r + 1, cmp);
	*x = node(flag, p[mid]);
	build(x->c[0], l, mid - 1), build(x->c[1], mid + 1, r);
	x->updata();
}
int ans;
point t, t1, t2;
int col;
inline void pushdown(node *x) {
	if (!x || !x->tag)return;
	x->color = x->tag;
	if (x->c[0])
		x->c[0]->tag = x->tag;
	if (x->c[1])
		x->c[1]->tag = x->tag;
	x->tag = 0;
}
inline void modi(node *x) {
	if (!x)return;
//	printf("t1.x = %d, t2.x = %d, t1.y = %d, t2.y = %d, x->r1.x = %d, x->r2.x = %d, x->r1.y = %d, x->r2.y = %d, x->p.x = %d, x->p.y = %d, col = %d\n",t1.x , t2.x, t1.y, t2.y, x->r1.x, x->r2.x,x->r1.y,x->r2.y, x->p.x, x->p.y, col);
	pushdown(x);
	if (x->r1.x > t2.x || x->r2.x < t1.x || x->r1.y > t2.y || x->r2.y < t1.y)return;
	if (x->r1.x >= t1.x && x->r2.x <= t2.x && x->r1.y >= t1.y && x->r2.y <= t2.y){
//		puts("233");
		x->tag = col;
		return;
	}
	if (x->p.x >= t1.x && x->p.x <= t2.x && x->p.y >= t1.y && x->p.y <= t2.y)x->color = col;
	modi(x->c[0]); modi(x->c[1]);
}
inline void modify(int x1, int y1, int x2, int y2, int co) {
	t1.x = x1; t1.y = y1;
	t2.x = x2; t2.y = y2;
	col = co;
	modi(root);
}
int cnt;
int dep[100005], dfn[100005], ed[100005];
inline int getcolor(node *x) {
	if(!x) return 0;
//	printf("x->p.x = %d, x->p.y = %d\n", x->p.x, x->p.y);
	pushdown(x);
	if (t.x < x->r1.x || t.x > x->r2.x || t.y < x->r1.y || t.y > x->r2.y)return 0;
	if (x->p.x == t.x && x->p.y == t.y)return x->color;
	return getcolor(x->c[0]) + getcolor(x->c[1]);
}
inline int query(int x, int y) {
	t.x = x; t.y = y;
	return getcolor(root);
}
int tot;
inline void dfs(int x, int f) {
	dfn[x] = ++tot;
	int v;
	for (int i = 0; i < q[x].size(); ++i) {
		v = q[x][i];
		if (v == f) continue;
		dep[v] = dep[x] + 1;
		dfs(v, x);
	}
	ed[x] = tot;
}
const int mod = 1000000007;
int main () {
///	  freopen("in.in","r",stdin);

	srand(495);
	int T;
	R(T);
	long long ans = 0;
	while (T--) {
		memset(q, 0, sizeof(q));
		int n, c, q1;
		R(n), R(c), R(q1);
		int x, y;
		cnt = 0;
		tot = 0;
		ans = 0;
		for (int i = 2; i <= n; ++i) {
			R(x);
			q[x].push_back(i);
			q[i].push_back(x);
		}
		dep[1] = 1;
		dfs(1, 1);
		for (int i = 1; i <= n; ++i) {
			p[i].x = dfn[i], p[i].y = dep[i];
		}
		root = NULL;
	//	memset(pool.buf, 0, sizeof(pool.buf));
	//	memset(pool.st, 0, sizeof(pool.st));
	//	pool.top = 0;
	//	pool.tail = pool.buf;
		build(root, 1, n);
		int a, l;
		long long temp;
		for (int i = 1; i <= q1; ++i) {
			R(a), R(l), R(c);
			if (c == 0) {
				temp = query(dfn[a], dep[a]);
		//		printf("temp = %d\n", temp);
				ans = (ans + (long long)i * temp ) % mod;
			} else {
		//		printf("dfn[%d] = %d\n", a, dfn[a]);
				modify(dfn[a], dep[a], ed[a], dep[a] + l, c);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
