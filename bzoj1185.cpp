
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
	if (p) v = -v;
}
int n;
struct point {
	double x, y;
	point(double x, double y) : x(x), y(y) {
	}
	point() {}
} p[50005], s[50005], ans[10];
int tot;
const double eps = 1e-9;
inline double operator *(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}

inline point operator -(const point &a, const point &b) {
	return point (a.x - b.x, a.y - b.y);
}
inline point operator +(const point &a, const point &b) {
	return point (a.x + b.x, a.y + b.y);
}
inline double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}
inline bool cmp(const point &a, const point &b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
inline bool cmp1(const point &a, const point &b) {
	return a.y < b.y || (a.y == b.y && a.x < b.x);
}
inline void tubao () {
	//233
	for (int i = 1; i <= n; ++i) {
		while (tot > 1 &&  (s[tot] - s[tot - 1]) * (p[i] - s[tot - 1]) <= 0) --tot;
		s[++tot] = p[i];
	}
	int k = tot;
	for (int i = n - 1; i; --i) {
		while (tot > k && (s[tot] - s[tot - 1]) * (p[i] - s[tot - 1]) <= 0) --tot;
		s[++tot] = p[i];
	}
	if (n > 1) tot--;
}
inline point operator *(const point &a, double b) {
	return point(a.x * b , a.y * b);
}
inline double getlen(const point &a) {
	return sqrt(a.x * a.x + a.y * a.y);
}
double ret;
const double inf = 2140000000;

inline void RC() {
	int p = 2, q = 2, r = 2;
	ret = inf;
	point a;
	double len;
	s[tot + 1] = s[1];
	double r1, l1;
	double length, height;
	for (int i = 1; i < tot; ++i) {
		a = s[i + 1] - s[i];
		len = getlen(a);
		while (dot(a, s[p] - s[i]) <= dot(a, s[p + 1] - s[i])) {++p; if (p == tot + 1) p = 1;}
		while (a * (s[r] - s[i]) <= a * (s[r + 1] - s[i]) ) {++r; if (r == tot + 1) r = 1;}
		if (i == 1) q = r;
		while (dot(a, s[q] - s[i]) >= dot(a, s[q + 1] - s[i])) {++q; if (q == tot + 1) q = 1;}
		//	cerr << "p=" << p << " q=" << q << " r=" << r << '\n';
		r1 = dot(a, s[p] - s[i]) / len;
		l1 = fabs(dot(a, s[q] - s[i]) / len);
		length = r1 + l1;
		height = fabs(a * (s[r] - s[i]) / len);
		//cerr << "length=" << length << " height =" << height << '\n';
		if (length * height < ret) {
			ret = length * height;
			ans[0] = s[i] + (s[i + 1] - s[i]) * (r1 / len);
			ans[1] = ans[0] + (s[p] - ans[0]) * (height / getlen(s[p] - ans[0]));
			ans[2] = ans[1] + (s[r] - ans[1]) * (length / getlen(s[r] - ans[1]));
			ans[3] = ans[2] + (s[q] - ans[2]) * (height / getlen(s[q] - ans[2]));
		}
	}
}
int main() {
	//freopen("in.in", "r", stdin);
	R(n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf", &p[i].x, &p[i].y);
	}

	sort(p + 1, p + n + 1, cmp);
//	for (int i = 1; i <= n; ++i) {
//		printf("%lf %lf\n", p[i].x, p[i].y );
//	}
	tubao();
	//cerr << "tot=" << tot << '\n';
	//for (int i = 1; i <= tot; ++i) {
	//	printf("%lf %lf\n", s[i].x, s[i].y );
	//}
	RC();
	printf("%0.5lf\n", ret + eps);
	int pre = 0;
	for (int i = 1; i <= 3; i++)
	{
		if (ans[i].y < ans[pre].y)pre = i;
		else if (fabs(ans[i].y - ans[pre].y) < eps && ans[i].x < ans[pre].x)pre = i;
	}
	for (int i = 0; i < 4; ++i) {
		printf("%0.5lf %0.5lf\n", ans[(pre+i)%4].x + eps, ans[(pre+i)%4].y + eps );
	}
}
