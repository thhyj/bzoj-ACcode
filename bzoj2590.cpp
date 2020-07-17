
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#include<queue>
//#include<iostream>
using namespace std;

int n, K;
#define LL long long
LL t;
#define maxn 50011
int a[maxn], b[maxn]; bool vis[maxn];
struct node
{
    int id; LL v;
    bool operator < (const node &b) const {return v < b.v;}
    bool operator > (const node &b) const {return v > b.v;}
} tb[maxn];
priority_queue<node, vector<node>, greater<node> > qa, qb, qc;
int main()
{
    scanf("%d%d%lld", &n, &K, &t);
    for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]), tb[tb[i].id = i].v = b[i];
    sort(tb + 1, tb + 1 + n);
    memset(vis, 0, sizeof(vis));
    int ans = 0;
    for (int i = 1; i <= K; i++)
    {
        t -= tb[i].v;
        if (t < 0) break;
        vis[tb[i].id] = 1;
        ans++;
    }
    if (t < 0) printf("%d\n", ans);
    else
    {
        for (int i = 1; i <= n; i++)
            if (vis[i]) qc.push((node) {i, a[i] - b[i]});
        else qa.push((node) {i, a[i]}), qb.push((node) {i, b[i]});
        while (t >= 0)
        {
            while (!qa.empty() && vis[qa.top().id]) qa.pop();
            while (!qb.empty() && vis[qb.top().id]) qb.pop();
            if (qa.empty() || qb.empty()) break;
            int tmp = qb.top().v + qc.top().v;
            if (tmp < qa.top().v)
            {
                t -= tmp;
                if (t < 0) break;
                ans++;
                vis[qb.top().id] = 1;
                qc.pop();
                qc.push((node) {qb.top().id, a[qb.top().id] - b[qb.top().id]});
                qb.pop();
            }
            else
            {
                t -= qa.top().v;
                if (t < 0) break;
                ans++;
                vis[qa.top().id] = 1;
                qa.pop();
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
