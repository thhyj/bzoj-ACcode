
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
using namespace std;
int to[N], nxt[N], pre[N], cnt;
void ae(int ff, int tt)
{
	cnt++;
	to[cnt] = tt;
	nxt[cnt] = pre[ff];
	pre[ff] = cnt;
}
int fa[N];
int n, S, K;
long long que[N][21], duo[N][21];
int ans;
void build(int x)
{
	int i, j, k;
	que[x][0] = 1;
	for (i = pre[x]; i; i = nxt[i])
	{
		j = to[i];
		if (j == fa[x]) continue;
		fa[j] = x;
		build(j);
		for (k = 0; k < K; k++)
			que[x][k + 1] += que[j][k];
		for (k = K; k > 0; k--)
			duo[x][k - 1] += duo[j][k];
	}
	k = (que[x][K] + S - 1) / S;
	ans += k;
	duo[x][K] += k * S;
	for (j = 0; j <= K; j++)
		if (duo[x][j])
		{
			for (k = j; k >= 0 && (k >= j - 1 || x == 1); k--)
			{
				if (duo[x][j] <= que[x][k])
				{
					que[x][k] -= duo[x][j];
					duo[x][j] = 0;
					break;
				}
				duo[x][j] -= que[x][k];
				que[x][k] = 0;
			}
		}
}
int main()
{
	scanf("%d%d%d", &n, &S, &K);
	int i, j, x, y;
	for (i = 1; i < n; i++)
	{
		scanf("%d%d", &x, &y);
		ae(x, y); ae(y, x);
	}
	build(1);
	int tot = 0;
	for (i = 0; i <= K; i++)
		tot += que[1][i];
	ans += (tot + S - 1) / S;
	printf("%d", ans);
}
