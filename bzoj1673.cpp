
#include <iostream>
#include <stdio.h>
#include <string.h>
#define MAX_N 1005

using namespace std;

int n,c;
int ans=0;
int w[MAX_N];
long long sum[MAX_N];

void dfs(int col,int tot)
{
    if(tot>c) return;
    ans=max(ans,tot);
    if(col>n) return;
    if(tot+sum[n]-sum[col-1]<=ans) return;
    dfs(col+1,tot+w[col]);
    dfs(col+1,tot);
}

void read()
{
    cin>>n>>c;
    for(int i=n;i>=1;i--)
    {
        cin>>w[i];
    }
}

void solve()
{
    sum[0]=0;
    for(int i=1;i<=n;i++)
    {
        sum[i]=sum[i-1]+w[i];
    }
    dfs(1,0);
}

void print()
{
    cout<<ans<<endl;
}

int main()
{
    read();
    solve();
    print();
}
