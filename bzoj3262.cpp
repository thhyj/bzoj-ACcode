
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#define inf 0x7fffffff
#define ll long long
using namespace std;
inline void R(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-')
			p = 1;
	} while ( !isdigit(ch) );
	while ( isdigit(ch) ) {
		v = ( v << 1 ) + ( v << 3 ) + ( ch ^ '0' );
		ch = getchar();
	}
	if (p)
		v = -v;
}
int n, m, t[200005], ans[100005], N;
struct data {
	int a, b, c, s, ans;
} a[100005], p[100005], temp[100005];
inline bool cmp(data a, data b) {
	if (a.a == b.a && a.b == b.b) return a.c < b.c;
	if (a.a == b.a) return a.b < b.b;
	return a.a < b.a;
}
inline bool operator < (data a, data b) {
	if (a.b == b.b) {
		if (a.c == b.c)	return a.a < b.a;
		return a.c < b.c;
	}
	return a.b < b.b;
}
inline int lowbit(int x) {
	return x & ( -x );
}
inline void update(int x, int num) {
	for ( int i = x; i <= m; i += lowbit(i) )
		t[i] += num;
}
inline int ask(int x) {
	int tmp = 0;
	for ( int i = x; i; i -= lowbit(i) )
		tmp += t[i];
	return tmp;
}
void solve(int l, int r) {
	if (l == r) {p[l].ans += p[l].s - 1; return;}
	//printf("l = %d, r = %d\n", l, r);
	//for (int i = l; i <= r; ++i) {
//		printf("p[%d].a = %d, p[%d].b = %d, p[%d].c = %d, p[%d].s = %d\n", i, p[i].a, i, p[i].b, i, p[i].c, i, p[i].s);
	//}
	int mid = ( l + r ) >> 1;
	int l1 = l, l2 = mid + 1;
	for (int i = l; i <= r; ++i) {
		if (p[i].a <= mid) temp[l1++] = p[i];
		else temp[l2++] = p[i];
	}
	for (int i = l; i <= r; ++i) {
		p[i] = temp[i];
	}
	solve(l, mid);
	int j = mid + 1, i = l;
	while (j <= r) {
		while (i <= mid && p[i].b <= p[j].b) {
			update(p[i].c, p[i].s);
			i++;
		}
		p[j].ans += ask(p[j].c);
		j++;
	}
	for (int j = l; j < i; j++) update(p[j].c, -p[j].s);
	solve(mid + 1, r);
	//sort(p + l, p + r + 1);
	l1 = l, l2 = mid + 1;
	sort(p + l, p + r + 1);
	//for (int i = l; i <= r; ++i) p[i] = temp[i];
}
int main() {
	R(N);
	R(m);
	for (int i = 1; i <= N; i++)
		R(a[i].a), R(a[i].b), R(a[i].c);
	sort(a + 1, a + N + 1, cmp);
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		cnt++;
		if (a[i].a ^ a[i + 1].a || a[i].b ^ a[i + 1].b || a[i].c ^ a[i + 1].c) {
			p[++n] = a[i];
			p[n].s = cnt;
			cnt = 0;
		}
	}
	for (int i = 1; i <= n; ++i) p[i].a = i;
	sort(p + 1, p + n + 1);
	//for (int i = 1; i <= n; ++i) {
	//	printf("p[%d].a = %d, p[%d].b = %d, p[%d].c = %d, p[%d].s = %d\n", i, p[i].a, i, p[i].b, i, p[i].c, i, p[i].s);
	//}
	solve(1, n);
	for (int i = 1; i <= n; i++)
		ans[p[i].ans] += p[i].s;
	for (int i = 0; i < N; i++)
		cout << ans[i] << '\n';
	return 0;
}
