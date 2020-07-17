
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2510
using namespace std;
int n;
int f[N][5];

int main()
{
    scanf("%d",&n);
    int s=n/2;
    if(n%2==0)
        s--;
    f[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=4;j++)
            for(int k=max(0,i-s);k<i;k++)
                f[i][j]+=f[k][j-1];
    printf("%d\n",f[n][4]);
    return 0;
}
