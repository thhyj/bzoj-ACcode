
#include<bits/stdc++.h>
const int N = 30050;
const int P = 1e9 + 9;
int n, f[2][N], m[N];
char ch[N];
int main() {
	scanf("%d", &n);
	scanf("%s", ch + 1);
	if (n & 1 || ch[1] == ')') {printf("0\n"); return 0;}
	for (register int i = n - 1; i > 0; i--)
		m[i] = std::min(n - i, i);
	int now = 0, last = 1;
	f[1][1] = 1;
	for (register int i = 2; i <= n; i++, now ^= 1, last ^= 1) {
		if (f[last][0] > P) f[last][0] -= P;
		for (register int j = 1; j <= m[i] + 1; j++) {
			if (f[last][j] > P) f[last][j] -= P;
			f[now][j - 1] = f[last][j];
		}
		if (ch[i] == '(')
			for (int j = 0; j <= m[i]; j++)
				f[now][j + 1] += f[last][j];
	}
	printf("%d\n", f[last][0] % P);
	return 0;
}
