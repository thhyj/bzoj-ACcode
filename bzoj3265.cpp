
#include <bits/stdc++.h>
const int inf=210000000;
using namespace std;
inline void R(int &v) {
    static char ch;
    v = 0;
    bool p = 0;
    do {
       ch = getchar();
       if(ch == '-')
           p = 1;
    }while(!isdigit(ch));
    while(isdigit(ch)) {
        v = (v + (v << 2) <<1) + (ch ^ '0');
        ch = getchar();
    }
    if(p)
         v = -v;
}
struct node {
    int to,length,pa,w;
    node (int to, int length, int pa, int w):to(to),length(length),pa(pa),w(w){
    }
    node (){
    }
};
vector<node>edge[10005];
const int MAXN = 10100;
inline void create (const int &x, const int &y, const int &z,const int &w) {
    edge[x].push_back(node(y, z, edge[y].size(), w));
    edge[y].push_back(node(x, 0 ,edge[x].size()-1, -w));    
}
typedef pair<int, long long> Pair;
const long long INF = 9187201950435737471;
inline Pair getflow(int s, int t, int n) {
    Pair ans(0, 0);
    while (1) {
        static bool vis[MAXN];
        static long long dis[MAXN];
        static int prev[MAXN], pree[MAXN];
        queue<int> q;
        //fill(dis, dis + n + 1, INF);
         memset(dis, 127, sizeof(long long) * (n + 1));
        memset(vis, 0, sizeof(bool) * (n + 1));
        q.push(s), dis[s] = 0;
        while (!q.empty()) {
            register int u = q.front();
            q.pop();
            vis[u] = false;
            for (register int i = 0; i < edge[u].size(); i++) {
                node *p = &edge[u][i];
                if (p->length && dis[u] + p->w < dis[p->to]) {
                    dis[p->to] = dis[u] + p->w;
                    prev[p->to] = u, pree[p->to] = i;
                    if (!vis[p->to]) q.push(p->to), vis[p->to] = true;
                }
            }
        }
        if (dis[t] == INF) break;
        register int flow = INT_MAX;
        for (register int i = t; i != s; i = prev[i])
            flow = min(flow, edge[prev[i]][pree[i]].length);
        ans.first += flow, ans.second += flow * dis[t];
        for (register int i = t; i != s; i = prev[i]) {
            node *p = &edge[prev[i]][pree[i]];
            p->length -= flow, edge[p->to][p->pa].length += flow;
        }
    }
    return ans;
}
 
#define y1 da56dh4gtf6asg
int a[10005];
int x1[10005],y1[10005];
int main () {
    int n,m,s,t;
    R(n);R(m);
    s=0,t=n+2;
    int x,y,z;
    for(int i=1;i<=n;++i) {
        R(a[i]);
        if(a[i]-a[i-1]>0)
        create(i,t,a[i]-a[i-1],0);
        else if(a[i]-a[i-1]<0) create(s,i,a[i-1]-a[i],0);
    }
    create(s, n+1, a[n],0);
    for(int i=1;i<=n;++i) {
        create(i, i+1, inf, 0);
    }
    int k;
    for(int i=1;i<=m;++i) {
    	R(k);
    	for(int j=1;j<=k;++j) {
    		R(x1[j]),R(y1[j]);
    	}
       	R(z);
       	for(int j=1;j<=k;++j)
        create(y1[j]+1,x1[j],inf,z);
    }
    cout<<getflow(s,t,t+1).second<<'\n'; 
}
