
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <set>
 
using namespace std;
 
const int MaxN = 100000 + 5, INF = 999999999;
 
int n, k, Ans;
int A[MaxN], d[MaxN], Next[MaxN], Prev[MaxN];
 
struct ES
{
    int x, y;
    ES() {}
    ES(int a, int b) {x = a; y = b;}
     
    bool operator < (const ES &e) const
    {
        if (y == e.y) return x < e.x;
        return y < e.y;
    }
};
 
set<ES> S;
set<ES> :: iterator It;
 
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &d[i]);
        A[i] = d[i] - d[i - 1];
    }
    for (int i = 2; i <= n; ++i)
    {
        Next[i] = i + 1;
        Prev[i] = i - 1;
        S.insert(ES(i, A[i]));
    }
    A[1] = A[n + 1] = INF;
    int x;
    for (int i = 1; i <= k; ++i)
    {
        It = S.begin();
        x = (*It).x;
        Ans += A[x];
        S.erase(ES(x, A[x]));
        S.erase(ES(Prev[x], A[Prev[x]]));
        S.erase(ES(Next[x], A[Next[x]]));
        A[x] = A[Prev[x]] + A[Next[x]] - A[x];
        S.insert(ES(x, A[x]));
        if (Prev[Prev[x]]) Next[Prev[Prev[x]]] = x;
        if (Next[Next[x]]) Prev[Next[Next[x]]] = x;
        Prev[x] = Prev[Prev[x]];
        Next[x] = Next[Next[x]];
    }
    printf("%d\n", Ans);
    return 0;
}
