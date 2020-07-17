
#include <bits/stdc++.h>
using namespace std;
inline void R (long long &v) {
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
struct edge {
	long long fr, to, w;
	edge(long long fr, long long to , long long w): fr(fr), to(to), w(w) {}
	edge() {}
} bian[300005];
long long n, m;
long long a[100005], b[100005], fa[100005], v[100005];
inline bool operator < (const edge &a,  const edge &b) {
	return a.w < b.w ;
}
inline long long getfather(long long x) {
	return x == fa[x] ? x : (fa[x] = getfather(fa[x]));
}
int main () {
//	freopen("dumpling.in","r",stdin); 
	R(n), R(m);
	for (long long i = 1; i <= n; ++i) {
		R(a[i]), R(b[i]);
		v[i] = a[i] * b[i];
		fa[i] = i;
	}
	long long x, y, z;
	for (long long i = 1; i <= m; ++i) {
		R(x), R(y), R(z);
		bian[i] = edge(x, y, z);
	}
	sort(bian + 1, bian + m + 1);
	long long cnt = 0, fx, fy;
	for (long long i = 1 ; i <= m; ++i) {
		fx = getfather(bian[i].fr), fy = getfather(bian[i].to);
		if (fx != fy) {
			fa[fx] = fy;
			a[fy] = max(max(a[fy], a[fx]), bian[i].w);
			b[fy] = min(b[fy], b[fx]);
			v[fy] = min(v[fx] + v[fy], a[fy] * b[fy]);
			++cnt;
		}
		if(cnt == n - 1) break;
	}
	long long ans = 0;
	for (register int i = 1; i <= n; i++) fa[i] == i ? ans += v[i] : 0;
	cout<<ans;
	return 0;
}
