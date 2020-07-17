
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
int a[3000005], q[3000005], n, k, q1[3000005];
int main() {
//	freopen("in.in","r",stdin);
//	freopen("out.out","w",stdout);
	R(k), R(n);
	for (int i = 1; i <= n; ++i) {
		R(a[i]);
	}
	long long mid, l = 1, r = n + 1;
	while (l + 1 < r) {
		mid = l + r >> 1;
		//printf("mid = %d\n", mid) ;
		int head =  1, tail = 1, head1 = 1, tail1 = 1, min1, max1;
		bool pd = 0;
		memset(q, 0 , sizeof(q));
		memset(q1, 0, sizeof(q1));
		q[1] = 1; q1[1] = 1;
		for (int i = 2; i <= n; ++i) {
			while (head <= tail && i - q[head] >= mid) ++head;
			while (head <= tail && a[q[tail]] <= a[i])--tail;
			q[++tail] = i;
			max1 = a[q[head]];
			while (head1 <= tail1 && i - q1[head1] >= mid) ++head1;
			while (head1 <= tail1 && a[q1[tail1]] >= a[i])--tail1;
			q1[++tail1] = i;
			min1 = a[q1[head1]];
	//		printf("i=%d,max1=%d, min1=%d,head=%d, tail=%d\n",i,max1,min1,head,tail);
			if (max1 - min1 <= k && i >= mid) {pd = 1; break;}
		}
		if (pd) l = mid;
		else r = mid;
	}
	printf("%lld\n", l);
}
