
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
using namespace std;
char ch;
inline void R(int &v)
{
	v = 0;
	do
	{
		ch = getchar();
	} while (!isdigit(ch));
	while (isdigit(ch))
	{
		v = (v << 1) + (v << 3) + (ch^'0');
		ch = getchar();
	}
}
int a[100001], q[100001];
int main()
{
	int n;
	R(n);
	for (int i = 1; i <= n; ++i)
	{
		R(a[i]);
	}
	int len = 1;
	q[1] = a[1];
	int l, r, mid;
	for (int i = 2; i <= n; ++i)
	{
		if (a[i] > q[len])q[++len] = a[i];
		else
		{
			l = 0, r = len + 1;
			while (l < r - 1)
			{
				mid = l + r >> 1;
				if (q[mid] >= a[i])r = mid;
				else
					l = mid;
			}
			q[r] = a[i];
		}
	}
	cout << len;
	return 0;
}
