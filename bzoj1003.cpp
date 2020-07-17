
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int maxlongint=0x7fffffff;
const int INF=maxlongint/3;

struct Edge{
    int from,to;
    int w;
    Edge(){
        from=to=0;
        w=0;
    }
    Edge(int from_,int to_,int w_){
        from=from_;
        to=to_;
        w=w_;
    }
};

struct Line{
    int l,r;
    Line(){
        l=r=0;
    }
    Line(int l_,int r_){
        l=l_;
        r=r_;
    }
};

int l[105],r[105];
bool can[1005];
bool used[1005];
int dis[1005];
int f[1005];
int n,m;
vector<int> G[1005];
vector<Edge> edges;
vector<Line> Num[1005];
int k;

bool Init(Line q,int a,int b)
{
    return min(q.r,b)-max(q.l,a)>=0;
}

void AddEdge(int from,int to,int w)
{
    edges.push_back(Edge(from,to,w));
    edges.push_back(Edge(to,from,w));
    int m=edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
}

void Bellman_Ford()
{
    memset(used,false,sizeof(used));
    queue<int> Q;
    for(int i=1;i<=m;i++)
        dis[i]=INF;
    dis[1]=0;
    Q.push(1);
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        used[u]=false;
        for(int i=0;i<G[u].size();i++){
            Edge e=edges[G[u][i]];
            if(!can[e.to])
                continue;
            if(dis[e.to]>dis[u]+e.w){
                dis[e.to]=dis[u]+e.w;
                if(!used[e.to]){
                    used[e.to]=true;
                    Q.push(e.to);
                }
            }
        }
    }
}

int Cover(int a,int b)
{
    memset(can,true,sizeof(can));
    for(int i=1;i<=m;i++)
        for(int j=0;j<Num[i].size();j++)
            if(Init(Num[i][j],a,b))
                can[i]=false;
    Bellman_Ford();
    return dis[m];
}

void Solve()
{
    f[1]=Cover(1,1);
    for(int i=2;i<=n;i++){
        f[i]=Cover(1,i);
        if(f[i]!=maxlongint/3)
            f[i]*=i;
        for(int j=2;j<=i;j++){
            int ans=Cover(j,i);
            if(ans==INF)
                continue;
            f[i]=min(f[i],f[j-1]+(i-j+1)*ans+k);
        }
    }
    printf("%d\n",f[n]);
}

void read()
{
    int e;
    scanf("%d%d%d%d",&n,&m,&k,&e);
    for(int i=1;i<=e;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        AddEdge(a,b,c);
    }
    int d;
    scanf("%d",&d);
    for(int i=1;i<=d;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        Num[a].push_back(Line(b,c));
    }
}
int main()
{
    read();
    Solve();
    return 0;
}
