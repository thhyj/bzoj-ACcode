
#include <bits/stdc++.h>
using namespace std;
string s1, s2;
int n;
int sa[60005], rk[60005], height[60005], c[60005];
char s[60005];
inline void R(char &ch) {
	do {
		ch = getchar();
	} while (!isupper(ch));
}
inline void getsa(int m) {
	int i , j, k, *x = rk, *y = height;
	for (i = 0; i < n; ++i) c[x[i] = s1[i]]++;
	for (i = 1; i < m; ++i) c[i] += c[i - 1];
	for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
	for (k = 1; k < n; k <<= 1) {
		j = 0;
		for (i = n - k; i < n; ++i)y[j++] = i;
		for (i = 0; i < n; ++i) if (sa[i] >= k)y[j++] = sa[i] - k;
		for (i = 0; i < m; ++i)c[i] = 0;
		for (i = 0; i < n; ++i) c[x[y[i]]]++;
		for (i = 1; i < m; ++i) c[i] += c[i - 1];
		for (i = n - 1; i >= 0; --i) {
			//	printf("c[%d]=%d\n", x[y[i]], c[x[y[i]]]);
			sa[--c[x[y[i]]]] = y[i];
		}
		swap(x, y);
		x[sa[0]] = j = 1;
		for (i = 1; i < n; ++i) {
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? j : ++j;
		}
		if (j == n) break;
		m = j + 1;
	}
	for (i = 0; i < n; ++i) rk[sa[i]] = i;
}
int main() {
	int n1;
	scanf("%d", &n1);
	//printf("n1=%d\n", n1);
	for (int i = 0; i < n1 ; ++i) {
		R(s[i]);
	}
	s1 = s;
	s2 = s1;
	reverse(s2.begin(), s2.end());
	s1 += 127;
	s1 += s2;
	n = s1.length();
//	cout << "s1=" << s1 << '\n';
	getsa(128);
//	for (int i = 0; i < n; ++i) {
//		printf("rk[%d]=%d\n", i, rk[i]);
	//}
	int l = 0, r = n1 + 1, cnt = 0;
	memset(s, 0, sizeof(s));
	while (cnt < n1) {
		if (rk[l] < rk[r]) {
			s[++cnt] = s1[l++];
		} else s[++cnt] = s1[r++];
		putchar(s[cnt]);
		if (cnt % 80 == 0)putchar('\n');
	}
	return 0;
}
