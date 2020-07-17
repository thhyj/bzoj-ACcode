
#include<iostream>  
#include<cstdlib>  
#include<cstdio>  
#include<cstring>  
#include<ctime>  
#include<cmath>  
#include<algorithm>  
#include<iomanip>  
#include<queue>  
#include<map>  
#include<bitset>  
#include<stack>  
#include<vector>  
#include<set>  
using namespace std;  
#define MAXN 2010  
#define MAXM 1010  
#define INF 1000000000  
#define MOD 1000000007  
#define ll long long  
#define eps 1e-8  
int n,m;  
ll sa[MAXN][MAXN],sb[MAXN][MAXN];  
int a[MAXN][MAXN],b[MAXN][MAXN];  
char xB[1<<15],*xS=xB,*xT=xB;  
#define getc() (xS==xT&&(xT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xT)?0:*xS++)  
inline int read()  
{  
int x=0,f=1;char ch=getc();  
while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}  
while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}  
return x*f;  
}  
int main(){  
    int i,j,x,y,xx,yy;  
    n=read();  
    m=read();  
    for(i=1;i<=n;i++){  
        for(j=1;j<=n;j++){  
            a[i][j]=read();  
            sa[i][j]=sa[i-1][j]+a[i][j];  
        }  
    }  
    for(i=1;i<=n;i++){  
        for(j=1;j<=n;j++){  
            b[i][j]=read();  
            sb[i][j]=sb[i][j-1]+b[i][j];  
        }  
    }  
    while(m--){  
        x=read();  
        y=read();  
        xx=read();  
        yy=read();  
        if(x>xx){  
            swap(x,xx);  
        }  
        if(y>yy){  
            swap(y,yy);  
        }  
        ll ans=0;  
        for(i=1;i<=n;i++){  
            ans+=(sa[xx][i]-sa[x-1][i])*(sb[i][yy]-sb[i][y-1]);  
        }  
        printf("%lld\n",ans);  
    }  
    return 0;  
}
