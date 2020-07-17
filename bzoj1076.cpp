
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
#define LL long long
#define inf 1<<30
#define Pi acos(-1.0)
#define free(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout);
using namespace std;
 
const int maxn=110;
int bin[30];
int n,K,S[maxn],p[maxn];
double f[maxn][1<<15];
 
int main() {
    bin[0]=1;for (int i=1;i<=20;i++) bin[i]=bin[i-1]<<1;
    scanf("%d%d",&K,&n);
    for (int x,i=1;i<=n;i++) {
        scanf("%d",&p[i]);
        while (scanf("%d",&x)!=EOF && x) S[i]+=bin[x-1];
    }
    for (int i=K;i>=1;i--)
        for (int j=0;j<bin[n];j++) {
            for (int k=1;k<=n;k++) {
                if ((S[k]&j)==S[k]) f[i][j]+=max(f[i+1][j],f[i+1][j|bin[k-1]]+p[k]);   //可以选择不吃
                else f[i][j]+=f[i+1][j];
            }
            f[i][j]/=n;
        }
    printf("%.6lf",f[1][0]);
    return 0;
}
