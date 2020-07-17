
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=20;

int f[1<<maxn],sum[1<<maxn];
int main(){
    int n,m,x;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&sum[1<<i]);
        
    scanf("%d",&m);
    for(int i=n;i<n+m;i++){
        scanf("%d",&x);
        sum[1<<i]=-x;
    }
    
    int end=1<<(n+m);
    
    for(int i=1;i<end;i++){
        int t=i&-i;
        sum[i]=sum[t]+sum[i-t];
        for(int j=0;j<n+m;j++)
            if(i&(1<<j)) f[i]=max(f[i],f[i^(1<<j)]);
        if(!sum[i]) f[i]++;
    }
    
    printf("%d",n+m-2*f[end-1]);
    return 0;
}
