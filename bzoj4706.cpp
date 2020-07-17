
#include<iostream>
using namespace std;
int mod=1000000007;
long long f[1000005],inv[1000005];
int main()
{
    int n,i;
    inv[0]=inv[1]=f[0]=f[1]=1;
    cin>>n;
    for(int i=2;i<=n;i++)
    inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    for(int i=2;i<=n-2;i++)
    f[i]=((6*i-3)*f[i-1]%mod-(i-2)*f[i-2]%mod+mod)%mod*inv[i+1]%mod;
    cout<<f[n-2];
}
