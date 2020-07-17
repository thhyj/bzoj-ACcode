
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
struct node {
	double x, y;
	node(double x, double y): x(x), y(y) {}
	node() {}
} p[10005], s[10005];
inline double dis(const node &x, const node &y) {
	return (x.x - y.x) * (x.x - y.x) * (x.y - y.y) * (x.y - y.y);
}
inline double operator * (const node &x, const node &y) {
	return x.x * y.y - x.y * y.x;
}
inline node operator - (const node &x, const node &y) {
	return node(x.x - y.x, x.y - y.y);
}
double t;
inline bool operator < (const node &x, const node &y) {
	t = (x - p[1]) * (y - p[1]);
	if (t == 0) return dis(x, p[1]) < dis(y, p[1]);
	return t < 0;
}
int n;
int x, y;
int top;
inline void graham() {
	int k = 1;
	for (int i = 2; i <= n; ++i) {
		if (p[k].y < p[i].y || (p[k].y == p[i].y) && p[k].x < p[i].x) k = i;
	}
	swap(p[1], p[k]);
	sort(p + 2, p + n + 1);
	s[++top] = p[1], s[++top] = p[2];
	for (int i = 3; i <= n; ++i) {
		while ((p[i] - s[top - 1]) * (s[top] - s[top - 1]) <= 0 && top > 1) --top;
		s[++top] = p[i];
	}
}
inline double getans() {
	s[top + 1] = p[1];
	double ans = 0;
	for (int x = 1; x <= top; ++x) {
		int a = x % top + 1, b = (x + 2) % top + 1;
		for (int y = x + 2; y <= top; ++y) {
			while (a % top + 1 != y && (s[y] - s[x]) * (s[a + 1] - s[x]) > (s[y] - s[x]) * (s[a] - s[x]))
				a = a % top + 1;
			while (b % top + 1 != x &&  (s[b + 1] - s[x]) * (s[y] - s[x]) > (s[b] - s[x]) * (s[y] - s[x]) )
				b = b % top + 1;
			ans = max((s[y] - s[x]) * (s[a] - s[x]) + (s[b] - s[x]) * (s[y] - s[x]), ans);
		}
	}
	return ans;
}
int main () {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);
	graham();
	printf("%0.3lf", getans() / 2);
}
