
#include<iostream>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<cstdlib>
#include<cstdio>
#include<map>
#include<bitset>
#include<set>
#include<stack>
#include<vector>
#include<queue>
using namespace std;
#define MAXN 200010
#define MAXM 20000010
#define ll long long
#define eps 1e-8
#define MOD 1000000007
#define INF 1000000000
char xB[1 << 15], *xS = xB, *xTT = xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
#define isd(c) (c>='0'&&c<='9')
int read() {
	char xchh;
	int xaa;
	while (xchh = getc(), !isd(xchh)); (xaa = xchh - '0');
	while (xchh = getc(), isd(xchh))xaa = xaa * 10 + xchh - '0'; return xaa;
}
struct vec {
	int fro;
	int l;
	int r;
	int v;
};
vec mp[MAXN * 4];
int tai[MAXN], cnt;
int n, m, p1, p2;
int a[MAXN];
ll v[MAXM], ch[MAXM];
int son[MAXM][2];
int st[MAXN], tp;
int L[MAXN], R[MAXN];
int rtl[MAXN], rtr[MAXN];
int tot;
inline void be(int x, int l, int r, int v) {
	mp[++cnt].fro = tai[x];
	tai[x] = cnt;
	mp[cnt].l = l;
	mp[cnt].r = r;
	mp[cnt].v = v;
}
void change(int &x, int xx, int y, int z, int l, int r, int cv) {
	if (l > r) {
		return ;
	}
	x = ++tot;
	v[x] = v[xx];
	ch[x] = ch[xx];
	memcpy(son[x], son[xx], sizeof(son[x]));
	v[x] += (ll)(r - l + 1) * cv;
	if (y == l && z == r) {
		ch[x] += cv;
		return ;
	}
	int mid = y + z >> 1;
	if (r <= mid) {
		change(son[x][0], son[xx][0], y, mid, l, r, cv);
	} else if (l > mid) {
		change(son[x][1], son[xx][1], mid + 1, z, l, r, cv);
	} else {
		change(son[x][0], son[xx][0], y, mid, l, mid, cv);
		change(son[x][1], son[xx][1], mid + 1, z, mid + 1, r, cv);
	}
}
ll ask(int x, int y, int z, int l, int r) {
	if (!x) {
		return 0;
	}
	if (y == l && z == r) {
		return v[x];
	}
	ll re = ch[x] * (r - l + 1);
	int mid = y + z >> 1;
	if (r <= mid) {
		return re + ask(son[x][0], y, mid, l, r);
	} else if (l > mid) {
		return re + ask(son[x][1], mid + 1, z, l, r);
	} else {
		return re + ask(son[x][0], y, mid, l, mid) + ask(son[x][1], mid + 1, z, mid + 1, r);
	}
}
int main() {
	int i, x, y;
	n = read();
	m = read();
	p1 = read();
	p2 = read();
	for (i = 1; i <= n; i++) {
		a[i] = read();
	}
	for (i = 1; i <= n; i++) {
		while (tp && a[st[tp]] < a[i]) {
			tp--;
		}
		L[i] = st[tp] + 1;
		st[++tp] = i;
	}
	st[tp = 0] = n + 1;
	for (i = n; i; i--) {
		while (tp && a[st[tp]] < a[i]) {
			tp--;
		}
		R[i] = st[tp] - 1;
		st[++tp] = i;
	}
	for (i = 1; i <= n; i++) {
		be(L[i] - 1, R[i] + 1, R[i] + 1, p1);
		be(L[i] - 1, i + 1, R[i], p2);
		be(R[i] + 1, L[i], i - 1, p2);
	}
	for (x = 1; x <= n; x++) {
		rtl[x] = rtl[x - 1];
		for (i = tai[x]; i; i = mp[i].fro) {
			if (mp[i].l > x) {
				change(rtl[x], rtl[x], 1, n, max(1, mp[i].l), min(n, mp[i].r), mp[i].v);
			}
		}
		if (x != n) {
			change(rtl[x], rtl[x], 1, n, x + 1, x + 1, p1);
		}
	}
	for (x = n; x; x--) {
		rtr[x] = rtr[x + 1];
		for (i = tai[x]; i; i = mp[i].fro) {
			if (mp[i].r < x) {
				change(rtr[x], rtr[x], 1, n, max(1, mp[i].l), min(n, mp[i].r), mp[i].v);
			}
		}
	}
	while (m--) {
		x = read();
		y = read();
		ll ans = 0;
		ans += ask(rtl[y], 1, n, x, y);
		ans -= ask(rtl[x - 1], 1, n, x, y);
		ans += ask(rtr[x], 1, n, x, y);
		ans -= ask(rtr[y + 1], 1, n, x, y);
		printf("%lld\n", ans);
	}
	return 0;
}
