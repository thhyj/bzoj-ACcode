
#include<bits/stdc++.h>
using namespace std;
inline char read() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    if (s == t) {
        t = (s = buf) + fread(buf, 1, IN_LEN, stdin);
        if (s == t) return -1;
    }
    return *s++;
}
  
template<class T>
inline void R(T &x) {
    static char c;
    static bool iosig;
    for (iosig = false, c = read(); !isdigit(c); c = read()) {
        if (c == -1) return;
        if (c == '-') iosig = true;
    }
    for (x = 0; isdigit(c); c = read())
        x = (x + (x << 2) << 1) + (c ^ '0');
    if (iosig) x = -x;
}
  
struct node {
    double w;
    int to, pa, length;
    node(int to, int length, double w, int pa): to(to), length(length), w(w), pa(pa) {}
    node() {}
};
const int inf = 2100000000;
std::vector<node>q[305];
int b[105][105], a[105][105];
int s, t, prev[305], pree[305];
double dis[305];
bool vis[305];
inline void create(int x, int y, int length, double w) {
    q[x].push_back(node(y, length, w, q[y].size()));
    q[y].push_back(node(x, 0, -w, q[x].size() - 1));
}
inline pair<int, double> feiyong(int n) {
    pair<int , double> ans = (pair<int , double>) {0, 0};
    int j;
    node *p;
    while (1) {
        //memset(dis, 15,sizeof(dis));
        //cout<<"dis[0]="<<dis[0]<<'\n';
        for (int i = 1; i <= n; ++i) dis[i] = inf;
        memset(vis, 0 , sizeof(vis));
        queue<int> que;
        que.push(s);
        vis[s] = 1;
        while (!que.empty()) {
            j = que.front();
            que.pop();
            vis[j] = 0;
            for (int i = 0; i < q[j].size(); ++i) {
                p = &q[j][i];
                if (dis[p->to] > dis[j] + p->w && p->length) {
                    dis[p->to] = dis[j] + p->w;
                    prev[p->to] = j;
                    pree[p->to] = i;
                    vis[p->to] = 1;
                    que.push(p->to);
                }
            }
        }
        if (dis[t] == inf) break;
        //  cout<<"dis[t]="<<dis[t]<<'\n';
        double flow = INT_MAX;
        for (register int i = t; i ^ s; i = prev[i]) {
            flow = min(flow, (double)q[prev[i]][pree[i]].length);
        }
        ans.first += flow, ans.second += flow * (double)dis[t];
        for (register int i = t; i ^ s; i = prev[i]) {
            p = &q[prev[i]][pree[i]];
            p->length -= flow;
            q[p->to][p->pa].length += flow;
        }
    }
    return ans;
}
const double eps=1e-8;
int main() {
   // freopen("ball.in", "r", stdin);
  //  freopen("ball.out", "w", stdout);
    int n;
    R(n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            R(a[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            R(b[i][j]);
        }
    }
    double l = 0, r = 10000, mid;
    s = 0; t = n + 1 + n;
    pair <int, double>ans;
   while(r-l>eps){
        mid = (l + r) / 2;
    //  printf("l=%lf, r=%lf, mid=%lf\n",l, r, mid);
        memset(q, 0 , sizeof(q));
        for (int j = 1; j <= n; ++j) {
            create(s, j, 1, 0);
        }
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                create(j, k + n, 1, (double)b[j][k] * mid - a[j][k]);
            }
        }
        for (int j = 1; j <= n; ++j) {
            create(j + n, t, 1, 0);
        }
        ans = feiyong(t + 1);
        if(ans.second >= 0) r = mid;
        else l = mid;
    }
    printf("%0.6lf\n",(double)mid);
}
