
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#define maxn 500010
#define maxm 500010

using namespace std;

int head[maxn], to[maxm], nxt[maxm], a[maxm], b[maxn];
int n, m, T, ans, num, k;
bool vis[maxn];
int c[40], o[40];

void addedge(int x, int y)
{
	num++; to[num] = y; nxt[num] = head[x]; head[x] = num;
}

void dfs1(int x)
{
	vis[x] = 1;
	for (int p = head[x]; p; p = nxt[p])
		if (!vis[to[p]]) dfs1(to[p]);
		else
		{
			a[p] = rand();
			b[x] ^= a[p]; b[to[p]] ^= a[p];
		}
}

void dfs2(int x)
{
	vis[x] = 1;
	for (int p = head[x]; p; p = nxt[p])
		if (!vis[to[p]])
		{
			dfs2(to[p]);
			a[p] ^= b[to[p]];
			b[x] ^= b[to[p]];
		}
}

bool check()
{
	/*int now = 0;
	for (int i = 1 << 30; i; i >>= 1)
	{
		int j = now + 1;
		for (; j <= k; j++) if (c[j]&i) break;
		if (j == k + 1) continue;
		swap(c[j], c[++now]);
		for (int j = 1; j <= k; j++)
			if (j != now && c[j]&i) c[j] ^= c[now];
	}
	if (c[k]) return 0; else return 1;*/
	memset(o, 0 , sizeof(o));
	for (int i = 1; i <= k; ++i) {
		for (int j = 30; j >= 0; j--) {
			if ((c[i] & (1 << j)) == 0) continue;
			if (o[j]) c[i] ^= o[j];
			else {
				for (int k = 0; k < j; ++k) {
					if (c[i] & (1 << k)) c[i] ^= o[k];
				}
				for (int k = j + 1; k <= 30; ++k) {
					if (o[k] & (1 << j)) o[k] ^= c[i];
				}
				o[j] = c[i];
				goto end;
			}
		}
		return 1;
end: continue;
	}
	return 0;
}

int main()
{
	srand('gou' + 'li' + 'guo' + 'sheng' + 'si' + 'yi' + 'qi' + 'yin' + 'huo' + 'fu' + 'bi' + 'qu' + 'zhi');
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if (x > y) swap(x, y);
		addedge(x, y);
	}
	dfs1(1);
	memset(vis, 0, sizeof(vis));
	dfs2(1);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &k);
		for (int i = 1; i <= k; i++)
		{
			int x;
			scanf("%d", &x);
			c[i] = a[x];
		}
		if (check()) printf("Disconnected\n");
		else {ans++; printf("Connected\n");}
	}
	return 0;
}
