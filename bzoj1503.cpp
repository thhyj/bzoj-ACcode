
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
struct node *null, *tot, *t, *root;
int cg, xiajie;
int ans;
struct node {
	node *fa, *c[2];
	int siz, v, ben;
	node (): fa(null), ben(0), v(0), siz(0) {c[0] = c[1] = null;}
	inline void updata() {
		siz = c[0]->siz + c[1]->siz + ben;
	}
	inline void rotate(bool f) {
		node *o = fa;
		(fa = o->fa)->c[o->fa->c[1] == o] = this;
		(o->c[f] = c[!f])->fa = o;
		(c[!f] = o)->fa = this;
		o->updata();
	}
	inline void splay() {
		bool f;
		node *o = fa;
		for (; o != null; o = fa) {
			if (o->fa == null) {
				rotate(o->c[1] == this);
			} else {
				((f = o->c[1] == this) == (o->fa->c[1] == o)) ?
				(o->rotate(f), rotate(f)) : (rotate(f), rotate(!f));
			}
		}
		root = this;
		updata();
	}
	inline node* find(int zhi) {
		node *x = this;
		while (x->v != zhi) {
			x->v > zhi ? x = c[0] : x = c[1];
			if (x == null) return null;
		}
		x->splay();
		return x;
	}
	inline void insert(int zhi) {
		if (root == null) {
			++tot;
			tot->v = zhi;
			tot->fa = null;
			tot->ben++;
			tot->splay();
			root = tot;
			//	cout<<"tot="<<tot<<'\n';
			return ;
		}
		node *x = this, *z = this;
		bool f = 0;
		while (x != null && x->v != zhi) {
			z = x;
			x->v > zhi ? (x = x->c[0], f = 0) : (x = x->c[1], f = 1);
		}
		if (x->v == zhi) {
			//		cout << "123123\n";
			x->ben ++;
			x->splay();
			return;
		}
		++tot;
		tot->fa = z;
		//	cout << "z=" << z << '\n';
		z->c[f] = tot;
		tot->ben = 1;
		tot->v = zhi;
		tot->splay();
	}
	inline void merge(node *y) {
		if (this == null) {
			root = y; return;
		}
		if (y == null) {
			root = this; return;
		}
		node *x = this;
		while (x->c[1] != null) x = c[1];
		x->splay();
		x->c[1] = y;
		y->fa = x;
		root = x;
	}
	inline void del() {
		splay();
		c[1]->fa = c[0]->fa = null;
		c[0]->merge(c[1]);
		c[1] = c[0] = null;
	}
	int query(int k) {
		node *x = this;
		if (k <= c[1]->siz)return c[1]->query(k);
		if (k == c[1]->siz + 1)return v + cg;
		return c[0]->query(k - c[1]->siz - 1);
	}
	inline int getkth(int k) {
		node *x = this;
		//	cout << "x=" << x << '\n';
//		printf("x->siz = %d, x->ben = %d\n", x->siz, x->ben);
//		cout << "k=" << k << '\n';
		while (1) {
			if (x == null) return -1;
			if (k <= x->c[1]->siz) x = x->c[1];
			else if (k <= x->c[1]->siz + x->ben) return x->v + cg;
			else k -= x->c[1]->siz + x->ben, x = x->c[0];
		}
	}
} pool[100005];
inline void del(node* &x , node* f) {
	if (x == null) return ;
	if (x->v + cg >= xiajie) {
		del(x->c[0], x);
	} else {
		ans += x->c[0]->siz + x->ben;
		x = x->c[1];
		x->fa = f;
		if (f == null) root = x;
		del(x, f);
	}
	if (x != null)  x->splay();
}
inline void init() {
	null = root = tot = pool;
	null->fa = null->c[0] = null->c[1] = null;
	null->siz = null->ben = 0;
	null->v = 0x3f3f3f3f;
}
inline void shuchu(node *x) {
	//	cout << "x = " << x << " x->c[0] = " << x->c[0] << " x->c[1] = " << x->c[1] << '\n';
	//	printf("x->v = %d\n", x->v);
}
inline void bianli(node *x) {
	if (x == null) return;
	if (x->c[0] != null)
		bianli(x->c[0]);
	cout << "x = " << x << " x->c[0] = " << x->c[0] << " x->c[1] = " << x->c[1] << '\n';
	printf("x->v = %d, x->ben = %d\n", x->v + cg, x->ben);
	if (x->c[1] != null)
		bianli(x->c[1]);
}
int main () {
//	freopen("cashier2.in", "r", stdin);
	//freopen("cashier.out", "w", stdout);
	int n;
	init();
	R(n), R(xiajie);
	for (int i = 1; i <= 100000; ++i) {
		pool[i] = node();
	}
	char ch;
	int x;
	//	cout<<"root = "<<root<<" null = "<<null<<'\n';
	for (int i = 1; i <= n; ++i) {
		//	cout << "null->c[1] = " << null->c[1] << " null->c[0] = " << null->c[0] << '\n';
		do {
			ch = getchar();
		} while (!isupper(ch));
		//	cout << "root=" << root << '\n';
		switch (ch) {
		case 'I' : R(x); if (x >= xiajie) root -> insert(x - cg); //cout << "root=" << root << '\n';
			//	bianli(root);
			break;
		case 'S' : // cout << "root=" << root << '\n';
			R(x); cg -= x; del(root, null);
			//	cout << "root=" << root << '\n';
			//	bianli(root);
			break;
		case 'A' :  R(x); cg += x; break;
		case 'F' : //cout << "root=" << root << '\n';
			//	bianli(root); puts("F");
			R(x);
			//	printf("cg = %d\n", cg);
			if (root->siz < x) {puts("-1"); break;}
			printf("%d\n", root->getkth(x)); break;
		}
		//	puts("------------------------------------------------------");
	}
	printf("%d\n", ans);
	return 0;
}
