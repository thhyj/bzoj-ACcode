
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
		v = (v + (v << 2) << 1) + (ch ^ '0');
		ch = getchar();
	}
	if (p) v = -v;
}
const int N = 100005;
struct yueshu {
	int s, i;
} ys[N + 50];
inline bool cmp(const yueshu &a, const yueshu &b) {
	return a.s < b.s;
}
int ans[100055];
struct wenti {
	int n, m, a, id;
} q[N + 50];
int miu[N + 50], prime[N + 50];
bool heshu[N + 50];
int cnt;
inline void init() {
	miu[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!heshu[i]) prime[++cnt] = i, miu[i] = -1;
		for (int j = 1; j <= cnt && prime[j] * i <= N; ++j) {
			heshu[i * prime[j]] = 1;
			if ( i % prime[j] == 0) {
				miu[i * prime[j]] = 0;
				break;
			} else {
				miu[i * prime[j]] = -miu[i];
			}
		}
	}
	for (int i = 1; i <= N; ++i) {
		ys[i].i = i;
		for (int j = i ; j <= N; j += i) {
			ys[j].s += i;
		}
	}
}
inline bool cmp1(const wenti &a, const wenti &b) {
	return a.a < b.a;
}
int sum[100055];
#define lowbit(x) (x&-x)
inline void add(int x, int y) {
	for (int i = x; i <= N; i += lowbit(i)) {
		sum[i] += y;
	}
}
inline int query(int x) {
	int ret = 0;
	for (int i = x; i; i -= lowbit(i)) {
		ret += sum[i];
	}
	return ret;
}
inline void ins(int x) {
	for (int i = 1; i * ys[x].i <= N; ++i) {
		add(ys[x].i * i, ys[x].s * miu[i]);
	}
}
inline int calc(int n, int m) {
	if (n > m) swap(n, m);
	int j, ret = 0;
	for (int i = 1;  i <= n; i = j + 1 ) {
		j = min(n / (n / i), m / (m / i));
		ret += (query(j) - query(i - 1)) * (n / i) * (m / i);
	}
	return ret;
}
int main () {
	init();
	sort(ys + 1, ys + N, cmp);
	int T;
	R(T);
	for (int i = 1; i <= T; ++i) {
		R(q[i].n), R(q[i].m), R(q[i].a);
		q[i].id = i;
	}
	sort(q + 1, q + T + 1, cmp1);
	int now = 0;
	for (int i = 1; i <= T; ++i) {
		while (ys[now + 1].s <= q[i].a) {
			ins(++now);
//			cout<<"now = "<<now<<'\n';
		}
		ans[q[i].id] = calc(q[i].n, q[i].m);
	}
	for(int i = 1; i <= T; ++i) {
		printf("%d\n", ans[i] & 0x7FFFFFFF);
	}
}
