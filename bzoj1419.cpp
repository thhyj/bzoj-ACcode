
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=5100;
double f[2][maxn];
int r,b,x=0;
int main()
{
    scanf("%d%d",&r,&b);
    for(int i=1;i<=r;i++)
    {
        f[x][0]=i;
        for(int j=1;j<=b;j++)
        f[x][j]=max(0.0,1.0*i/(i+j)*(1+f[1-x][j])+1.0*j/(i+j)*(-1+f[x][j-1]));
        x=1-x;
    }
    printf("%.6lf\n",f[1-x][b]-5e-7);
    return 0;
}
