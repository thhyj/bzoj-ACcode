
#include <bits/stdc++.h>
using namespace std;
inline void R (long long &v)
{
        static char ch;
        v=0; bool p=0;
        do {
                ch=getchar();
                if(ch=='-')
                {
                        p=1;
                }
        } while(!isdigit(ch));
        while(isdigit(ch))
        {
                v=(v<<1)+(v<<3)+(ch^'0');
                ch=getchar();
        }
        if(p)
                v=-v;
}
long long pow1[1000005],first[1000005],nxt[2000005],to[2000005],fa[1000005];
bool vis[1000005];
long long bh[1000005];
long long dp[1000005][2],f[1000005][4];
long long ez[1000005];
long long cnt;
long long tot;
long long ans2;
long long ans;
inline void create(const long long &x,const long long &y)
{
        nxt[++tot]=first[x];
        first[x]=tot;
        to[tot]=y;
}
inline void trdp(const long long &x)
{
        //if(vis[x]) return;
        dp[x][0]=0,dp[x][1]=pow1[x];
        vis[x]=1;
        for(long long p=first[x]; p; p=nxt[p])
        {
                trdp(to[p]);
                dp[x][0]+=max(dp[to[p]][1],dp[to[p]][0]);
                dp[x][1]+=dp[to[p]][0];
        }
}
inline void dp2()
{
        long long i,k;
        ans=0;
        f[1][1]=0; f[1][2]=0;
        f[1][0]=dp[bh[1]][1];
        f[1][3]=dp[bh[1]][0];
        for(i=2; i<=cnt; i++)
        {
                k=bh[i];
                f[i][0]=f[i-1][1]+dp[k][1];
                f[i][1]=max(f[i-1][0],f[i-1][1])+dp[k][0];
                f[i][2]=f[i-1][3]+dp[k][1];
                f[i][3]=max(f[i-1][2],f[i-1][3])+dp[k][0];
        }
        ans=max(f[cnt][1],max(f[cnt][2],f[cnt][3]));
}
int main()
{
        long long n;
        long long x;
        R(n);
        for(long long i=1; i<=n; ++i)
        {
                R(pow1[i]),R(x);
                //create(i,x),
                create(x,i);
                fa[i]=x;
        }
        long long k,now;
        for(long long i=1; i<=n; ++i)
        {
                if(vis[i]) continue;

                cnt=0;
                k=i;
                while(!vis[k])
                {
                        vis[k]=1;
                        k=fa[k];
                        ez[fa[k]]=k;
                }
                now=k;
                while(1)
                {
                        dp[k][1]=pow1[k];
                        for(long long p=first[k]; p; p=nxt[p])
                        {
                                if(to[p]^ez[k])
                                {
                                        trdp(to[p]);
                                        dp[k][0]+=max(dp[to[p]][1],dp[to[p]][0]);
                                        dp[k][1]+=dp[to[p]][0];
                                }
                        }
                        bh[++cnt]=k;
                        k=fa[k];
                        if(k==now) break;
                }
                dp2();
                ans2+=ans;
        }
        cout<<ans2<<'\n';
        return 0;
}
