
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline void R(int &v) {
    v=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c<='9'&&c>='0') {
        v=(v<<3)+(v<<1)+(c^'0');
        c=getchar();
    }
}
int pai[20],ans,cnt[5];
void dfs(int nowans) {
    if(nowans>ans)
        return;
    int j;
    int temp=0;
    memset(cnt,0,sizeof(cnt));
    for(int i=0; i<=14; ++i) {
        ++cnt[pai[i]];
    }
    while(cnt[4]) {
        --cnt[4];
        ++temp;
        if(cnt[2]>=2)
            cnt[2]-=2;
        else if(cnt[1]>=2) {
            cnt[1]-=2;
        }
    }
    while(cnt[3]) {
        --cnt[3];
        ++temp;
        if(cnt[2])
            --cnt[2];
        else if(cnt[1])
            --cnt[1];
    }
    if(pai[0]&&pai[1]&&cnt[1]>=2)--temp;
    temp+=cnt[1]+cnt[2];
    ans=min(temp+nowans,ans);
    for(int i=3; i<15; ++i) {
        for(j=i; pai[j]>=3&&j<15; ++j) {
            pai[j]-=3;
            if(j-i>=1)
                dfs(nowans+1);
        }
        while(j>i)
            pai[--j]+=3;
    }
    j=0;
    for(int i=3; i<15; ++i) {
        for(j=i; pai[j]>=2&&j<15; ++j) {
            pai[j]-=2;
            if(j-i>=2)
                dfs(nowans+1);
        }
        while(j>i)
            pai[--j]+=2;
    }
    j=0;
    for(int i=3; i<15; ++i) {
        for(j=i; pai[j]&&j<15; ++j) {
            pai[j]-=1;
            if(j-i>=4)
                dfs(nowans+1);
        }
        while(j>i)
            ++pai[--j];
    }
    j=0;
}
int main() {
    int T,n;
    R(T);
    R(n);
    int x,y;
    for(int l=1; l<=T; ++l) {
        memset(pai,0,sizeof(pai));
        for(int i=1; i<=n; ++i) {
            R(x);
            R(y);
            if(x) {
                if(x^1)
                    ++pai[x];
                if(x==1)
                    ++pai[14];
            } else {
                if(y==1) {
                    ++pai[0];
                }
                if(y==2) {
                    ++pai[1];
                }
            }
        }
        ans=n;
        dfs(0);
        cout<<ans<<"\n";
    }

    return 0;
}
