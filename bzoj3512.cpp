
#include <bits/stdc++.h>
#define ll long long
#define N 2000009
#define mod 1000000007
using namespace std;
int n, M, pri[N], pd[N], cnt, phi[N], Min[N], Ans[N], sum[N];
#define pii pair<int ,int>
#define mk make_pair
map<pii, int>MAP;
int S(int n, int m)
{
    if (m <= 1) return phi[n * m];
    if (n == 1)
    {
        if (m < N) return sum[m];
        if (Ans[M / m] != -1) return Ans[M / m];
        ll ans = (ll)m * (m + 1) / 2 % mod;
        for (int i = 2, j; i <= m; i = j + 1)
        {
            j = m / (m / i);
            ans = ans - (ll)(j - i + 1) * S(1, m / i) % mod + mod;
        }
        return Ans[M / m] = ans % mod;
    }
    else
    {
        if (MAP[mk(n, m)]) return MAP[mk(n, m)];
        ll ans = 0;
        for (int i = 1; i * i <= n; i++)
            if (n % i == 0)
            {
                ans = ans + (ll)phi[n / i] * S(i, m / i) % mod;
                if (i * i != n) ans = ans + (ll)phi[i] * S(n / i, m / (n / i)) % mod;
            }
        return MAP[mk(n, m)] = ans % mod;
    }
}
int main()
{
    ll ans = 0;
    scanf("%d%d", &n, &M);
    memset(Ans, -1, sizeof Ans);
    if (n > M) swap(n, M);
    Min[1] = phi[1] = pd[1] = 1;
    for (int i = 2; i < N; i++)
    {
        if (!pd[i]) pri[++cnt] = Min[i] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && i * pri[j] < N; j++)
        {
            pd[i * pri[j]] = 1;
            if (i % pri[j] == 0)
            {
                Min[pri[j]*i] = Min[i];
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            }
            phi[i * pri[j]] = phi[i] * (pri[j] - 1);
            Min[i * pri[j]] = Min[i] * pri[j];
        }
    }
    for (int i = 1; i < N; i++) sum[i] = (phi[i] + sum[i - 1]) % mod;
    for (int i = 1; i <= n; i++) ans = ans + ((ll)i / Min[i] * S(Min[i], M) % mod);
    printf("%lld\n", ans % mod);
    return 0;
}
