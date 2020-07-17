
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-7;

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
struct P {
	double slop;
	int x, y, z;
	P(int x, int y, int z, double slop): x(x), y(y), z(z) , slop(slop) {}
	P() {}
} p[200005], b[400005];
int x, y, X, Y;
int tot;
int centre, area, online;
int cnt;
int s[400005];
inline int operator * (const P &a, const P &b) {
	return a.x * b.y - a.y * b.x;
}
inline bool cmp(const P &a, const P &b) {
	return a.slop < b.slop;
}

int main () {
	int n;
	R(n);
	R(X), R(Y);
	for (int i = 2; i <= n; ++i) {
		R(x), R(y);
		if (x == X && y == Y) {centre++; continue;}
		p[++tot] = 	P(x - X, y - Y, 1, atan2(y - Y, x - X));
		p[++tot] =  P(X - x, Y - y, 0, atan2(Y - y, X - x));
	}
	if (!tot) {
		printf("%d %d", 1, centre + 1);
		return 0;
	}
	sort(p + 1, p + tot + 1, cmp);
//	for (int i = 1; i <= tot; i++) {
//		printf("p[%d].x = %d, p[%d].y = %d, p[%d].slop =%f, p[%d].z = %d\n", i, p[i].x, i, p[i].y, i, p[i].slop, i, p[i].z );
//	}
	int sum = 0;
	int i, j;
	for (i = 1; i <= tot; i = j) {
		sum = 0;
		for (j = i; j <= tot && fabs(p[i].slop - p[j].slop) < eps; ++j) sum += p[j].z;
		b[++cnt] = p[i];
		b[cnt].z = sum;
	}
//	cout << "cnt=" << cnt << '\n';
	for (i = 1; i <= cnt; ++i) b[i + cnt] = b[i];
	for (i = 1; i <= cnt + cnt; ++i) s[i] = s[i - 1] + b[i].z;
//	for (i = 1; i <= cnt + cnt; ++i) {
//		printf("s[%d]=%d\n", i, s[i] );
	//}
	//for (i = 1; i <= cnt + cnt; i++) {
///		printf("p[%d].x = %d, p[%d].y = %d, p[%d].slop =%f, p[%d].z = %d\n", i, b[i].x, i, b[i].y, i, b[i].slop, i, b[i].z );
	//}
	int maxans = 1000000000, minans = 0;
	for (i = j = 1; i <= cnt; ++i) {
		if (j < i) j = i;
		if (b[i].x < 0 || b[i].y > 0)continue;
		while (j + 1 < i + cnt && b[i]*b[j + 1] >= 0) ++j;
	//	cout << "i=" << i << " j=" << j << '\n';
		area = s[j] - s[i - 1];
		online = b[i].z;
		if (i < j && b[i] * b[j] == 0) online += b[j].z;
		area -= online;
		online += centre;
		maxans = min(area + 1, maxans);
		minans = max(area + online + 1, minans);
	}
	cout << maxans << ' ' << minans;
	return 0;
}
