
#include <cstdio>
#include <set>
#include <map>
#include <iostream>
using namespace std;

const int max_n = 100000 + 10;
const int max_m = 30 + 2;

int n, m, read_num, ans = 0;
int sum[max_n][max_m], t;
#define rm read_num

map<string, int> q;
map<string, int>::iterator it;


inline int get(int k,int p) //
{
	return (k >> (p - 1))&1;
}

char str[200];
inline string change(int *a)
{
	t = 0;
	for (int i = m; i > 1; -- i)
	{
		int tmp = a[i];
		if (!tmp)	str[t ++] = '0';
		while (tmp)
		{
			str[t ++] = tmp % 10 +'0';
			tmp /= 10;
		}
	}
	str[t] = '\0';
	return str;
}

inline void read(int &x)
{
       char ch;
       while (ch=getchar(),ch>'9' || ch<'0') ;
       x=ch-48;
       while (ch=getchar(),ch<='9' && ch>='0') x=x*10+ch-48; 
}

int main()
{
	read(n);	read(m);
	for (int i = 1; i <= n; ++ i)
	{
		read(rm);
		for (int j = 1; j <= m; ++ j)	sum[i][j] = get(rm, j);
		for (int j = 1; j <= m; ++ j)	sum[i][j] += sum[i - 1][j];
	}
	for (int i = 1; i <= n; ++ i)	
	{
		for (int j = 2; j <= m; ++ j)
			sum[i][j] -= sum[i][1];
		sum[i][1] = 0;
	}
	for (int i = n; i >= 0; -- i)
	{
		if ((it = q.find(change(sum[i]))) != q.end())	ans = max(ans, (*it).second - i);
		else q[change(sum[i])] = i;
	}
	printf("%d\n", ans);
	return 0;
}
