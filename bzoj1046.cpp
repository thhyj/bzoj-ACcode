
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

#define inf 1000000000
#define N 100007

using namespace std;
int n, m, cnt;
int a[N], f[N], best[N];
inline bool cmp(int a, int b) {
	return a > b;
}
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
void solve(int x)
{
	int last = 0;
	for (int i = 1; i <= n; i++)
		if (f[i] >= x && a[i] > last)
		{
			printf("%d", a[i]);
			if (x != 1)printf(" ");
			last = a[i]; x--;
			if (!x)break;
		} printf("\n");
}

int find(int x)
{
	for(int i = 1; i <= cnt; ++i) {
		printf("best[%d] = %d ", i, best[i]);
	}
	puts(" ");
	printf("x = %d\n", x);
	int l = 1, r = cnt, ans = 0;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (best[mid] > x) ans = mid, l = mid + 1;
		else r = mid - 1;
	} 
	printf("ans = %d\n", ans);
	return ans;
}
int find1(int x)
{
//	for(int i = 1; i <= cnt; ++i) {
//		printf("best[%d] = %d ", i, best[i]);
//	}
//	puts(" ");
//	printf("x = %d\n", x);
	int l = 0, r = cnt + 1, ans = 0;
	while (l < r - 1)
	{
		int mid = (l + r) >> 1;
		if (best[mid] > x) ans = mid, l = mid;
		else r = mid;
	} 
//	printf("l = %d\n", ans);
	return ans;
}
void dp()
{
	for (int i = n; i; i--)
	{
		
		int t = lower_bound(best + 1, best + cnt + 1, a[i], cmp) - best - 1;//
	//	find(a[i]);
		f[i] = t + 1; cnt = max(cnt, t + 1);
		if (best[t + 1] < a[i]) best[t + 1] = a[i];
	}
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	dp(); m = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read();
		if (x <= cnt)solve(x);
		else puts("Impossible");
	}
	return 0;
}
