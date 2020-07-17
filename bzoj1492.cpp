
#include <bits/stdc++.h>
using namespace std;
inline void R (int &v) {
	bool p = 0;
	v = 0;
	static char ch;
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
struct point {
	double x, y, a, b, slop, rate;
	int id;
	point (double x, double y): x(x), y(y) {}
	point() {}
} p[100005], t[100005];
double f[100005];
inline bool cmp (const point &a, const point &b) {
	return a.slop > b.slop;
}
inline point operator - (const point &a , const point &b) {
	return point(a.x - b.x, a.y - b.y);
}
inline double operator * (const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
int st[100005];
inline double getslop(const point &a, const point &b) {
	if (a.x == b.x) return 1e20;
	return (a.y - b.y) / (a.x - b.x);
}
inline void solve(int l, int r) {
	if (l == r) {
		f[l] = max(f[l], f[l - 1]);
		p[l].y = f[l] / (p[l].a * p[l].rate + p[l].b);
		p[l].x = p[l].y * p[l].rate;
		return;
	}
//	printf("l = %d, r = %d\n", l, r );

	int mid = l + r >> 1, l1 = l, l2 = mid + 1;
	for (int i = l; i <= r; ++i) {
		if (p[i].id <= mid) t[l1++] = p[i];
		else t[l2++] = p[i];
	}
	for (int i = l; i <= r; ++i) {
		p[i] = t[i];
	}
	solve(l, mid);
	int top = 0;
	for (int i = l; i <= mid; ++i) {
		while (top > 1 && (p[st[top]] - p[st[top - 1]]) * (p[i] - p[st[top - 1]]) >= 0)--top;
		st[++top] = i;
	}
	int now = 1;
	for (int i = mid + 1; i <= r; ++i) {
		while (now < top && getslop(p[st[now]], p[st[now + 1]]) > p[i].slop)++now;
		f[p[i].id] = max(f[p[i].id], p[st[now]].x * p[i].a + p[st[now]].y * p[i].b);
	}
	solve(mid + 1, r);
	l1 = l, l2 = mid + 1;
	for (int i = l; i <= r; ++i) {
		if ((p[l1].x < p[l2].x || (p[l1].x == p[l2].x && p[l1].y < p[l2].y) || l2 > r) && l1 <= mid)t[i] = p[l1++];
		else t[i] = p[l2++];
	}
	for (int i = l; i <= r; ++i) p[i] = t[i];
}
int main() {
	int n, s;
	R(n), R(s);
	f[0] = s;
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf%lf", &p[i].a, &p[i].b, &p[i].rate);
		p[i].slop = -p[i].a / p[i].b;
		p[i].id = i;
	}
	sort(p + 1, p + n + 1, cmp);
	solve(1, n);
	printf("%0.3f\n", f[n]);
}
