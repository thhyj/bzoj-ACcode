
#include <bits/stdc++.h>
#include <tr1/unordered_map>
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
	if (p)v = -v;
}
int n;
struct Node {
	int sc, sx;
	Node(int sc, int sx): sc(sc), sx(sx) {}
	Node() {}
};
inline bool operator <= (const Node &a, const Node &b) {
	return a.sc > b.sc || (a.sc == b.sc && a.sx <= b.sx);
}
inline bool operator < (const Node &a, const Node &b) {
	return a.sc > b.sc || (a.sc == b.sc && a.sx < b.sx);
}
inline bool operator == (const Node &a, const Node &b) {
	return a.sc == b.sc && a.sx == b.sx;
}
map<string, Node>ma;
map<Node, vector<char> >ma1;
struct node *null;
struct node {
	node *lc, *rc;
	int siz, rank;
	Node key;
	node(Node key = Node(0, 0)): rank(rand()), key(key), lc(null), rc(null), siz(1) {}
	inline void maintain() {
		siz = lc->siz + rc->siz + 1;
	}
}*rt, *pool[250005], data[250005];
int pooltop, datatop;
inline node* newnode(Node v) {
	node *x;
	if (pooltop) x = pool[pooltop--];
	else x = &data[++datatop];
	*x = node(v);
	return x;
}
inline void recycle (node *x) {
	pool[++pooltop] = x;
}
inline void clear(node *x) {
	if (x == null) return;
	clear(x->lc), clear(x->rc);
	recycle(x);
}
inline node* merge(node *x, node *y) {
	if (x == null) return y;
	if (y == null) return x;
	if (x->rank < y->rank) {
		x->rc = merge(x->rc, y);
		x->maintain();
		return x;
	} else {
		y->lc = merge(x, y->lc);
		y->maintain();
		return y;
	}
}
typedef pair<node*, node*> Pair;
inline Pair split(node *x, int k) {
	if (x == null) return make_pair(null, null);
	Pair t;
	if (x->lc->siz >= k) {
		t = split(x->lc, k);
		x->lc = t.second;
		t.second = x;
	} else {
		t = split(x->rc, k - x->lc->siz - 1);
		x->rc = t.first;
		t.first = x;
	}
	x->maintain();
	return t;
}
inline int getrank(node *x, Node k) {
	int ans = 0;
	while (x != null) {
		if(k <= x->key) x = x->lc; 
		else 
		ans += x->lc->siz + 1, x = x->rc;
	}
	return ans;
}
inline void insert(Node v) {
	int rank = getrank(rt, v);
	Pair t1 = split(rt, rank);
	node *x = newnode(v);
	rt = merge(merge(t1.first, x), t1.second);
}
int cnt;
inline void del(Node v) {
	int rank = getrank(rt, v);
	Pair t1 = split(rt, rank), t2 = split(t1.second, 1);
	rt = merge(t1.first, t2.second);
	clear(t2.first);
}
inline void bianli (node *x) {
	if (x == null) return;
	bianli(x->lc);
	if(cnt) printf(" ");
	for(int i = 0; i < ma1[x->key].size(); ++i) {
		putchar(ma1[x->key][i]);
	}
	++cnt;
	bianli(x->rc);
}
inline void getwanjia(int k) {
	cnt = 0;
	Pair t1 = split(rt, k - 1), t2 = split(t1.second, 10);
	bianli(t2.first);
	puts("");
	rt = merge(merge(t1.first, t2.first), t2.second);
}

inline void init() {
	null = newnode(Node(-INT_MAX, -INT_MAX));
	null->siz = 0;
}
int main () {
//	freopen("in.in", "r", stdin);
	R(n);
	char ch[105];
	init();
	string s;
	int x;
	int len;
	set<node>::iterator it;
	std::vector<char> temp;
	rt = null;
	for (int i = 1;  i <= n; ++i) {
		scanf("%s", ch);
		len = strlen(ch);
		if (ch[0] == '+') {
			s.clear();
			R(x);
			temp.clear();
			for (int j = 1; j < len; ++j) {
				temp.push_back(ch[j]);
				s+=ch[j];
			}
			ma1[Node(x, i)] = temp;
			if (ma.find(s) == ma.end()) {
				ma[s] = Node(x, i);
				insert(Node(x, i));
			} else {
				del(ma[s]);
				ma[s] = Node(x, i);
				insert(Node(x, i));
			}
		} else {
			if (isdigit(ch[1])) {
				x = 0;
				for (int j = 1; j < len; ++j) {
					x = (x + (x << 2) << 1) + (ch[j]^'0');
				}
				getwanjia(x);
			} else {
				s.clear();
				for (int j = 1; j < len; ++j) {
					s+=ch[j];
				}	
				printf("%d\n", getrank(rt, ma[s]) + 1);
			}
		}
	}
}
