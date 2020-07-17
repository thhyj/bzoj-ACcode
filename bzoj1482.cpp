
#include<bits/stdc++.h>
int main() {
	puts("nan");/*#include <bits/stdc++.h>
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
struct point {
	double x, y;
	point (double x, double y): x(x), y(y) {}
	point() {}
};
struct circle {
	double r;
	point q;
	circle(double r, point q): r(r), q(q) {}
	circle() {}
} p[1005];
inline double getdis(const point &a, const point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
bool vis[1005];
typedef pair<double, double> pdd;
std::vector<pdd> que[1005];
inline bool cmp( const pdd &a, const pdd &b) {
	return a.first < b.first || (a.first == b.first && a.second < b.second);
}
const double pi = acos(-1);
const double eps = -1e9;
int main() {
	freopen("in.in", "r", stdin);
	int n;
	R(n);
	double dis;
	double coszhi, alpha, k;
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf%lf", &p[i].r, &p[i].q.x, &p[i].q.y);
		for (int j = 1; j < i ; ++j) {
			if (!vis[j]) {
				dis = getdis(p[j].q, p[i].q);
				if (p[j].r + dis <= p[i].r) {vis[j] = 1; continue;}
				if (p[i].r + dis <= p[j].r) continue;
				if (p[i].r + p[j].r <= dis) continue;
				//if (p[j].r < eps || dis < eps)continue;
				//		printf("dis = %lf\n", dis);
				alpha = acos((p[j].r * p[j].r + dis * dis - p[i].r * p[i].r) / (p[j].r * dis * 2));
				//		printf("alpha = %lf\n", alpha);
				k = atan2(p[i].q.y - p[j].q.y, p[i].q.x - p[j].q.x);
				//		printf("%lf\n",p[i].q.x - p[j].q.x);
				//		printf("k = %lf\n", k);
				if ((k + alpha) > pi) {
					que[j].push_back((pdd) {k - alpha, pi});
					que[j].push_back((pdd) { -pi, k + alpha - 2 * pi}); continue;
				}
				if ((k - alpha) < -pi) {
					que[j].push_back((pdd) {k - alpha + 2 * pi, pi});
					que[j].push_back((pdd) { -pi, k + alpha}); continue;
				}
				que[j].push_back((pdd) {k - alpha, k + alpha});
			}
		}
	}
	double ans = 0;
	double ret;
	double st;
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		ret = 0;
		sort(que[i].begin(), que[i].end(), cmp);
		st = -pi;
		for (int j = 0; j < que[i].size(); ++j) {
			while ((que[i][j].first == que[i][j + 1].first) && j < que[i].size() - 1) ++j;
			//if (que[i][j].first < st) continue;
			//	printf("que[%d][%d].first = %lf, que[%d][%d].second = %lf\n", i,j,que[i][j].first, i, j, que[i][j].second);
			ret += ((que[i][j].second - max(que[i][j].first, st)) > 0) ? ((que[i][j].second - max(que[i][j].first, st))) : 0;
			st = max(que[i][j].second, st);
		}
		ret = pi * 2 - ret;
		ans += ret * p[i].r;
		//	st = -pi;
		//	for (int j = 0; j < que[i].size(); ++j) {
		//		if (st < que[i][j].first)ans += (que[i][j].first - st) * p[i].r;
		//		st = max(st, que[i][j].second);
		//	}
		//	if (st < pi)ans += (pi - st) * p[i].r;
	}
	printf("%0.3lf", ans);
	return 0;
}
*/
}
