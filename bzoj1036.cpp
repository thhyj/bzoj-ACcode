
#include <bits/stdc++.h>
using namespace std;
inline char read() {
    static const int IN_LEN = 1024 * 1024;
    static char buf[IN_LEN], *s, *t;
    if (s == t) {
        t = (s = buf) + fread(buf, 1, IN_LEN, stdin);
        if (s == t) return -1;
    }
    return *s++;
}
 
///*
template<class T>
inline bool R(T &x) {
    static char c;
    static bool iosig;
    for (c = read(), iosig = false; !isdigit(c); c = read()) {
        if (c == -1) return false;
        if (c == '-') iosig = true;
    }
    for (x = 0; isdigit(c); c = read())
        x = (x << 3) + (x << 1) + (c ^ '0');
    if (iosig) x = -x;
    return true;
}
//*/
 
const int OUT_LEN = 1024 * 1024;
char obuf[OUT_LEN], *oh = obuf;
 
inline void write_char(char c) {
    if (oh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), oh = obuf;
    *oh++ = c;
}
 
template<class T>
inline void W(T x) {
    static int buf[30], cnt;
    if (!x) write_char(48);
    else {
        if (x < 0) write_char('-'), x = -x;
        for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
        while (cnt) write_char(buf[cnt--]);
    }
}
 
inline void write(bool flag) {
    if (flag)
        write_char('Y'), write_char('e'), write_char('s'), write_char('\n');
    else write_char('N'), write_char('o'), write_char('\n');
}
 
inline void flush() { fwrite(obuf, 1, oh - obuf, stdout); }
vector<int>q[30005];
inline void create(const int &x, const int &y) {
	q[x].push_back(y);
	q[y].push_back(x);
}
const int N = 1000005;
struct node *null;
struct node {
    node *fa, *top, *c[2];
    int val, ma, sum;
    bool rev;
    node(): fa(null), ma(INT_MIN), top(NULL) {
        c[0] = c[1] = null;
    }
    inline void reverse () {
        rev ^= 1;
        swap(c[0], c[1]);
    }
    inline void updata() {
        ma = max(max(c[1]->ma, c[0]->ma), val);
        sum = c[1]->sum + c[0]->sum + val;
    }
    inline void pushdown() {
        if (rev) {
            c[1]->reverse(), c[0]->reverse();
            rev = 0;
        }
    }
    inline bool relation() {
        return fa->c[1] == this;
    }
    inline void rotate(const bool &f) {
        node *o = fa;
        top = o->top;
        o->pushdown(), pushdown();
        (fa = o->fa)->c[o->relation()] = this;
        (o->c[f] = c[!f])->fa = o;
        (c[!f] = o)->fa = this;
        o->updata();
    }
    inline void splay() {
        bool f;
        node *o = fa;
        //cout << "pushdown\n";
        for (pushdown(); o != null; o = fa) {
            if (o->fa == null) {
                rotate(o->c[1] == this);
            } else {
                (f = o->c[1] == this) == (o->fa->c[1] == o) ?
                (o->rotate(f), rotate(f)) :
                (rotate(f), rotate(!f));
            }
        }
        updata();
    }
    inline void expose(node* p = null) {
        //  cout << 9 << '\n';
        splay();
        if (c[1] != null) {
            c[1]->fa = null;
            c[1]->top = this;
        }
        (c[1] = p)->fa = this;
        updata();
    }
       inline node *access() {
        node *x = this;
        for (x->expose(); x->top; x = x->top)
            x->top->expose(x);
        return x;
    }
    inline void link(node *f) {
        node *x = access();
        x->reverse(), x->top = f;
    }
    inline void evert() {
        access(), splay(), reverse();
    }
    inline void split(node *y) {
        y->evert(), access(), splay();
    }
    inline void modify(const int &v) {
        splay();
        val = v;
        updata();
    }
    inline void cut (node *y) {
        node *x = this;
        x->expose(), y->expose();
        if (x->top == y) x->top = NULL;
        if (y->top == x) y->top = NULL;
    }
    inline void init(const int v) {
        val = sum = ma = v;
    }
} pool[N];
inline void init() {
    null = pool;
    null->fa = null;
    null->sum = 0;
    null->ma = null->val = INT_MIN;
}
inline void dfs(const int &x, node *f) {
	(x+pool)->top = f;
	for(int i=0;i<q[x].size();++i) {
		if((q[x][i]+pool)!=f) {
			dfs(q[x][i],x+pool);
		}
	}
}
int x[30005],y[30005];
int main() {
    //freopen("in.in", "r", stdin);
    //freopen("bzoj_1036.in","r",stdin);
    //freopen("bzoj_1036.out","w",stdout);
    int n;
    init();
    R(n);
    int q;
    for (register int i = 1; i <= n; i++) pool[i] = node();
    for (int i = 1; i < n; ++i) {
    	R(x[i]),R(y[i]);
	//	(x+pool)->top = y;
       // create(x,y);
    }	
	dfs(1,NULL);
    int t;
    for (int i = 1; i <= n; ++i) {
        R(t);
        (pool + i)->init(t);
    }
    for (int i = 1; i < n; ++i) {
       (x[i] + pool)->link(y[i] + pool);
    }
    R(q);
    char c;
    int x,y;
    for (int i = 1; i <= q; ++i) {
        c = read();
        while (!isupper(c)) c = read();
        if (c == 'C') {
            R(x);
            R(y);
            (pool + x)->modify(y);
        } else {
            c = read();
            if (c == 'S') {
                R(x);
                R(y);
                (x + pool)->split(y + pool);
                W((x + pool)->sum);
                write_char('\n');
            } else {
                R(x);
                R(y);
                (x + pool)->split(y + pool);
                W((x + pool)->ma);
                write_char('\n');
            }
        }
    }
    flush();
}
