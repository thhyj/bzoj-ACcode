
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
char s[111];
int f[101][101];
bool check(int l,int r,int cl,int cr)
{
        if((r-l+1)%(cr-cl+1)!=0) return 0;
        for(int i=l; i<=r; i++)
                if(s[i]!=s[(i-l)%(cr-cl+1)+cl]) return 0;
        return 1;
}
int calc(int x)
{
        int t=0;
        while(x) {
                x/=10;
                t++;
        }
        return t;
}
int dp(int l,int r)
{
        if(l==r) return 1;
        if(f[l][r]^-1) return f[l][r];
        int ret=r-l+1;
        for(int i=l; i<r; ++i)
        {
                ret=min(ret,dp(l,i)+dp(i+1,r));
                if(check(i+1,r,l,i))
                {
                        ret=min(ret,dp(l,i)+2+calc((r-i)/(i-l+1)+1));
                }
        }
        return f[l][r]=ret;
}
int main()
{
        cin>>s;
        memset(f,-1,sizeof(f));
        int n=strlen(s);
        cout<<dp(0,n-1);
}
