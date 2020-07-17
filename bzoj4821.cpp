
#include <bits/stdc++.h>
using namespace std;
inline char read() {
	static const int IN_LEN = 1024 * 1024;
	static char buf[IN_LEN], *s, *t;
	if (s == t) {
		t = (s = buf) + fread(buf, 1, IN_LEN, stdin);
		if (s == t) return -1;
	}
	return *s++;
}

///*
template<class T>
inline void R(T &x) {
	static char c;
	static bool iosig;
	for (c = read(), iosig = false; !isdigit(c); c = read()) {
		if (c == -1) return ;
		if (c == '-') iosig = true;
	}
	for (x = 0; isdigit(c); c = read())
		x = ((x << 2) + x << 1) + (c ^ '0');
	if (iosig) x = -x;
}
//*/

int n, m, x[100005], y[100005];
struct  tree {
	double sumx, sumy, sumxy, sumxx, tagx1, tagy1;
	bool tagx2;
} tr[400005];
inline void updata(int x) {
	tr[x].sumx = tr[x << 1].sumx + tr[x << 1 | 1].sumx;
	tr[x].sumy = tr[x << 1].sumy + tr[x << 1 | 1].sumy;
	tr[x].sumxy = tr[x << 1].sumxy + tr[x << 1 | 1].sumxy;
	tr[x].sumxx = tr[x << 1].sumxx + tr[x << 1 | 1].sumxx;
}
inline void build(int x1, int l , int r) {
	if (l == r) {
		tr[x1].sumx = x[l];
		tr[x1].sumy = y[l];
		tr[x1].sumxx = (double)x[l] * x[l];
		tr[x1].sumxy = (double)x[l] * y[l];
		return;
	}
	int mid  = l + r >> 1;
	build(x1 << 1, l , mid);
	build(x1 << 1 | 1, mid + 1, r);
	updata(x1);
}
struct dabao {
	double sumx, sumxy, sumxx, sumy;
	dabao(double sumx, double sumy, double sumxy, double sumxx): sumx(sumx), sumy(sumy), sumxy(sumxy), sumxx(sumxx) {}
	dabao() {}
};
inline dabao operator + (const dabao &a, const dabao &b) {
	return dabao(a.sumx + b.sumx, a.sumy + b.sumy, a.sumxy + b.sumxy, a.sumxx + b.sumxx);
}
#define sum2(x) ( (double)(x)*((x)+1)*(2*(x)+1)/6 )
#define add_tag(x, l, r) tr[(x)].sumxx = tr[(x)].sumxy = sum2((r)) - sum2((l) - 1); tr[(x)].sumx = tr[(x)].sumy = ((double)(l) + (r)) * ((r) - (l) + 1) / 2; tr[(x)].tagx1 = tr[(x)].tagy1 = 0; tr[(x)].tagx2 = 1;
#define add_x(x, l, r, v) tr[(x)].tagx1 += (v); tr[(x)].sumxx += 2 * (double)(v) * tr[(x)].sumx + (double)(v) * (v) * ((r) - (l) + 1); tr[(x)].sumxy += (double)(v) * tr[(x)].sumy; tr[(x)].sumx += (double)(v) * ((r) - (l) + 1);
#define add_y(x, l, r, v) tr[(x)].tagy1 += (v); tr[(x)].sumxy += (double)(v) * tr[(x)].sumx; tr[(x)].sumy += (double)(v) * ((r) - (l) + 1);
inline void pushdown(int x, int l, int r) {
	if (x == 0 || l == r) return ;
	int mid = l + r >> 1;
	if (tr[x].tagx2) {
		add_tag(x << 1, l, mid);
		add_tag(x << 1 | 1, mid + 1, r);
		tr[x].tagx2 = 0;
	}
	if (tr[x].tagx1) {
		add_x(x << 1, l, mid, tr[x].tagx1);
		add_x(x << 1 | 1, mid + 1, r, tr[x].tagx1);
		tr[x].tagx1 = 0;
	}
	if (tr[x].tagy1) {
		add_y(x << 1, l, mid, tr[x].tagy1);
		add_y(x << 1 | 1, mid + 1, r, tr[x].tagy1);
		tr[x].tagy1 = 0;
	}
}

inline dabao query(int x, int l, int r, int ql, int qr) {
	if (l >= ql && r <= qr) {
		return dabao(tr[x].sumx, tr[x].sumy, tr[x].sumxy, tr[x].sumxx);
	}
	pushdown(x, l , r);
	//updata(x);
	int mid = l + r >> 1;
	dabao ret = dabao(0, 0, 0, 0);
	if (ql <= mid) ret = ret + query(x << 1, l , mid, ql , qr);
	if (qr > mid) ret = ret + query(x << 1 | 1, mid + 1, r, ql, qr);
	return ret;
}
inline void add(int x, int l, int r, int al, int ar, int s, int t) {
	if (l >= al && r <= ar) {
		add_x(x, l, r, s);
		add_y(x, l, r, t);
		return;
	}
	int mid = l + r >> 1;
	pushdown(x, l, r);
	if (al <= mid) add(x << 1, l , mid , al , ar, s, t);
	if (ar > mid) add(x << 1 | 1, mid + 1, r, al, ar, s, t);
	updata(x);
}

inline void modify(int x, int l, int r, int al, int ar) {
	if (l >= al && r <= ar) {
		add_tag(x, l, r);
		return;
	}
	int mid = l + r >> 1;
	pushdown(x, l, r);
	if (al <= mid) modify(x << 1, l , mid , al , ar);
	if (ar > mid) modify(x << 1 | 1, mid + 1, r, al, ar);
	updata(x);
}
int main () {
	R(n), R(m);
	for (int i = 1 ; i <= n; ++i)
		R(x[i]);
	for (int i = 1; i <= n; ++i)
		R(y[i]);
	build(1, 1, n);
	int kind, l, r, s, t;
	dabao a;
	double len;
	for (int i = 1; i <= m; ++i) {
		R(kind);
		switch (kind) {
		case 1:
			R(l), R(r);
			a = query(1, 1, n, l, r);
			len = r - l + 1;
			printf("%0.10lf\n", (a.sumxy * len - a.sumx * a.sumy) / (a.sumxx * len - a.sumx * a.sumx));
			break;
		case 2:
			R(l), R(r), R(s), R(t);
			add(1, 1, n, l, r, s, t);
			break;
		case 3:
			R(l), R(r), R(s), R(t);
			modify(1, 1, n, l, r);
			add(1, 1, n, l, r, s, t);
			break;
		}
	}
	return 0;
}
