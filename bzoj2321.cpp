
#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
long long sum1,sum2;
int main()
{
    scanf("%d%d",&n,&m);
    int x;
    for(int i=1;i<=n;i++)
       for(int j=1;j<=m;j++)
       {
               scanf("%d",&x);
               sum1+=((i*i)+(j*j))*x; 
               }
    for(int i=1;i<=n;i++)
       for(int j=1;j<=m;j++)
       {
               scanf("%d",&x);
               sum2+=((i*i)+(j*j))*x; 
               }
    printf("%lld",(sum1-sum2)/2);
    return 0;
}
