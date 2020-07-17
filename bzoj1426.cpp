
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define MAXN 10010
int N;
double g[MAXN],f[MAXN];
int main()
{
    scanf("%d",&N);
    for (int i=N-1; i>=0; i--) g[i]=g[i+1]+1.0*N/(N-i);
    for (int i=N-1; i>=0; i--) f[i]=f[i+1]+g[i+1]+g[i]*1.0*i/(N-i)+1.0*N/(N-i);
    printf("%.2lf\n",f[0]);
}
