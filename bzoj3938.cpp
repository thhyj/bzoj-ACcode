
#include<bits/stdc++.h>
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
	if (p) v = -v;
}
struct node {
	long long k, b;
	int id;
	int ls, rs;
	inline long long v(int x) {
		return k * x + b;
	}
} tr[200010 * 40];
struct P {
	int t, ty, l, r;
	long long k, b;
} line[700010];
int last[100010];
long long lastst[700010];
int tot, n, m;
inline bool cmp(node &a, node &b, int x) {
	if (a.v(x) == b.v(x) && a.id < b.id) return true;
	else if (a.v(x) > b.v(x)) return true;
	return false;
}
inline void change(int x, int l, int r, node now) {
	if (!tr[x].id) {
		tr[x].k = now.k;
		tr[x].b = now.b;
		tr[x].id = now.id;
		return;
	}
	if (cmp(now, tr[x], l)) {
		swap(now.k, tr[x].k);
		swap(now.b, tr[x].b);
		swap(now.id, tr[x].id);
	}
	if (tr[x].v(r) >= now.v(r)) return;
	int mid = l + r >> 1;
	double m = ((double)tr[x].b - (double)now.b) / ((double)now.k - (double)tr[x].k);
	//printf("x = %f\n", m);
	if (m <= mid) {
		if (!tr[x].ls) tr[x].ls = ++tot;
		change(tr[x].ls, l, mid , tr[x]);
		tr[x].k = now.k;
		tr[x].b = now.b;
		tr[x].id = now.id;
	} else {
		if (!tr[x].rs) tr[x].rs = ++tot;
		change(tr[x].rs, mid + 1, r , now);
	}
}
inline void insert(int x, int l, int r, int ql, int qr, node now) {
	if (l >= ql && r <= qr) {
		change(x, l, r, now);
		return;
	}
	int mid = l + r >> 1;
	if (ql <= mid) {
		if (!tr[x].ls) tr[x].ls = ++tot;
		insert(tr[x].ls, l, mid, ql, qr, now);
	}
	if (qr > mid) {
		if (!tr[x].rs) tr[x].rs = ++tot;
		insert(tr[x].rs, mid + 1, r, ql, qr, now);
	}
}
const long long inf = 1000000000000000000;
inline long long query(int x, int l, int r, int pos) {
	if (!x) return -inf;
	if (l == r) {
		return tr[x].v(l);
	}
	int mid = l + r >> 1;
	long long ret;
	if (pos <= mid) ret = query(tr[x].ls, l, mid, pos);
	else ret = query(tr[x].rs, mid + 1, r, pos);
	return max(ret, tr[x].v(pos));
}
int main() {
	R(n), R(m);
	tot = 2;
	int x;
	for (int i = 1; i <= n; ++i) {
		R(x);
		line[i].t = line[i].ty = line[i].l = 0;
		line[i].r = 1000000000;
		line[i].b = x, line[i].k = 0;
		last[i] = i;
		lastst[i] = x;
	}
	int t;
	char s[20];
	int pre, k;
	for (int i = n + 1; i <= n + m; ++i) {
		R(t);
		scanf("%s", s);
		if (s[0] == 'c') {
			R(k), R(x);
			pre = last[k];
			line[i].ty = 0;
			line[i].t = t;
			line[pre].r = line[i].l = t;
			line[i].r =  1000000000;
			line[i].k = x;
			lastst[i] = lastst[pre] + (line[pre].k * (line[pre].r - line[pre].l));
			line[i].b = lastst[i] - line[i].k * line[i].t;
			last[k] = i;
		} else {
			line[i].ty = 1;
			line[i].t = t;
		}
	}
	node temp;
	long long ans1, ans2;
	for (int i = 1; i <= n + m; ++i) {
		if (line[i].ty == 0) {
			temp.b = line[i].b, temp.k = line[i].k, temp.id = i;
			insert(1, 0, 1000000000, line[i].l, line[i].r, temp);
			temp.k = -temp.k;
			temp.b = -temp.b;
			insert(2, 0, 1000000000, line[i].l, line[i].r, temp);
		} else {
			ans1 = query(1, 0, 1000000000, line[i].t);
			ans2 = query(2, 0, 1000000000, line[i].t);
			printf("%lld\n", max(ans1, ans2));
		}
	}
}
