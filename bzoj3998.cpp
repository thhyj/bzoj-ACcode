
#include <bits/stdc++.h>
using namespace std;
char s[500005];
struct  node {
	int max, nxt[26], fa, siz, endpossize;
	node(int max, int fa) : max(max), fa(fa) {}
	node() {}
} tr[1000005];
const int root = 1;
int cur;
inline int extend (const int &c, int p) {
	int np = ++cur;
	tr[np] = node(tr[p].max + 1, 0);
	while (p && !tr[p].nxt[c]) tr[p].nxt[c] = np, p = tr[p].fa;
	if (!p) {
		tr[np].fa = root;
	} else {
		int q = tr[p].nxt[c];
		if (tr[q].max == tr[p].max + 1) {
			tr[np].fa = q;
		} else {
			int nq = ++cur;
			tr[nq] = node(tr[p].max + 1, tr[q].fa);
			memcpy(tr[nq].nxt, tr[q].nxt, sizeof(tr[q].nxt));
			tr[np].fa = tr[q].fa = nq;
			while (p && tr[p].nxt[c] == q) tr[p].nxt[c] = nq, p = tr[p].fa;
		}
	}
	return np;
}
vector<int>q[1000005];
vector< pair<int, int> > edge[1000005];
int n;
inline void init() {
	for (int i = 1; i <= cur; ++i) {
		tr[i].siz = 1;
		q[tr[i].max].push_back(i);
	}
	for (int i = n; i>=0; --i) {
		for (int j = 0; j < q[i].size(); ++j) {
			int p = q[i][j];
			for (int k = 0; k < 26; ++k) {
				if (tr[p].nxt[k]) {
					edge[p].push_back((pair<int, int>(tr[p].nxt[k], k)));
					tr[p].siz += tr[tr[p].nxt[k]].siz;
				}
			}
		}
	}
}
inline void init1() {
	int now = root;
	char *a = ::s;
	for (int i = 0; i < n; ++i) {
		now = tr[now].nxt[*a++ -'a'];
		tr[now].endpossize++;
	}
	for (int i = 1; i <= cur; ++i) q[tr[i].max].push_back(i);
	for (int i = n; i; --i) {
		for (int j = 0; j < q[i].size(); ++j) {
			int p = q[i][j];
			tr[tr[p].fa].endpossize += tr[p].endpossize;
		}
	}
	tr[1].endpossize=0;
	for (int i = 1; i <= cur; ++i) tr[i].siz=tr[i].endpossize;
	for (int i = n; i >= 0; --i) {
		for (int j = 0; j < q[i].size(); ++j) {
			int p = q[i][j];
			for (int k = 0; k < 26; ++k) {
				if (tr[p].nxt[k]) {
					edge[p].push_back((pair<int, int>(tr[p].nxt[k], k)));
					tr[p].siz += tr[tr[p].nxt[k]].siz;
				}
			}
		}
	}
	
}
int len;
inline void dfs(const int &now, int left) {
	if (--left == 0) return;
	for (int i = 0; i < edge[now].size(); ++i) {
		pair<int, int> *p = &edge[now][i];
		//cout<<"p->second="<<p->second<<'\n';
		if (tr[p->first].siz < left) left -= tr[p->first].siz;
		else {
			putchar('a' + p->second);
			dfs(p->first, left);
			break;
		}
	}
}
inline void dfs1(const int &now, int left) {
	if ((left-=tr[now].endpossize)<=0) return;
	for (int i = 0; i < edge[now].size(); ++i) {
		pair<int, int> *p = &edge[now][i];
		if (tr[p->first].siz < left) left -= tr[p->first].siz;
		else {
			putchar('a' + p->second);
			dfs1(p->first, left);
			break;
		}
	}
}
int main () {
	   int size = 80 << 20; 
    char *p = (char*)malloc(size) + size;
    __asm__ __volatile__("movl %0, %%esp\n" :: "r"(p));
	scanf("%s", s);
	int q;
	int k;
	int last = 1;
	cur = 1;
	n = strlen(s);
	for (int i = 0; i < n; ++i) {
		last = extend(s[i] - 'a', last);
	}
	int t;
	scanf("%d", &t);
	scanf("%d", &k);
	if (!t) {
		init();
		if(k>tr[root].siz) {
			printf("-1");
			return 0;
		} 
		dfs(root, k + 1);
	} else {
		init1();
		if(k>tr[root].siz) {
			printf("-1");
			return 0;
		} 
		dfs1(root, k);
	}
	return 0;
}
