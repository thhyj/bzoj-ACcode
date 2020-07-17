
#include<cstdio>
#define N 500010
typedef long long ll;
int n, k, i, j, x, y, z, g[N], nxt[N << 1], v[N << 1], w[N << 1], ed, f[N], dis[N], h, t, q[N], size[N], de[N];
ll d[N][4], u[N][2], tmp;
bool is[N];
inline void read(int&a) {
  char c;
  while (!(((c = getchar()) >= '0') && (c <= '9')));
  a = c - '0';
  while (((c = getchar()) >= '0') && (c <= '9'))
    (a *= 10) += c - '0';
}
inline void add(int x, int y, int z) {
  v[++ed] = y; w[ed] = z; nxt[ed] = g[x]; g[x] = ed;
}
inline ll min(ll x, ll y) {return x < y ? x : y;}
int main() {
  read(n), read(k);
  for (i = 1; i < n; i++)read(x), read(y), read(z), add(x, y, z), add(y, x, z);
  while (k--)read(x), is[x] = 1;
  q[h = t = 1] = 1;
  while (h <= t)
    for (j = g[x = q[h++]]; j; j = nxt[j])
      if (v[j] != f[x])f[q[++t] = v[j]] = x, dis[v[j]] = w[j];
  for (i = n; i; i--) {
    size[x = q[i]] = is[x];
    for (j = g[x]; j; j = nxt[j])
      if (v[j] != f[x] && size[v[j]]) {
        size[x] += size[v[j]];
        d[x][0] += d[v[j]][0] + 2LL * w[j];
        tmp = d[v[j]][1] - d[v[j]][0] - w[j];
        if (tmp < d[x][2])d[x][3] = d[x][2], d[x][2] = tmp, de[x] = v[j]; else d[x][3] = min(d[x][3], tmp);
      }
    d[x][1] = d[x][0] + d[x][2];
  }
  for (i = 2; i <= n; i++)if (size[1] > size[x = q[i]]) {
      u[x][0] = u[f[x]][0] + d[f[x]][0] - d[x][0];
      u[x][1] = u[f[x]][1] + d[f[x]][0];
      if (de[f[x]] == x)u[x][1] = min(u[x][1], u[f[x]][0] + d[f[x]][0] + d[f[x]][3]);
      else u[x][1] = min(u[x][1], u[f[x]][0] + d[f[x]][1]);
      u[x][1] -= d[x][0] + dis[x];
      if (!size[x])u[x][0] += 2 * dis[x], u[x][1] += 2 * dis[x];
    }
  for (i = 1; i <= n; i++)printf("%lld\n", min(d[i][0] + u[i][1], d[i][1] + u[i][0]));
  return 0;
}
