
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
inline void R(int &v)
{
    v = 0;
    char c = 0;
    bool p = true;
    while (c > '9' || c < '0')
    {
        if (c == '-')
        {
            p = false;
        }
        c = cin.get();
    }
    while (c >= '0' && c <= '9')
    {
        v = (v << 3) + (v << 1) + c - '0';
        c = cin.get();
    }
    if (p == false)
    {
        v = -v;
    }
}
int const fx[5] = {0, 0, 1, 0, -1};
int const fy[5] = {0, 1, 0, -1, 0};
int m, hh[1001][1001], way[1001][1001], ti[1000001];
int head = 0, tail = 1, x, y, x1[1000001], y2[1000001];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen("meteor.in","r",stdin);
    //freopen("meteor.out","w",stdout);
    memset(hh, 127, sizeof(hh));
    R(m);
    int a, b, c;
    for (int i = 1; i <= m; i++)
    {
        R(a); R(b); R(c);
        if (hh[a][b] > c)
            hh[a][b] = c;
        if (a - 1 >= 0 && hh[a - 1][b] > c)
            hh[a - 1][b] = c;
        if (a + 1 <= 500 && hh[a + 1][b] > c)
            hh[a + 1][b] = c;
        if (b - 1 >= 0 && hh[a][b - 1] > c)
            hh[a][b - 1] = c;
        if (b + 1 <= 500 && hh[a][b + 1] > c)
            hh[a][b + 1] = c;
    }
    while (head <= tail)
    {   head++;
        for (int i = 1; i <= 4; i++)
        {
            x = x1[head] + fx[i];
            y = y2[head] + fy[i];
            if (ti[head] + 1 < hh[x][y] && way[x][y] == 0 && x >= 0 && x <= 500 && y >= 0 && y <= 500)
            {
                tail++;
                x1[tail] = x;
                y2[tail] = y;
                ti[tail] = ti[head] + 1;
                way[x][y] = 1;
                if (hh[x][y] > 2000000000)
                {
                    cout << ti[tail];
                    return 0;
                }
            }
        }
    }
    cout << "-1";
    return 0;
}
