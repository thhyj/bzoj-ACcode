
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <functional>
#define Maxn 2100
#define inf 1<<30
using namespace std;

struct Tnode
{
       int num, id;
       };
int n, f[Maxn], a[Maxn];
Tnode d[Maxn];
bool cmp(const Tnode &a, const Tnode &b)
{
     return a.num <b.num;
     }
void dp()
{
     for(int i=0; i<n; i++) f[i] = abs(a[d[i].id] - a[0]);
     for (int i=1; i<n; i++)
     {
         int tmp = f[0];
         for (int j=0; j<n; j++)
         {
             tmp = min(tmp, f[j]);
             f[j] = tmp + abs(a[d[j].id]-a[i]);             
         }         
     }
     int ans = inf;
     for (int i=0; i<n; i++) ans = min(ans, f[i]);
     cout <<ans <<endl;    
     }
int main()
{
    scanf("%d", &n);
    for (int i=0; i<n; i++)
    {
        scanf("%d", &d[i].num);
        a[i] = d[i].num;
        d[i].id = i;
    }
    sort(d, d+n, cmp);
    dp();
    return 0;
    }
