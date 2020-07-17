
#include <bits/stdc++.h>
using namespace std;
inline void R (int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-')p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p)v = -v;
}
inline void R (long long &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-')p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p)v = -v;
}
struct point {
	long long x, y;
	point(long long x, long long y) : x(x), y(y) {}
	point() {}
} p[100005];
inline bool operator < (const point &a, const point &b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
inline long long operator *(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
inline point operator -(const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}
int n;
set<point>U, D;
set<point>::iterator l, r, it;
long long ans;
inline void maintainU(point t) {
	it = U.lower_bound(t);
	if (it == U.begin()) {
		r = it; it++;
		while (it != U.end()) {
			if (((*r) - t) * ((*it) - t) < 0) break;
			ans += (*r) * (*it);
			U.erase(r); r = it; it++;
		}
		ans -=  t * (*r);
		U.insert(t);
	} else {
		if (it == U.end()) {
			it--; l = it;
			while (it != U.begin()) {
				it--;
				if (((*l) - (*it)) * (t - (*it)) < 0) break;
				ans += (*it) * (*l);
				U.erase(l); l = it;
			}
			ans -= (*l) * t;
			U.insert(t);
		} else {
			r = it; it--; l = it;
			if ((t - (*l)) * ((*r) - (*l)) < 0) {
				ans += (*l) * (*r);
				while (it != U.begin()) {
					it--;
					if (((*l) - (*it)) * (t - (*it)) < 0) break;
					ans += (*it) * (*l);
					U.erase(l); l = it;
				}
				ans -=  (*l) * t;
				it = r; it++;
				while (it != U.end()) {
					if (((*r) - t) * ((*it) - t) < 0) break;
					ans += (*r) * (*it);
					U.erase(r); r = it; it++;
				}
				ans -=  t * (*r);
				U.insert(t);
			}
		}
	}
}
inline void maintainD(point t) {
	it = D.lower_bound(t);
	if (it == D.begin()) {
		r = it; it++;
		while (it != D.end()) {
			if (((*r) - t) * ((*it) - t) > 0) break;
			ans -= (*r) * (*it);
			D.erase(r); r = it; it++;
		}
		ans +=  t * (*r);
		D.insert(t);
	} else {
		if (it == D.end()) {
			it--; l = it;
			while (it != D.begin()) {
				it--;
				if (((*l) - (*it)) * (t - (*it)) > 0) break;
				ans -= (*it) * (*l);
				D.erase(l); l = it;
			}
			ans += (*l) * t;
			D.insert(t);
		} else {
			r = it; it--; l = it;
			if ((t - (*l)) * ((*r) - (*l)) > 0) {
				ans -= (*l) * (*r);
				while (it != D.begin()) {
					it--;
					if (((*l) - (*it)) * (t - (*it)) > 0) break;
					ans -= (*it) * (*l);
					D.erase(l); l = it;
				}
				ans +=  (*l) * t;
				it = r; it++;
				while (it != D.end()) {
					if (((*r) - t) * ((*it) - t) > 0) break;
					ans -= (*r) * (*it);
					D.erase(r); r = it; it++;
				}
				ans +=  t * (*r);
				D.insert(t);
			}
		}
	}
}
int main () {
	R(p[1].x), R(p[1].y),
	R(p[2].x), R(p[2].y),
	R(p[3].x), R(p[3].y);
	sort(p + 1, p + 4);
	long long area;
	U.insert(p[1]), U.insert(p[3]);
	D.insert(p[1]), D.insert(p[3]);
	area = (p[2] - p[1]) * (p[3] - p[1]);
	if (area < 0) U.insert(p[2]), ans -= area;
	if (area > 0) D.insert(p[2]), ans += area;
	R(n);
	point t;
	while (n--) {
		R(t.x), R(t.y);
		maintainU(t);
		maintainD(t);
		printf("%lld\n", ans);
	}
	return 0;
}
