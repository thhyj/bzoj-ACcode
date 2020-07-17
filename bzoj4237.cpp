
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
struct point {
	int x, y;
} p[200005],  temp[200005];
int n;
int topl, topr;
int stl[200005], str[200005];
inline bool cmp(const point &a, const point &b) {
	return a.x < b.x;
}
inline bool cmp1(const point &a, const point &b) {
	return a.y < b.y;
}
inline bool cmp2 (const int &a, const int &b) {
	return p[a].x < p[b].x;
}
long long ans;
int a[200005];
inline void solve(int l, int r) {
	if (l == r) {
		return;
	}
	int mid = l + r >> 1, l1 = l, l2 = mid + 1;
	for (int i = l; i <= r; ++i) {
		if (p[i].y <= mid)temp[l1++] = p[i];
		else temp[l2++] = p[i];
	}
	for (int i = l; i <= r; ++i) {
		p[i] = temp[i];
	}
	topl = 0; topr = 0;
	int t1;
	for (int i = mid + 1, j = l; i <= r; ++i) {
		while (j <= mid && p[j].x <= p[i].x) {
			while (topl && p[stl[topl]].y < p[j].y)--topl;
			stl[++topl] = j;
			++j;
		}
		while (topr && p[str[topr]].y > p[i].y) --topr;
		str[++topr] = i;
		t1 = upper_bound(stl + 1, stl + topl + 1, str[topr - 1], cmp2) - stl;
		ans += topl - t1 + 1;
	}
	solve(l, mid);
	solve(mid + 1, r);
}
int main() {
	R(n);
	static pair<int, int*> b[200005];
	for (int i = 1; i <= n; ++i) {
		R(p[i].x), R(p[i].y);
	}
	for (int i = 1; i <= n; i++)
		b[i] = make_pair(p[i].x, &p[i].x);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
		*b[i].second = i;

	for (int i = 1; i <= n; i++)
		b[i] = make_pair(p[i].y, &p[i].y);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
		*b[i].second = i;
	sort(p + 1, p + n + 1, cmp);
	solve(1, n);
	cout << ans;
}
