
#include <bits/stdc++.h>
using namespace std;
struct point {
	double x, y;
	point(double x, double y): x(x), y(y) {
	}
	point() {}
} p[10005];
int n;
inline bool operator <(const point &a, const point &b) {
	return a.x < b.x;
}
double ans, ansx;
inline double operator *(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
inline point operator - (const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}
inline bool check(const point &a) {
	for (int i = 1; i < n; ++i) {
		if ((p[i] - a) * (p[i + 1] - a) < 0) return 0;
	}
	return 1;
}
inline double calc(double x) {
	double l = 0, r = 1e11, mid;
	while (r - l > 1e-5) {
		mid = (l + r) / 2;
		if (check(point(x, mid))) r = mid;
		else l = mid;
	}
	int b1 = upper_bound(p + 1, p + n + 1, point(x, 0)) - p;
	double height = (p[b1].y - p[b1 - 1].y) * ((x - p[b1 - 1].x) / (p[b1].x - p[b1 - 1].x)) + p[b1 - 1].y;
	mid -= height;
	if (mid < ans) ans = mid, ansx = x;
	return mid;
}
inline double get() {
    return (rand() % 10000) / 10000.0;
}
inline void yewodamonituihuola() {
	double x = p[1].x, x1, now, nxt;
	ans = 1e11;
	now = calc(x);
//	cerr << "now=" << now << '\n';
	double de, T = 1e11;
	
	double mod = p[n].x - p[1].x;
	while (T > 0.0000001) {
		x1 = x + sin((double)rand())*T;
		if(x1 < p[1].x || x1>p[n].x){
		T*=0.999;
		continue;
	}
		nxt = calc(x1);
		de = now - nxt;
		if (de > 0 || (exp(de / T)*RAND_MAX > rand())) {
			x = x1, now = nxt;
			//	printf("de=%lf\n", de );
		}
		T *= 0.995;
	}
}

int main() {
	srand(19260817);
//	freopen("in.in", "r", stdin);
	//freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i].x;
	}
	for (int i = 1; i <= n; ++i) {
		cin >> p[i].y;
	}
	sort(p + 1, p + n + 1);
//	for (int i = 1; i <= n; ++i) {
//		printf("p[%d].x = %lf, p[%d].y = %lf\n", i, p[i].x, i, p[i].y );
//	}
	yewodamonituihuola();
	 std::cout << std::fixed << std::setprecision(3) << (double)ans;
}
