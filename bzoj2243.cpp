
#include <bits/stdc++.h>
using namespace std;
inline void R(int &v) {
	v = 0;
	bool p = 0;
	static char ch;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while ( !isdigit(ch) );
	while ( isdigit(ch) ) {
		v = ( v + ( v << 2 ) << 1 ) + ( ch ^ '0' );
		ch = getchar();
	}
	if (p) v = -v;
}
int a[400005];
int root, tot;
std::vector <int> q[400005];
inline void create(const int &x, const int &y) {
	q[x].push_back(y);
	q[y].push_back(x);
}
int cnt;
int num[400005], pos[400005], fa[400005], top[400005], son[400005], siz[400005], dep[400005];
inline void dfs1(int x) {
    siz[x] = 1;
    for (int i = 0; i < q[x].size(); ++i) {
         int v = q[x][i];
         if (v ^ fa[x]) {
              fa[v] = x;
              dep[v] = dep[x] + 1;
              dfs1(v);
              siz[x] += siz[v];
              if ( ( !son[x] ) || siz[v] > siz[son[x]] ) son[x] = v;
              }
         }
    }
inline void dfs2(int x) {
    pos[x] = ++cnt;
    num[pos[x]] = x;
    if (son[x]) {
         top[son[x]] = top[x];
         dfs2(son[x]);
         }
    for (int i = 0; i < q[x].size(); ++i) {
         int v = q[x][i];
         if ( ( v ^ son[x] ) && ( v ^ fa[x] ) ) {
              top[v] = v;
              dfs2(v);
              }
         }
    }
struct tree {
	int son[2], sum, lc, rc, tag;
} tr[400005];
inline void updata(const int &x) {
	tr[x].sum = tr[tr[x].son[0]].sum + tr[tr[x].son[1]].sum - ( tr[tr[x].son[0]].rc == tr[tr[x].son[1]].lc );
	tr[x].lc = tr[tr[x].son[0]].lc, tr[x].rc = tr[tr[x].son[1]].rc;
}
inline void build(int &x, int l, int r) {
	if (!x) x = ++tot;
	tr[x].tag = -1;
	if (l == r) {
		tr[x].sum = 1;
		tr[x].lc = tr[x].rc = a[num[l]];
		return;
	}
	int mid = l + r >> 1;
	build(tr[x].son[0], l, mid);
	build(tr[x].son[1], mid + 1, r);
	updata(x);
}
int n, m;
int lcol, rcol;
inline void pushdown(int x) {
	if (~tr[x].tag) {
		tr[tr[x].son[0]].sum = tr[tr[x].son[1]].sum = 1;
		tr[tr[x].son[0]].tag = tr[tr[x].son[1]].tag = tr[tr[x].son[0]].lc = tr[tr[x].son[0]].rc = tr[tr[x].son[1]].lc = tr[tr[x].son[1]].rc = tr[x].tag;
		tr[x].tag = -1;
	}
}
inline int query(int x, int ql, int qr, int l, int r) {
	if(l==ql) lcol = tr[x].lc;
	if(r==qr) rcol = tr[x].rc;
	if (ql <= l && qr >= r) {
		return tr[x].sum;
	}
	pushdown(x);
	int t1=-1,t2=-1;
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret += query(tr[x].son[0], ql, qr, l, mid), t1=tr[tr[x].son[0]].rc;
	if (qr > mid) ret += query(tr[x].son[1], ql, qr, mid + 1, r), t2=tr[tr[x].son[1]].lc;
	ret-=(t1==t2&&t1!=-1);
	return ret;
}
inline int trqc(int x, int y, int t1, int t2) {
	int ret=0;
	while (top[x] ^ top[y]) {
		//cout<<"top[x]="<<top[x]<<" top[y]="<<top[y]<<'\n';
		if (dep[top[x]] < dep[top[y]]) swap(x, y), swap(t1,t2);
		ret+=query(root, pos[top[x]], pos[x], 1, n);
		//cout<<"ret+="<<ret<<'\n';
		ret-= ( t1==rcol );
		//cout<<"ret-="<<ret<<'\n';
		x=fa[top[x]];
		t1=lcol;
	}
	if (dep[x] < dep[y]) swap(x, y), swap(t1,t2);
	ret+= query(root, pos[y], pos[x], 1, n);
	//cout<<"ret+="<<ret<<'\n';
	ret-=(t1==rcol&&t1!=-1)+(t2==lcol&&t2!=-1);
	//cout<<"ret-="<<ret<<'\n';
	return ret;
}
inline void modify(int x, int al, int ar, int l, int r, int c) {
	if (l >= al && r <= ar) {
		tr[x].lc = tr[x].rc = tr[x].tag = c;
		tr[x].sum = 1;
		return;
	}
	int mid = l + r >> 1;
	pushdown(x);
	if (al <= mid) modify(tr[x].son[0], al, ar, l, mid, c);
	if (ar > mid) modify(tr[x].son[1], al, ar, mid + 1, r, c);
	updata(x);
}
inline void trmd(int x, int y, int c) {
	if (top[x] ^ top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		modify(root, pos[top[x]], pos[x], 1, n, c), trmd(fa[top[x]], y, c);
	} else {
		if (dep[x] > dep[y]) swap(x, y);
		modify(root, pos[x], pos[y], 1, n, c);
		return;
	}
}

int main () {
	R(n), R(m);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
	}
	int x, y;
	for (int i = 1; i < n; ++i) {
		R(x), R(y);
		create(x, y);
	}
	fa[1] = dep[1] = top[1] = 1;
	dfs1(1);
	root = tot = 1;
	//tr[root].lc = tr[root].rc = -1;
	dfs2(1);
	build(root, 1, n);
	char ch;
	for(int i=1; i<=11; ++i) {
		//cout<<"i="<<i<<" tr[i].lc="<<tr[i].lc<<" tr[i].rc="<<tr[i].rc<<" tr[i].tag="<<tr[i].tag<<" tr[i].sum="<<tr[i].sum<<'\n';
	}
	int z;
	for (int i = 1; i <= m; ++i) {
		ch = getchar();
		while ( !isupper(ch) ) ch = getchar();
		if (ch == 'Q') {
			R(x), R(y);
			printf( "%d\n", trqc(x, y,-1,-1) );
		} else {
			R(x),R(y),R(z);
			trmd(x,y,z);
		}
	}
}
