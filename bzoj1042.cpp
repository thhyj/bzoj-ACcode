
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int c[5];
long long F[110000];
struct{long long operator[](int pos){return pos<0?0:F[pos];}}f;
int main(int argc, char *argv[])
{
    int T;scanf("%d%d%d%d%d",&c[1],&c[2],&c[3],&c[4],&T);
    F[0]=1;
    for(int i=1;i<=4;i++)
        for(int j=0;j<=100000;j++)
        if(j+c[i]<=100000)F[j+c[i]]+=F[j];
    while(T--)
    {
        int d[5],s;scanf("%d%d%d%d%d",&d[1],&d[2],&d[3],&d[4],&s);
        long long ans=f[s];
        ans-=f[s-(d[1]+1)*c[1]];
        ans-=f[s-(d[2]+1)*c[2]];
        ans-=f[s-(d[3]+1)*c[3]];
        ans-=f[s-(d[4]+1)*c[4]];
        ans+=f[s-(d[1]+1)*c[1]-(d[2]+1)*c[2]];
        ans+=f[s-(d[1]+1)*c[1]-(d[3]+1)*c[3]];
        ans+=f[s-(d[1]+1)*c[1]-(d[4]+1)*c[4]];
        ans+=f[s-(d[2]+1)*c[2]-(d[3]+1)*c[3]];
        ans+=f[s-(d[2]+1)*c[2]-(d[4]+1)*c[4]];
        ans+=f[s-(d[3]+1)*c[3]-(d[4]+1)*c[4]];
        ans-=f[s-(d[1]+1)*c[1]-(d[2]+1)*c[2]-(d[3]+1)*c[3]];
        ans-=f[s-(d[1]+1)*c[1]-(d[2]+1)*c[2]-(d[4]+1)*c[4]];
        ans-=f[s-(d[1]+1)*c[1]-(d[3]+1)*c[3]-(d[4]+1)*c[4]];
        ans-=f[s-(d[2]+1)*c[2]-(d[3]+1)*c[3]-(d[4]+1)*c[4]];
        ans+=f[s-(d[1]+1)*c[1]-(d[2]+1)*c[2]-(d[3]+1)*c[3]-(d[4]+1)*c[4]];
        #ifdef ONLINE_JUDGE
            printf("%lld\n",ans);
        #else
            printf("%I64d\n",ans);
        #endif
    }
    return 0;
}
