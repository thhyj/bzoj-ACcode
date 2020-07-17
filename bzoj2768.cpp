
#include<iostream>
#include<cstdio>
#include<cstring>
#define T 301
#define inf 0x7fffffff
using namespace std;
int n,m,cnt=1,ans;
int q[305],h[305],head[305],cur[305];
struct data{int to,next,v;}e[500001];
void ins(int u,int v,int w)
{e[++cnt].to=v;e[cnt].next=head[u];e[cnt].v=w;head[u]=cnt;}
void insert(int u,int v,int w)
{ins(u,v,w);ins(v,u,0);}
bool bfs()
{
	int t=0,w=1;
	for(int i=0;i<=T;i++)h[i]=-1;
	q[0]=0;h[0]=0;
	while(t!=w)
	{
		int now=q[t];t++;
		for(int i=head[now];i;i=e[i].next)
			if(e[i].v&&h[e[i].to]==-1)
			{
				h[e[i].to]=h[now]+1;
				q[w++]=e[i].to;
			}
    }
    if(h[T]==-1)return 0;
    return 1;
}
int dfs(int x,int f)
{
	if(x==T)return f;
	int w,used=0;
	for(int i=cur[x];i;i=e[i].next)
	{
	    if(e[i].v&&h[e[i].to]==h[x]+1)
	    {
	    	w=f-used;
			w=dfs(e[i].to,min(e[i].v,w));
	    	e[i].v-=w;
	    	if(e[i].v)cur[x]=i;
			e[i^1].v+=w;
	    	used+=w;if(used==f)return f;
	    }
	}
    if(!used)h[x]=-1;
    return used;
}
void dinic()
{while(bfs()){for(int i=0;i<=T;i++)cur[i]=head[i];ans+=dfs(0,inf);}}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		if(x)insert(0,i,1);
		else insert(i,T,1); 
	}
	for(int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		ins(u,v,1);ins(v,u,1);
	}
	dinic();
	printf("%d",ans);
	return 0;
}
