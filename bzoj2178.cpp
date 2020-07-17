
#include <bits/stdc++.h>
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
int n;
struct node {
	double x, y, r;
} a[1005], b[1005];
struct line {
	double l, r;
} p[1005];
inline bool cmp(const node &a, const node &b) {
	return a.r < b.r;
}
inline double getdis(const node &a, const node &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
bool useless[1005];
int cnt;
int st, ed;
inline bool cmp1(const node &a, const node &b) {
	return a.x - a.r < b.x - b.r;
}
inline bool cmp2(const line &a, const line &b) {
	return a.l < b.l;
}
double xl[1005], xr[1005];
inline double getf(double x) {
	double dis;
	int tot = 0;
	double len = 0;
	for (int i = st; i <= ed; ++i) {
		if (xl[i] >= x || xr[i] <= x) continue;
		dis = sqrt(b[i].r - (x - b[i].x) * (x - b[i].x));
		p[++tot].l = b[i].y - dis, p[tot].r = b[i].y + dis;
	}
	sort(p + 1, p + tot + 1, cmp2);
	double r;
	int j;
	for (int i = 1; i <= tot; ++i) {
		r = p[i].r;
		for (j = i + 1; j <= tot ; ++j) {
			if (p[j].l > r) break;
			r = max(r, p[j].r);
		}
		len += r - p[i].l, i = j - 1;
	}
	return len;
}
double ans;
const double eps = 1e-13;
inline double calc(double len, double fl, double fmid, double fr) {
	return ((len) / 6.0) * (fl + 4.0 * fmid + fr);
}
inline double simpson(double l, double mid, double r, double fl, double fmid, double fr, double s) {
	double m1 = (mid + l) / 2, m2 = (r + mid) / 2, f1, f2;
	f1 = getf(m1), f2 = getf(m2);
	double g1 = calc(mid - l, fl, f1, fmid), g2 = calc(r - mid, fmid, f2, fr);
	if (fabs(g1 + g2 - s) < eps) return g1 + g2;
	return simpson(l, m1, mid, fl, f1, fmid, g1) + simpson(mid, m2, r, fmid, f2, fr, g2);
}
inline void solve() {
	for (int i = 1; i <= cnt; ++i) xl[i] = b[i].x - b[i].r, xr[i] = b[i].x + b[i].r, b[i].r *= b[i].r;
	double l, r, fr, fl, fmid , mid;
	int j;
	for (int i = 1; i <= cnt; ++i) {
		l = xl[i], r = xr[i];
		for (j = i + 1; j <= cnt; ++j) {
			if (xl[j] > r) break;
			r = max(xr[j], r);
		}
		st = i, ed = j - 1, i = j - 1;
		mid = (l + r) / 2;
		fl = getf(l), fr = getf(r), fmid = getf(mid);
	//	printf("fl = %lf, fr = %lf, fmid = %lf\n", fl, fr, fmid);
		ans += simpson(l , mid, r, fl, fmid, fr, calc(r - l, fl, fmid, fr));
	}
}
int main () {
	R(n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].r);
	}
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (getdis(a[i], a[j]) <= a[j].r - a[i].r) {
				useless[i] = 1; break;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (!useless[i]) b[++cnt] = a[i];
	}
	sort(b + 1, b + 1 + cnt, cmp1);
	solve();
	printf("%0.3lf\n", ans);
}
