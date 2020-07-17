
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1005;
typedef long long ll;
inline int read(){
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0'; c=getchar();}
    return x*f;
}
int n;
int p[N];
bool notp[N];
void sieve(int n){
    for(int i=2;i<=n;i++){
        if(!notp[i]) p[++p[0]]=i;
        for(int j=1;j<=p[0]&&i*p[j]<=n;j++){
            notp[i*p[j]]=1;
            if(i%p[j]==0) break;
        }
    }
}
ll f[N][N];
void dp(){
    f[0][0]=1;
    for(int i=1;i<=p[0];i++)
        for(int j=0;j<=n;j++){
            f[i][j]=f[i-1][j];
            for(int k=p[i];k<=j;k*=p[i])
                f[i][j]+=f[i-1][j-k];
        }
    ll ans=0;
    for(int i=0;i<=n;i++) ans+=f[p[0]][i];
    printf("%lld",ans);
}
int main(){
   // freopen("in","r",stdin);
    n=read();
    sieve(n);
    dp();
}
