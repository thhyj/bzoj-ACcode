
#include<iostream>  
#include<cstdio>  
#include<cstdlib>  
#include<cstring>  
#include<ctime>  
#include<algorithm>  
#include<iomanip>  
#include<cmath>  
#include<queue>  
#include<bitset>  
#include<map>  
using namespace std;  
#define MAXN 5010  
#define ll long long  
char ch,BB[1<<15],*S=BB,*T=BB;  
#define getc() (S==T&&(T=(S=BB)+fread(BB,1,1<<15,stdin),S==T)?0:*S++)  
inline int read()  
{  
int x=0,f=1;char ch=getc();  
while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}  
while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}  
return x*f;  
}  
struct ply{  
    int h;  
    int s;  
    ll v;  
};  
inline bool cmph(ply x,ply y){  
    return x.h<y.h;  
}  
inline bool cmpv(ply x,ply y){  
    return x.v<y.v;  
}  
ply sh[MAXN],sv[MAXN];  
int n,ans;  
ll A,B,C;  
int main(){  
    int i,j,l,r,cnt;  
    n=read();  
    A=read();  
    B=read();  
    C=read();  
    for(i=1;i<=n;i++){  
        sh[i].h=read();  
        sh[i].s=read();  
        sh[i].v=A*sh[i].h+B*sh[i].s;  
        sv[i]=sh[i];  
    }  
    sort(sh+1,sh+n+1,cmph);  
    sort(sv+1,sv+n+1,cmpv);  
    for(i=1;i<=n;i++){  
        l=r=0;  
        cnt=0;  
        ll mx=sh[i].s+C/B;  
        for(j=1;j<=n;j++){  
            while(r<n&&sv[r+1].v<=A*sh[j].h+B*sh[i].s+C){  
                r++;  
                if(sv[r].s>=sh[i].s&&sv[r].s<=mx){  
                    cnt++;  
                }  
            }  
            while(l<n&&sh[l+1].h<sh[j].h){  
                l++;  
                if(sh[l].s>=sh[i].s&&sh[l].s<=mx){  
                    cnt--;  
                }  
            }  
            if(cnt>ans){  
                ans=cnt;  
            }  
        }  
    }  
    printf("%d\n",ans);  
    return 0;  
}  
