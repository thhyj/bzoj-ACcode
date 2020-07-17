
#include <bits/stdc++.h>
using namespace std;
inline char read() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
    return s == t ? -1 : *s++;
}
template <typename T>
inline void R(T &x) {
    static char c;
    static bool iosig;
    for (c = read(), iosig = false; !isdigit(c); c = read()) {
        if (c == -1) return;
        c == '-' ? iosig = true : 0;
    }
    for (x = 0; isdigit(c); c = read()) x = (x + (x << 2) << 1) + (c ^ '0');
    iosig ? x = -x : 0;
}
inline int read(char *buf) {
    register int s = 0;
    register char c;
    while (c = read(), isspace(c) && c != -1)
        ;
    if (c == -1) {
        *buf = 0;
        return -1;
    }
    do
        buf[s++] = c;
    while (c = read(), !isspace(c) && c != -1);
    buf[s] = 0;
    return s;
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
vector<point> q;
int now;
inline bool pd(const point &a) {
	return a.x >= x1 && a.x <= x2 && a.y >= y1 && a.y <= y2;
}
struct node {
	node *c[2];
	int kind, sum, siz;
	point p, r1, r2;
	node(int kind, point p): kind(kind), p(p), r1(p), r2(p), c(), sum(p.v), siz(1) {}
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
inline bool getresplit(int l, int r) {
	double vx = 0, vy = 0, ax = 0, ay = 0;
	for (int i = l; i <= r; ++i) {
		ax += q[i].x, ay += q[i].y;
	}
	ax /= r - l + 1, ay /= r - l + 1;
	for (int i = l; i <= r ; ++i) {
		vx += sqr(q[i].x - ax), vy += sqr(q[i].y - ay);
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
inline void zhongxubianli(node *x) {
	if (x->c[0]) zhongxubianli(x->c[0]);
	q.push_back(x->p);
	if (x->c[1]) zhongxubianli(x->c[1]);
	pool.Delete(x);
}
inline void rebuild(node *&x, int l, int r) {
	if (l > r) return;
	if (!x) x = pool.New();
	flag = getresplit(l, r);
	int mid = l + r >> 1;
	nth_element(q.begin() + l, q.begin() + mid, q.begin() + r + 1, cmp);
	*x = node(flag, q[mid]);
	rebuild(x->c[0], l, mid - 1), rebuild(x->c[1], mid + 1, r);
	x->updata();
}
inline void chonggou(node *&x) {
	q.clear();
	zhongxubianli(x);
	x = pool.New();
	rebuild(x, 0, q.size() - 1);
}
inline void insert(node *&x) {
	if (!x) {
		x = pool.New(), *x = node((bool)rand(), temp);
		//	cout<<"x="<<x<<" root="<<root<<'\n';
		//	printf("x->p.x = %d, x->p.y = %d, x->r1.x = %d, x->r1.y = %d, x->r2.x = %d, x->r2.y = %d\n", x->p.x, x->p.y, x->r1.x, x->r1.y, x->r2.x, x->r2.y);
		//x->updata();
		return;
	} else {
		if (x->kind ? (temp.y < x->p.y || (temp.y == x->p.y && temp.x < x->p.x)) :
		        (temp.x < x->p.x || (temp.x == x->p.x && temp.y < x->p.y))) {
			insert(x->c[0]);
		} else insert(x->c[1]);
		x->updata();
		if (max(x->c[0] ? x->c[0]->siz : 0, x->c[1] ? x->c[1]->siz : 0) >= 0.75 * x->siz) {
			chonggou(x);
		}
		//x->updata();
	}
}
int ans;
inline void query(node *x) {
	if (!x) return ;
	///printf("x->p.x = %d, x->p.y = %d, x->r1.x = %d, x->r1.y = %d, x->r2.x = %d, x->r2.y = %d\n", x->p.x, x->p.y, x->r1.x, x->r1.y, x->r2.x, x->r2.y);
	int p = x->check();
	if (pd(x->p)) ans += x->p.v;
	if (x->c[0]) {
		p = x->c[0]->check();
		if (p == 1) ans += x->c[0]->sum;
		else {
			if (p == 0) {
				query(x->c[0]);
			}
		}
	}
	if (x->c[1]) {
		p = x->c[1]->check();
		if (p == 1) ans += x->c[1]->sum;
		else {
			if (p == 0) {
				query(x->c[1]);
			}
		}
	}
}
int main () {
//	freopen("bzoj_4066.in", "r", stdin);
	//freopen("bzoj_4066.out", "w", stdout);
	srand(495);
	int T;
	R(T);
	int opt;
	int lastans = 0;
	while (1) {
		R(opt);
		if (opt == 1) {
			R(temp.x), R(temp.y), R(temp.v);
		//	temp.x ^= lastans, temp.y ^= lastans, temp.v ^= lastans;
			p[++now] = temp;
			insert(root);
		} else if (opt == 2) {
			ans = 0;
			R(x1), R(y1), R(x2), R(y2);
		//	x1 ^= lastans, y1 ^= lastans, x2 ^= lastans, y2 ^= lastans;
			query(root);
			lastans = ans;
			printf("%d\n", lastans);
		} else if (opt == 3) return 0;
	}
	return 0;
}
