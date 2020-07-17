
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
inline void R(long long &v) {
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
bool p[75];
const long long mod = 1000000007;
long long dp[2][2][75][2];
inline long long dfs(int qq, int xz, int len, bool able) {
	if (dp[qq][xz][len][able]) {
		return dp[qq][xz][len][able];
	}
	if (!len) {
		return able;
	}
	int t = 1;
	if (xz) t = p[len];
	long long ret = 0;
	for (int i = 0; i <= t; ++i) {
		if (qq != 1 || i != 1)
		{
			//cout<<"i="<<i<<'\n';
			ret += dfs(i, xz && i == t, len - 1, able | i);
		}
	}
	dp[qq][xz][len][able] = ret;
	return ret;
}

struct matrix {
	int n, m;
	long long num[10][10];
	matrix(int a, int b) : n(a), m(b) {memset(num, 0, sizeof(num));}
};

matrix operator *(const matrix &a, const matrix &b)
{
	matrix ans(a.n, b.m);
	for (int i = 1; i <= ans.n; i ++)
		for (int j = 1; j <= ans.m; j ++)
			for (int k = 1; k <= a.m; k ++)
				ans.num[i][j] = (ans.num[i][j] + (long long)a.num[i][k] * b.num[k][j] % mod) % mod;
	return ans;
}

matrix ksm(matrix a, long long b)
{
	matrix ans(a.n, a.m);
	for (int i = 1; i <= ans.n; i ++)
		ans.num[i][i] = 1;
	while (b)
	{
		if (b & 1) ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}
long long work2(long long n)
{
	matrix fib(2, 2), ans(1, 2);
	fib.num[1][1] = 1; fib.num[1][2] = 1;
	fib.num[2][1] = 1; fib.num[2][2] = 0;
	ans.num[1][1] = 1; ans.num[1][2] = 1;
	return (ans * ksm(fib, n)).num[1][1];
}
int main () {
	int T;
	long long n;
	R(T);
	while (T--) {
		memset(dp, 0, sizeof(dp));
		memset(p, 0 ,sizeof(p));
		R(n);
		int len = 0;
		long long t = n;
		while (t) {
			//	cout << "t=" << t << '\n';
			p[++len] = t & 1;
			t >>= 1;
		}
		//reverse(p + 1, p + len + 1);
		//for (int i = 1; i <= len; ++i ) {
		//	cout << p[i];
		//}
		//	puts("");
		cout<<dfs(0, 1, len, 0)<<'\n'<<work2(n)<<'\n';
	}
}
