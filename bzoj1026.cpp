
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int num[20];
int dp[20][10][2][2];
int lena;
int dfs(int len,int qq,int xz,int zero) {
    if(!len)
        return zero;
    int n,res=0;
    if(dp[len][qq][xz][zero]!=-1)
        return dp[len][qq][xz][zero];
    if(xz)
        n=num[len];
    else
        n=9;
    if(!zero)
        for(register int i=0; i<=n; ++i)
        res+=dfs(len-1,i,xz&&i==n,i||zero);
    else
    for(register int i=0; i<=n; ++i) {
        if(i-qq<2&&i-qq>-2)
            {//cout<<"此时的len为"<<len<<" ";
               // cout<<qq<<i<<"\n";
                continue;}
        res+=dfs(len-1,i,xz&&i==n,1);
    }
    dp[len][qq][xz][zero]=res;
    return res;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long a,b;
    cin>>a>>b;
    --a;
    int len=0;
    memset(dp,-1,sizeof(dp));
    int ans1;
    if(a<10)
        ans1=a;
    else {
        while(a) {
            num[++len]=a%10;
            a/=10;
        }
        lena=len;
        ans1=dfs(len,0,1,0);
        memset(num,0,sizeof(num));
        len=0;
    }
     memset(dp,-1,sizeof(dp));
    int ans2;
    if(b<10)
        ans2=b;
    else {
        while(b) {
            num[++len]=b%10;
            b/=10;
        }
        lena=len;
        for(int i=1;i<=len;++i)
        ans2=dfs(len,0,1,0);
    }
  //  cout<<ans1<<"\n"<<ans2<<"\n";
    cout<<ans2-ans1;
    return 0;
}
