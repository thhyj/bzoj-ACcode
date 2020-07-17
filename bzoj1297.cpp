
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
const int mod = 2009;
int n;
struct matrix {
	int a[90][91];
	inline matrix operator *(matrix &b) {
		matrix temp;
		memset(temp.a, 0, sizeof(temp.a));
		int t;
		for (register int i = 0; i < n; i++) {
			for (register int k = 0; k < n; k++) {
				if (a[i][k]) {
					int *p2 = b.a[k], *p1 = temp.a[i], tmp = a[i][k], *r = p1 + n;
					r -= 15;
					for (; p1 < r; p1 += 16, p2 += 16) {
						*p1 += tmp * (*p2);
						*(p1 + 1) += tmp * ( * (p2 + 1));
						*(p1 + 2) += tmp * ( * (p2 + 2));
						*(p1 + 3) += tmp * ( * (p2 + 3));
						*(p1 + 4) += tmp * ( * (p2 + 4));
						*(p1 + 5) += tmp * ( * (p2 + 5));
						*(p1 + 6) += tmp * ( * (p2 + 6));
						*(p1 + 7) += tmp * ( * (p2 + 7));
						*(p1 + 8) += tmp * ( * (p2 + 8));
						*(p1 + 9) += tmp * ( * (p2 + 9));
						*(p1 + 10) += tmp * (* (p2 + 10));
						*(p1 + 11) += tmp * (* (p2 + 11));
						*(p1 + 12) += tmp * (* (p2 + 12));
						*(p1 + 13) += tmp * (* (p2 + 13));
						*(p1 + 14) += tmp * (* (p2 + 14));
						*(p1 + 15) += tmp * (* (p2 + 15));
					}
					r += 15;
					while (p1 < r) {
						*p1 += tmp * (*p2);
						++p1, ++p2;
					}
				}
			}
		}
		int *p1;
		for (int i = 0; i < n; ++i) {
			p1 = temp.a[i];
			for (int j = 0; j < n; ++j) {
				p1[j] %= mod;
				//printf("temp.a[%d][%d] = %d\n", i, j, temp.a[i][j]);
			}
		}
		return temp;
	}
} ma;
inline matrix ksm(matrix a, int k) {
	matrix temp;
	memset(temp.a, 0 , sizeof(temp.a));
	for (int i = 0 ; i < n ; ++i) {
		temp.a[i][i] = 1;
	}
	while (k) {
		if (k & 1) temp = temp * a;
		a = a * a; k >>= 1;
	}
	printf("%d", temp.a[8][n - 1]);
}
int main () {
	//freopen("in.in", "r", stdin);
	int t;
	R(n), R(t);
//  printf("n=%d,t=%d\n",n, t);
	int x;
	for (int i = 0; i < 9 * n; ++i) {
		ma.a[i][i + 1] = i % 9 != 8;
	}
	char s1[105];
	int *p1;
	int p = 0;
	for (int i = 0; i < n ; ++i) {
		fgets(s1, 100, stdin);
		p1 = ma.a[i*9+8];
		p=0;
		for (int j = 0; j < n; ++j,p+=9) {
			p1[p - s1[j] + 57] += s1[j] != '0';
		}
	}
	n *= 9;
	ksm(ma, t);
}
