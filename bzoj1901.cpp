
#include <bits/stdc++.h>
using namespace std;
inline void read(int &v) {
	static char ch;
	v = 0;
	bool p = 0;
	do {
		ch = getchar();
		if (ch == '-') p = 1;
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		v = (v + (v << 2) << 1) + (ch^'0');
		ch = getchar();
	}
	if (p) v = -v;
}
struct node {
	int son[2], sum;
} tr[8000005];
int root[50005], A[50005], B[50005], L[50005], R[50005];
int a[50005];
bool kind[50005];
int num[50005];
int top, tot;
int lisan[50006];
inline int lowbit(int x) {
	return x & (-x);
}
int find(int x)
{
	int l = 1, r = tot, mid;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (lisan[mid] < x)l = mid + 1;
		else r = mid - 1;
	}
	return l;
}
int sz;
void modify(int prev, int &now , int l, int r, int w, int x)
{
	if(!now)
	now = ++sz;
	tr[now].sum = tr[prev].sum + x; tr[now].son[0] = tr[prev].son[0]; tr[now].son[1] = tr[prev].son[1];
	if (l == r)  return;
	int mid = (l + r) >> 1;
	if (w <= mid)  modify(tr[prev].son[0], tr[now].son[0], l, mid, w, x);
	else  modify(tr[prev].son[1], tr[now].son[1], mid + 1, r, w, x);
}
int a1,b1;
int K[50005];
int query(int l, int r, int k)
{
	if (l == r)  return l;
	int i, suml = 0, sumr = 0;
	for (i = 1; i <= a1; i++)  suml += tr[tr[L[i]].son[0]].sum;
	for (i = 1; i <= b1; i++)  sumr += tr[tr[R[i]].son[0]].sum;
	int mid = (l + r) >> 1;
	if (sumr - suml >= k)
	{
		for (i = 1; i <= a1; i++)  L[i] = tr[L[i]].son[0];
		for (i = 1; i <= b1; i++)  R[i] = tr[R[i]].son[0];
		return query(l, mid, k);
	}
	else
	{
		for (i = 1; i <= a1; i++)  L[i] = tr[L[i]].son[1];
		for (i = 1; i <= b1; i++)  R[i] = tr[R[i]].son[1];
		return query(mid + 1, r, k - (sumr - suml));
	}
}
int main () {
	int n, m;
	read(n), read(m);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		num[++top] = a[i];
	}
	char s[10];
	for (int i = 1; i <= m; ++i) {
		scanf("%s", s);
		read(A[i]), read(B[i]);
		if (s[0] == 'Q'){read(K[i]);kind[i] = 1;}
		else num[++top] = B[i];
	}
	sort(num + 1, num + top + 1);
	lisan[++tot] = num[1];
	for (int i = 2; i <= top; i++)
		if (num[i] != num[i - 1])
			lisan[++tot] = num[i];
	for (int i = 1; i <= n; i++)
	{
		int t = find(a[i]);
		for (int j = i; j <= n; j += lowbit(j))
			modify(root[j], root[j], 1, tot, t, 1);
	}
	for (int i = 1; i <= m; i++)
		if (kind[i])
		{
			a1 = 0; b1 = 0; A[i]--;
			for (int j = A[i]; j > 0; j -= lowbit(j))
				L[++a1] = root[j];
			for (int j = B[i]; j > 0; j -= lowbit(j))
				R[++b1] = root[j];
			printf("%d\n", lisan[query(1, tot, K[i])]);
		}
		else
		{
			int t = find(a[A[i]]);
			for (int j = A[i]; j <= n; j += lowbit(j))
				modify(root[j], root[j], 1, tot,  t, -1);
			a[A[i]] = B[i];
			t = find(B[i]);
			for (int j = A[i]; j <= n; j += lowbit(j))
				modify(root[j], root[j], 1, tot, t, 1);
		}
	return 0;
}
