
#include<iostream>
#include<cstdio>
#define N 1000005
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n,ans;
int fa[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
int main()
{
    n=read();	
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=n;i++)
	{
		int x=read();
		int p=find(i),q=find(x);
		if(p!=q)fa[q]=i;
    }
	for(int i=1;i<=n;i++)
	    if(fa[i]==i)ans++;
	printf("%d",ans);
	return 0;
}
