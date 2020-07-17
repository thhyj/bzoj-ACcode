
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
	}	if (p) v = -v;
}
int n, m;
int a[50005], sum[50005], c[50005], tot, tong, cnt;
int block;
struct query {
	int l, r, id, belong;
} q[50005];
inline bool cmp(const query&a, const query&b) {
	return (a.belong < b.belong || (a.belong == b.belong) && a.r < b.r);
}
pair<int, int>ans[50005];
int main () {
//	freopen("in.in","r",stdin);
	R(n), R(m);
	for (int i = 1; i <= n ; ++i) {
		R(a[i]);
	}
	block = sqrt(n);
	for (int i = 1; i <= m; ++i) {
		R(q[i].l), R(q[i].r); q[i].id = i;
		q[i].belong = q[i].l / block;
	}
	sort(q + 1, q + m + 1, cmp);
	int l = 1, r = 0;
//	for (int i = 1; i <= m ; ++i) {
//		printf("q[%d].l = %d, q[%d].r = %d\n", i, q[i].l, i, q[i].r);
//	}
	for (int i = 1; i <= m; ++i) {
		while (r < q[i].r) {
			++r;
			++tot;
			cnt += (tot - 1);
			c[a[r]]++;
			tong += c[a[r]] - 1;
		}
		while (r > q[i].r) {
			c[a[r]]--;
			--tot;
			cnt -= tot;
			tong -= c[a[r]];
			--r;
		}
		while (l < q[i].l) {
			c[a[l]]--;
			--tot;
			cnt -= tot;
			tong -= c[a[l]];
			++l;
		}
		while (l > q[i].l) {
			--l;
			++tot;
			cnt += (tot - 1);
			c[a[l]]++;
			tong += c[a[l]] - 1;
		}
		ans[q[i].id] = make_pair(tong, cnt);
	}
	int GCD; 
	for (int i = 1; i <= m; ++i) {
		GCD = __gcd(ans[i].first, ans[i].second);
		printf("%d/%d\n", ans[i].first/GCD, ans[i].second/GCD );
	}
	return 0;
}
