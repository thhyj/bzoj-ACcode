
#include <bits/stdc++.h>
using namespace std;
int n;
struct circle {
	long long x, y, r;
} cir[100005];
double l, r;
inline bool check(const circle &a, const circle &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) < (a.r + b.r) * (a.r + b.r);
}
int main() {
	l = -INT_MAX;
	r = INT_MAX;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld %lld %lld", &cir[i].x, &cir[i].y, &cir[i].r);
//		printf("%lld %lld %lld", cir[i].x, cir[i].y, cir[i].r);
	}
	double mid;
	int posl, posr;
	double l1, r1, shang, xia;
	for (int i = 1; i <= 40; ++i) {
		mid = (l + r) / 2;
		l1 = -INT_MAX, r1 = -l1;
		for (int i = 1; i <= n; ++i) {
			if (fabs(mid - cir[i].x) >= cir[i].r) {
				if (cir[i].x > mid) {
					l = mid;
					goto end;
				} else {r = mid; goto end;}
			}
			shang = sqrt(cir[i].r * cir[i].r - fabs(mid - cir[i].x) * fabs(mid - cir[i].x)) + cir[i].y;
			xia = cir[i].y - (shang - cir[i].y);
			if (shang <= l1) {
				if (!check(cir[posl], cir[i])) {
					puts("NO");
					return 0;
				}
			}
			if (xia >= r1) {
				if (!check(cir[posr], cir[i])) {
					puts("NO");
					return 0;
				}
			}
			if(shang < r1) {
				r1 = shang;
				posr = i;
			}
			if(xia > l1) {
				l1 = xia;
				posl = i;
			}
		}
		puts("YES");
		return 0;
end: continue;
	}
	puts("NO");
}
