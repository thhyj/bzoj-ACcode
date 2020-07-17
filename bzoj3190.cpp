
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
#include<vector>
#define N 20005
#define double long double
#define inf 1e100
using namespace std;
int n;
const double eps = 1e-20;
struct point//  点&向量
{
    double x, y;
    point() {};
    point(double _x, double _y)
    {
        x = _x; y = _y;
    }
} p[N];
// 点减点=向量
point operator - (point a, point b) {return point(a.x - b.x, a.y - b.y);}
// 向量+向量=向量 点+向量=点
point operator + (point a, point b) {return point(a.x + b.x, a.y + b.y);}
// 向量数乘
point operator * (point a, double b) {return point(a.x * b, a.y * b);}
point operator / (point a, double b) {return point(a.x / b, a.y / b);}
// 叉积
double cross(point a, point b) {return a.x * b.y - a.y * b.x;}
int dcmp(double x)
{
    if (max(x, -x) < eps)return 0;
    if (x < 0)return -1;
    return 1;
}
struct line
{
    point p, v;
    int id;
    double ang;
    line() {};
    line(point pp, point vv, int _id)
    {
        id = _id;
        p = pp; v = vv;
        ang = atan2(v.y, v.x);
    }
    friend bool operator < (line aa, line bb)
    {
        return aa.ang < bb.ang;
    }
} lines[N], dep[N * 2]; int cnt;
point getpoint(line a, line b)
{
    point u = a.p - b.p;
    double t = cross(b.v, u) / cross(a.v, b.v);
    return a.p + a.v * t;
}
bool onright(point a, line b)
{
    return cross(b.v, a - b.p) < 0;
}
int tot, h, t;
void insert(line l)
{
    while (h < t && onright(p[t - 1], l))t--;
    while (h < t && onright(p[h], l))h++;
    dep[++t] = l;
    if (h < t && dcmp(dep[t].ang - dep[t - 1].ang) == 0)
    {
        t--;
        if (onright(dep[t].p, l))dep[t] = l;
    }
    if (h < t)p[t - 1] = getpoint(dep[t], dep[t - 1]);
}
void half()
{
    h = 1; t = 0;
    for (int i = 1; i <= cnt; i++)
    {
        insert(lines[i]);
    }
    while (h < t && onright(p[t - 1], dep[h]))t--;
    return ;
}
int v[N], pos[N];
int tt[N];
map<pair<int, int>, int>mp;
vector<int>ss[N];
int main()
{
//  freopen("in.txt","r",stdin);
    lines[++cnt] = line(point(inf, inf), point(-1, 0), 0);
    lines[++cnt] = line(point(0, inf), point(0, -1), 0);
    lines[++cnt] = line(point(0, 0), point(1, 0), 0);
    lines[++cnt] = line(point(inf, 0), point(0, 1), 0);
    // 保证答案为空集或一个凸多边形
    scanf("%d", &n); int mx = 0; int ans = 0;
    for (int i = 1; i <= n; i++)scanf("%d", &pos[i]), mx = max(mx, pos[i]);
    for (int i = 1; i <= n; i++)scanf("%d", &v[i]);
    for (int i = 1; i <= n; i++)
    {
//      if(i==6501){cout<<pos[i]<<' '<<v[i]<<endl;}
        if (pos[i] == mx)tt[++ans] = i;
        if (mp.find(make_pair(pos[i], v[i])) != mp.end())ss[mp[make_pair(pos[i], v[i])]].push_back(i);
        else mp[make_pair(pos[i], v[i])] = i, lines[++cnt] = line(point(0, (double)pos[i]), point(1.0, (double)v[i]), i);
    }
    sort(lines + 1, lines + cnt + 1);
    half();
    for (int i = h; i <= t; i++)
    {
        if (dep[i].id != 0)
        {
            int ttt = dep[i].id;
            if (pos[ttt] != mx)tt[++ans] = ttt;
            for (int j = 0; j < ss[ttt].size(); j++)
            {
                if (pos[ss[ttt][j]] != mx)
                {
                    tt[++ans] = ss[ttt][j];
                }
            }
        }
    }
    printf("%d\n", ans);
    sort(tt + 1, tt + ans + 1);
    for (int i = 1; i < ans; i++)printf("%d ", tt[i]);
    printf("%d", tt[ans]);
    return 0;
}
