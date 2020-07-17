
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring> 
using namespace std;
int n,kk,p[20],a[20],maxx;
long long f[20][1<<16],ans;
int main(){
  scanf("%d%d",&n,&kk);maxx=(1<<n)-1;
  for(int i=1;i<=n;i++){scanf("%d",&a[i]);p[i]=1<<(i-1);}
  for (int i=1;i<=n;i++)f[i][p[i]]=1;
  for (int i=0;i<=maxx;i++)
   for (int j=1;j<=n;j++)
    if (p[j]&i)
     for (int k=1;k<=n;k++)
       if ((p[k]|i)!=i&&abs(a[k]-a[j])>kk) f[k][p[k]|i]+=f[j][i];
  for (int i=1;i<=n;i++) ans+=f[i][maxx];
  cout<<ans<<endl;
}        
