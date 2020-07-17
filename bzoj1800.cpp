
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
inline void R(int &v)
{
    static char ch;
    v=0;
    bool p=0;
    do{
        ch=getchar();
        if(ch=='-')
        {
            p=1;
        }
    }while(!isdigit(ch));
    while(isdigit(ch))
    {
        
        v=(v<<1)+(v<<3)+(ch^'0');
        ch=getchar();
    }
    if(p)v=-v;
}
int main()
{
    int n;
    R(n);
    int a[100],tot=0,b[100];
    if(n<4)
    {
        cout<<0;
        return 0;
    }
    memset(b,0,sizeof(b));
    for(int i=1;i<=n;++i)
    {
        R(a[i]);
        b[i]=b[i-1]+a[i];
        tot+=a[i];
    }
    int ans=0;
    for(int i=1;i<=n-3;++i)
        for(int j=i+1;j<=n-2;++j)
            for(int k=j+1;k<=n-1;++k)
                for(int l=k+1;l<=n;++l)
                {
                    if((b[j]-b[i]==b[l]-b[k])&&(b[k]-b[j]==b[i]+tot-b[l]))
                        ++ans;
                }
    cout<<ans;
    return 0;
}
