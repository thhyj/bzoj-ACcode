
#include <bits/stdc++.h>
using namespace std;
inline char read() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    if (s == t) {
        t = (s = buf) + fread(buf, 1, IN_LEN, stdin);
        if (s == t) return -1;
    }
    return *s++;
}

template<class T>
inline void R(T &x) {
    static char c;
    static bool iosig;
    for (iosig = false, c = read(); !isdigit(c); c = read()) {
        if (c == -1) return;
        if (c == '-') iosig = true;
    }
    for (x = 0; isdigit(c); c = read())
        x = (x + (x << 2) << 1) + (c ^ '0');
    if (iosig) x = -x;
}

int n;
int a;
int qz[100005];
const int maxn = (1 << 21) + 2;
#define lowbit(x) (x&-x)
int sum1[maxn + 5];
int sum0[maxn + 5];
int ans[21];
int t;
inline int query1(int x) {
	int ret = 0;
	for (int i = x; i; i -= lowbit(i)) {
		ret += sum1[i];
	}
	return ret;
}
inline int query0(int x) {
	int ret = 0;
	for (int i = x; i; i -= lowbit(i)) {
		ret += sum0[i];
	}
	return ret;
}
inline void add1(int x) {
	for (int i = x; i <= t + 1; i += lowbit(i)) {
		sum1[i] += 1;
	}
}
inline void add0(int x) {
	for (int i = x; i <= t + 1 ; i += lowbit(i)) {
		sum0[i] += 1;
	}
}
int main () {
//	freopen("sum.in", "r", stdin);
//	freopen("sum.out", "w", stdout);
	R(n);
	for (int i = 1; i <= n; ++i) {
		R(a);
		qz[i] = qz[i - 1] + a;
	}
	int temp;
	for (int j = 0;(1<<j)<=qz[n]; ++j) {
		t = 1 << j;
		memset(sum1,0, (t<<2) + 5);
		memset(sum0,0, (t<<2) + 5);
		for (int i = 0 ; i <= n; ++i) {
			//	printf("qz[%d]=%d\n", i, qz[i]);
			//	for (int k = 1; k <= 10; ++k) {
			//	printf("query0(%d)=%d, query1(%d)=%d\n", k, query0(k), k, query1(k) );
			//	}
			if ((qz[i] & t) ^ 0) {						// sum i鐨勮繖涓€浣嶄负1
				temp = qz[i] % t;
				ans[j] = (ans[j] + query0(temp + 1)) ;
				ans[j] = (ans[j] + query1(t) - query1(temp + 1)) ;
				add1(temp + 1);
			} else {
				temp = qz[i] % t;
				ans[j] = (ans[j] + query1(temp + 1)) ;
				ans[j] = (ans[j] + query0(t) - query0(temp + 1)) ;
				add0(temp + 1);
			}
		}
	}
	int ret = 0;
	for (int i = 0; i <= 20; ++i) {
		if (ans[i] & 1) {
			//	cout << "i=" << i << '\n';
			ret += (1 << i);
		}
	}
	printf("%d",ret);
	return 0;
}
