
#include<cstdio>
#define N 3010
int n,m,C,i,j,k,a[N],b[N],c[N],f[N][N],g[N][N],d[N],e[N],ans=-1;
inline int max(int a,int b){return a>b?a:b;}
int main(){
  for(scanf("%d",&n),i=1;i<=n;i++)scanf("%d",&a[i]);
  for(scanf("%d",&m),i=1;i<=m;i++)scanf("%d",&b[i]);
  for(scanf("%d",&C),i=1;i<=C;i++)scanf("%d",&c[i]);
  for(i=1;i<=n;i++)for(j=1;j<=m;j++)f[i][j]=a[i]==b[j]?(f[i-1][j-1]+1):max(f[i-1][j],f[i][j-1]);
  if(!C)return printf("%d",f[n][m]),0;
  for(i=n;i;i--)for(j=m;j;j--)g[i][j]=a[i]==b[j]?(g[i+1][j+1]+1):max(g[i+1][j],g[i][j+1]);
  for(i=1;i<=n;i++)for(j=i,k=1;j<=n;j++){
    if(a[j]==c[k])k++;
    if(k>C){d[i]=j;break;}
  }
  for(i=1;i<=m;i++)for(j=i,k=1;j<=m;j++){
    if(b[j]==c[k])k++;
    if(k>C){e[i]=j;break;}
  }
  for(i=1;i<=n;i++)if(d[i])for(j=1;j<=m;j++)if(e[j])ans=max(ans,f[i-1][j-1]+g[d[i]+1][e[j]+1]+C);
  return printf("%d",ans),0;
}
