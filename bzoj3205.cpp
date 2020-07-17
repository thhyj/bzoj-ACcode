
#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 1000000000
#define N 505
#define M 600005
using namespace std;

const int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
int cnt, n, m, tp, f[10][10][N][N], val[N * N], path[N][N][4], dfsclk, sum[M];
char mp[N][N]; bool bo[N][N];
struct node { int x, y; } h[M + 5], q[N * N + 5], gol[N][N][4], a[10];
node dfs(int x, int y, int k) {
	node t;
	if (path[x][y][k] == dfsclk) {
		t.x = 0; t.y = -1; return t;
	}
	path[x][y][k] = dfsclk;
	if (gol[x][y][k].y) return gol[x][y][k];
	int w = k;
	if (mp[x][y] == 'A') w = (k + 1) % 4;
	if (mp[x][y] == 'C') w = (k + 3) % 4;
	int u = x + dx[w], v = y + dy[w];
	if (u <= 0 || u > m || v <= 0 || v > n || mp[u][v] == 'x')
	{ t.x = x; t.y = y; return gol[x][y][k] = t; }
	else return gol[x][y][k] = dfs(u, v, w);
}
void spfa(int l, int r) {
	memset(sum, 0, sizeof(sum));
	memset(bo, 1, sizeof(bo)); int i, mn = inf, mx = -inf;
	for (i = 1; i <= tp; i++) {
		sum[val[i]]++;
		mn = min(mn, val[i]); mx = max(mx, val[i]);
		bo[q[i].x][q[i].y] = 0;
	}
	for (i = mn + 1; i <= mx; i++) sum[i] += sum[i - 1];
	for (i = 1; i <= tp; i++) h[sum[val[i]]--] = q[i];
	for (i = 1; i <= tp; i++) q[i] = h[tp - i + 1];
	int head = 0, tail = 0, now; node u, v;
	while (tp || head != tail) {
		now = head % M + 1;
		if (head == tail || tp && f[l][r][q[tp].x][q[tp].y] < f[l][r][h[now].x][h[now].y])
			u = q[tp--]; else { head = now; u = h[head]; }
		bo[u.x][u.y] = 1;
		for (i = 0; i < 4; i++) {
			v = gol[u.x][u.y][i];
			if (v.x && f[l][r][u.x][u.y] + 1 < f[l][r][v.x][v.y]) {
				f[l][r][v.x][v.y] = f[l][r][u.x][u.y] + 1;
				if (bo[v.x][v.y]) {
					bo[v.x][v.y] = 0; tail = tail % M + 1; h[tail] = v;
				}
			}
		}
	}
}
int main() {
	scanf("%d%d%d", &cnt, &n, &m);
	int i, j, k, x, y; char ch = getchar();
	memset(f, 0x3f, sizeof(f));
	for (i = 1; i <= m; i++) {
		while ((ch < '1' || ch > '9') && ch != 'A' && ch != 'C' && ch != 'x' && ch != '.') ch = getchar();
		for (j = 1; j <= n; j++, ch = getchar()) {
			mp[i][j] = ch;
			if (ch >= '1' && ch <= '9') {
				a[k = ch - '0'].x = i; a[k].y = j; f[k][k][i][j] = 0;
			}
		}
	}
	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++) if (mp[i][j] != 'x')
				for (k = 0; k < 4; k++) {
					dfsclk++; gol[i][j][k] = dfs(i, j, k);
				}
	for (i = 1; i <= cnt; i++) {
		q[tp = 1] = a[i]; val[1] = 0; spfa(i, i);
	}
	for (i = cnt - 1; i; i--)
		for (j = i + 1; j <= cnt; j++) {
			for (k = i; k < j; k++)
				for (x = 1; x <= m; x++)
					for (y = 1; y <= n; y++) f[i][j][x][y] = min(f[i][j][x][y], f[i][k][x][y] + f[k + 1][j][x][y]);
			tp = 0;
			for (x = 1; x <= m; x++)
				for (y = 1; y <= n; y++) if (f[i][j][x][y] < inf) {
						q[++tp].x = x; q[tp].y = y; val[tp] = f[i][j][x][y];
					}
			spfa(i, j);
		}
	int ans = inf;
	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++) ans = min(ans, f[1][cnt][i][j]);
	printf("%d\n", (ans < inf) ? ans : -1);
	return 0;
}
