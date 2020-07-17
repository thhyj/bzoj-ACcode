
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
int x, y, a, b, n, head = 0, tail = 1, x1[1000001], y1[1000001], ans, step[1000001];
bool map[1001][1001];
const int fx[5] = {0, 0, 1, 0, -1};
const int fy[5] = {0, 1, 0, -1, 0};
int main()
{
    cin >> x >> y >> n;
    x = x + 500; y = y + 500;
    for (int i = 1; i <= n; i++)
    {
        cin >> a >> b;
        map[a + 500][b + 500] = 1;
    }
    x1[tail] = 500;
    y1[tail] = 500;
    step[tail] = 0;
    while (head <= tail)
    {   head++;
        for (int i = 1; i <= 4; i++)
        {   int x2 = x1[head] + fx[i], y2 = y1[head] + fy[i];
            if (map[x2][y2] == 0 && x2 >= 0 && x2 <= 1000 && y2 >= 0 && y2 <= 1000)
            {   map[x2][y2] = 1;
                tail++;
                if (x2 == x && y2 == y)
                {
                    ans = tail - head;
                    cout << step[head] + 1;;
                    return 0;
                }
                x1[tail] = x2;
                y1[tail] = y2;
                step[tail] = step[head] + 1;
            }
        }
    }
    return 0;
}
