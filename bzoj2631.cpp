
#include <bits/stdc++.h>
using namespace std;
struct node* null;
const int mod = 51061;
const int N = 100011;
struct node {
	node *fa, *c[2];
	bool rev;
	node *top;
	unsigned int siz, sum, add, mul, val;
	node(): siz(1), sum(1), val(1), mul(1), fa(null) {
		c[0] = c[1] = null;
	}
	inline void cover(const int &m, const int &a) {
		val = (val * m + a) % mod;
		sum = (sum * m + a * siz) % mod;
		add = (add * m + a) % mod;
		mul = mul * m % mod;
	}
	inline void updata() {
		sum = (c[0]->sum + c[1]->sum + val) % mod;
		siz = (c[0]->siz + c[1]->siz + 1) % mod;
	}
	inline void reverse() {
		rev ^= 1;
		swap(c[1], c[0]);
	}
	inline void pushdown() {
		if (rev) {
			c[0]->reverse(), c[1]->reverse(), rev = 0;
		}
		if (add != 0 || mul != 1) {
			c[0]->cover(mul, add), c[1]->cover(mul, add);
			mul = 1, add = 0;
		}
	}
	inline bool relation() {
		return fa->c[1] == this;
	}
	inline void rotate(const bool f) {
		node *o = fa;
		top = o->top;
		o->pushdown(), pushdown();
		(fa = o->fa)->c[o->relation()] = this;
		(o->c[f] = c[!f])->fa = o;
		(c[!f] = o)->fa = this;
		o->updata();
	}
	inline void splay() {
		bool f;
		node *o = fa;
		for (pushdown(); o != null; o = fa) {
			if (o->fa == null) {
				rotate(o->c[1] == this);
			} else {
				(f = o->c[1] == this) == (o->fa->c[1] == o)
				? (o->rotate(f), rotate(f)) : (rotate(f), rotate(!f));
			}
		}
		updata();
	}
	inline void expose(node * p = null) {
		splay();
		if (c[1] != null) {
			c[1]->top = this;
			c[1]->fa = null;
		}
		(c[1] = p)->fa = this;
		updata();
	}
	inline void access() {
		node *x = this;
		for (x->expose(); x->top; x = x->top)
			x->top->expose(x);
	}
	inline void evert() {
		access(); splay(); reverse();
	}
	inline void link(node *y) {
		y->evert();
		y->top = this;
	}
	inline void cut(node *y) {
		node *x = this;
		x->expose(), y->expose();
		if (x->top == y) x->top = NULL;
		if (y->top == x) y->top = NULL;
	}
	inline node* findroot() {
		node *f = this;
		f->access(), f->splay();
		while (f->pushdown(), f->c[0] != null)f = f->c[0];
		f->splay();
		return f;
	}
	inline void split(node *y) {
		y->evert(); access(); splay();
	}
} pool[N];
inline void init() {
	null = pool;
	null->fa = null;
	null->mul = 1;
	null->add = null->siz = null->val = null->sum = 0;
}
inline char nextChar() {
	static const int IN_LEN = 1000000;
	static char buf[IN_LEN], *s, *t;
	if (s == t) {
		t = (s = buf) + fread(buf, 1, IN_LEN, stdin);
		if (s == t) return -1;
	}
	return *s++;
}

inline int read() {
	static int x = 0;
	static char c;
	for (x = 0, c = nextChar(); !isdigit(c); c = nextChar());
	for (; isdigit(c); c = nextChar())
		x = (x + (4 * x) << 1) + (c ^ '0');
	return x;
}

const int OUT_LEN = 10000000;
char obuf[OUT_LEN], *oh = obuf;

template<class T>
inline void print(T x) {
	static int buf[30], cnt;
	if (x == 0) {
		*oh++ = '0';
	} else {
		if (x < 0) *oh++ = '-', x = -x;
		register int cnt = 0;
		for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
		while (cnt) *oh++ = buf[cnt--];
	}
}

template<class T>
inline void println(T x) {
	print(x), *oh++ = '\n';
}

inline void flush() {
	fwrite(obuf, 1, oh - obuf, stdout);
}

int n, q;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
#endif
	init();
	n = read(), q = read();
	for (register int i = 1; i <= n; i++) pool[i] = node();
	char s;
	register int x, y, z;
	for (register int i = 1; i < n; i++) (pool + read())->link(pool + read());

	for (register int i = 1; i <= q; i++) {
		s = nextChar(), x = read(), y = read();
		switch (s) {
		case '+':
			z = read(), (pool + x)->split(pool + y);
			(pool + x)->cover(1, z);
			break;
		case '-':
			(pool + x)->cut(pool + y),
			x = read(), y = read(),
			(pool + x)->link(pool + y);
			break;
		case '*':
			z = read(), (pool + x)->split(pool + y);
			(pool + x)->cover(z, 0);
			break;
		case '/':
			(pool + x)->split(pool + y), println((pool + x)->sum);
			break;
		}
	}
	flush();
	return 0;
}
