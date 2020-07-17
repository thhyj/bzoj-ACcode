
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAXN 300010
using namespace std;
long long f[MAXN<<2],sta[MAXN<<2];
int c,m,n,cnt;
int main()
{
    cin>>c>>m>>n;f[0]=0;f[1]=c;
    if (m==1)   return puts("1"),0;
    for (int i=2;i<=(n<<2);i++)
    {
        f[i]=(f[i-1]+f[i-2])%m;
        if ((i&1)&&i>6) sta[++cnt]=f[i]*c%m;
    }
    sort(sta+1,sta+cnt+1);
    int t=cnt;cnt=0;
    for (int i=1;i<=t;i++)  if (sta[i]!=sta[i-1]||i==1) sta[++cnt]=sta[i];
    cnt%=m;
    cout<<cnt<<endl;
}
