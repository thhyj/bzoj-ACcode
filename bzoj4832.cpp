
#include<iostream>  
#include<cstring>  
#include<ctime>  
#include<cmath>  
#include<algorithm>  
#include<iomanip>  
#include<cstdlib>  
#include<cstdio>  
#include<map>  
#include<bitset>  
#include<set>  
#include<stack>  
#include<vector>  
#include<queue>  
using namespace std;  
#define MAXN 51  
#define MAXM 10  
#define ll long long  
#define eps 1e-8  
#define MOD 1000000007  
#define INF 1000000000  
double f[MAXN][MAXM][MAXM][MAXM],p[MAXN][MAXM][MAXM][MAXM];  
int n,A,B,C;  
int main(){  
    int i,j,k,l;  
    int tmp;  
    scanf("%d",&tmp);  
    while(tmp--){  
        scanf("%d%d%d%d",&n,&A,&B,&C);  
        for(i=0;i<=n;i++){  
            for(j=0;j<=7;j++){  
                for(k=0;k<=7;k++){  
                    for(l=0;l<=7;l++){  
                        p[i][j][k][l]=0;  
                        f[i][j][k][l]=0;  
                    }  
                }  
            }  
        }  
        p[0][A][B][C]=1;  
        for(i=0;i<n;i++){  
            for(j=0;j<=7;j++){  
                for(k=0;k<=7;k++){  
                    for(l=0;l<=7;l++){  
                        if(j+k+l<=7){  
                            p[i+1][j][k][l]+=p[i][j][k][l]*1/(j+k+l+1);  
                            f[i+1][j][k][l]+=(f[i][j][k][l]+p[i][j][k][l])*1/(j+k+l+1);  
                            if(j){  
                                p[i+1][j-1][k][l]+=p[i][j][k][l]*j/(j+k+l+1);  
                                f[i+1][j-1][k][l]+=f[i][j][k][l]*j/(j+k+l+1);  
                            }  
                            if(j+k+l==7){  
                                if(k){  
                                    p[i+1][j+1][k-1][l]+=p[i][j][k][l]*k/(j+k+l+1);  
                                    f[i+1][j+1][k-1][l]+=f[i][j][k][l]*k/(j+k+l+1);  
                                }  
                                if(l){  
                                    p[i+1][j][k+1][l-1]+=p[i][j][k][l]*l/(j+k+l+1);  
                                    f[i+1][j][k+1][l-1]+=f[i][j][k][l]*l/(j+k+l+1);  
                                }  
                            }else{  
                                if(k){  
                                    p[i+1][j+1][k-1][l+1]+=p[i][j][k][l]*k/(j+k+l+1);  
                                    f[i+1][j+1][k-1][l+1]+=f[i][j][k][l]*k/(j+k+l+1);  
                                }  
                                if(l){  
                                    p[i+1][j][k+1][l]+=p[i][j][k][l]*l/(j+k+l+1);  
                                    f[i+1][j][k+1][l]+=f[i][j][k][l]*l/(j+k+l+1);  
                                }  
                            }  
                        }  
                    }  
                }  
            }  
        }  
        double ans=0;  
        for(i=0;i<=7;i++){  
            for(j=0;j<=7;j++){  
                for(k=0;k<=7;k++){  
                    ans+=f[n][i][j][k];  
                }  
            }  
        }  
        printf("%.2lf\n",ans);  
    }  
    return 0;  
}
