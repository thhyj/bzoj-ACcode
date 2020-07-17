
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int f[1010][1010],n;
int a[1010],b[1010];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            if(abs(a[i]-b[j])<=4) f[i][j]=max(f[i][j],f[i-1][j-1]+1);
        for(int j=2;j<=n;j++) f[i][j]=max(f[i][j],max(f[i][j-1],f[i-1][j]));
    }
    printf("%d",f[n][n]);}
