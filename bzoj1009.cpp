
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
char s1[25];
int nxt[25];
int mod;
struct matrix {
	long long a[25][25];
	inline matrix operator *(const matrix &b) {
		matrix temp;
		memset(temp.a, 0, sizeof(temp.a));
		long long  tmp;
		for (int i = 0; i < 25 ; ++i) {
			for (int k = 0; k < 25; ++k) {
				tmp = a[i][k];
				for (int j = 0; j < 25; ++j) {
					temp.a[i][j] = (temp.a[i][j] + tmp * b.a[k][j]) % mod;
				}
			}
		}
		return temp;
	}
};
inline matrix ksm (matrix a, int k) {
	matrix ans;
	memset(ans.a, 0, sizeof(ans.a));
	for (int i = 0; i <= 24 ; ++i) {
		ans.a[i][i] = 1;
	}
//	for (int i = 0; i < 25; ++i)
//		for (int j = 0; j < 25; ++j ) {
//			printf("ans.a[%d][%d]=%d\n", i, j, ans.a[i][j]);
//		}
	while (k) {
		if (k & 1) ans = ans * a;
		a = a * a, k >>= 1;
	}
	return ans;
}
matrix a, b;
int main () {
	int n, m;
	R(n), R(m), R(mod);
	scanf("%s", s1);
	int j = 0;
	for (int i = 1; i < m; ++i) {
		while (j&&s1[i]^s1[j]) j = nxt[j - 1];
		if (s1[i] == s1[j]) ++j;
		nxt[i] = j;
	}
	for (int i = 0; i < m; ++i) {
		for (int k = 0; k <= 9 ; ++k) {
			j = i;
			while (j&&(s1[j] - '0') != k) j = nxt[j - 1];
			if (s1[j] - '0' == k) ++j;
			if (j != m)
				b.a[j][i] = (b.a[j][i] + 1) % mod;
		}
	}
	matrix temp = ksm(b, n);
	int ans = 0;
	for (int i = 0; i < m; ++i) {
		ans = (ans + temp.a[i][0]) % mod;
	}
	cout << ans;
	return 0;
}
