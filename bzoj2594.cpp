
#include <bits/stdc++.h>
using namespace std;
inline char read() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
    return s == t ? -1 : *s++;
}
template<typename T>
inline void R(T &x) {
    static char c;
    static bool iosig;
    for (c = read(), iosig = false; !isdigit(c); c = read()) {
        if (c == -1) return;
        c == '-' ? iosig = true : 0;
    }
    for (x = 0; isdigit(c); c = read())
        x = (x + (x << 2) << 1) + (c ^ '0');
    iosig ? x = -x : 0;
}
inline int read(char *buf) {
    register int s = 0;
    register char c;
    while (c = read(), isspace(c) && c != -1);
    if (c == -1) {
        *buf = '\0';
        return -1;
    }
    do buf[s++] = c; while (c = read(), !isspace(c) && c != -1);
    buf[s] = '\0';
    return s;
}
inline void read(double &x) {
    static char buf[30];
    read(buf), x = atof(buf);
}
const int OUT_LEN = 1000000;
char obuf[OUT_LEN], *oh = obuf;
inline void print(char c) {
    oh == obuf + OUT_LEN ? (fwrite(obuf, 1, OUT_LEN, stdout), oh = obuf) : 0;
    *oh++ = c;
}
template<typename T>
inline void print(T x) {
    static int buf[30], cnt;
    if (x == 0) {
        print('0');
    } else {
        x < 0 ? (print('0'), x = -x) : 0;
        for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
        while (cnt) print((char)buf[cnt--]);
    }
}
inline void flush() {
    fwrite(obuf, 1, oh - obuf, stdout);
}
struct node *null;
struct node {
    node *top, *c[2], *id, *fr, *to;
    bool rev;
    int ma, v;
    node *fa;
    node() : fa(null), top(NULL), rev(0), ma(0), v(0), id(this) {c[0] = c[1] = null;}
    inline void reverse() {
        rev ^= 1;
        swap(c[0], c[1]);
    }
    inline void updata() {
        c[0]->ma > c[1]->ma ?
        (v > c[0]->ma ? (ma = v, id = this) : (ma = c[0]->ma, id = c[0]->id)) :
        (v > c[1]->ma ? (ma = v, id = this) : (ma = c[1]->ma, id = c[1]->id));
    }
    inline void pushdown() {
        if (rev) {
            c[0]->reverse();
            c[1]->reverse();
            rev = 0;
        }
    }
    inline bool relation () {
        return fa->c[1] == this;
    }
    inline void rotate(bool f) {
        node *o = fa;
        top = o->top;
        o->pushdown(), pushdown();
        (fa = o->fa)->c[o->fa->c[1] == o] = this;
        (o->c[f] = c[!f])->fa = o;
        (c[!f] = o)->fa = this;
        o->updata();
    }
    inline void splay() {
        node *o = fa;
        bool f;
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
    inline void expose(node *p = null) {
        splay();
        //puts("done");
        if (c[1] != null) {
            c[1]->fa = null;
            c[1]->top = this;
        }
        (c[1] = p)->fa = this;
        updata();
    }
    inline void access() {
        node *x = this;
        for (x->expose(); x->top; x = x->top) {
            x->top->expose(x);
        }
    }
    inline void evert() {
        access();
        splay();
        reverse();
    }
    inline void link(node *y) {
        y->evert();
        y->top = this;
    }
    inline void cut(node *y) {
        node *x = this;
        x->expose();
        y->expose();
        if (x->top == y) x->top = NULL;
        if (y->top == x) y->top = NULL;
    }
    inline void split(node *y) {
        y->evert();
        access();
        splay();
    }
    inline void modify(int v) {
        splay();
        ma = v;
        updata();
    }
} pool[1100005];
inline void init() {
    null = pool;
    null->rev = null->ma = null->v = 0;
    null->fa = null->c[1] = null->c[0] = null->id = null;
    null->top = NULL;
}
int tot;
struct ege {
    int to, length, fr, id;
    ege(int fr, int to, int length, int id): fr(fr), to(to), length(length), id(id) {}
    ege() {}
} edge[1100005];
int first[100005];
struct eg {
    int to, length;
    eg(int to, int length): to(to), length(length) {}
    eg() {}
};
std::vector<eg> q[100005];
inline void create1(int x, int y, int z) {
    q[x].push_back(eg(y, z));
    q[y].push_back(eg(x, z));
}
inline void create(int x, int y, int z) {
    edge[++tot] = ege(x, y, z, tot);
    // edge[++tot] = ege(y, x, z, tot);
}
map<int, bool>mp[100005];
int n, m, t;
int fa[100005];
inline int getfather(int x) {
    return fa[x] == x ? x : (fa[x] = getfather(fa[x]));
}
inline bool cmp(const ege&a , const ege&b) {
    return a.length < b.length;
}
struct query {
    int kind, x, y;
} que[100005];
int cnt;
inline void dfs(int x, int fa) {
    eg *p;
 //   printf("x=%d\n",x);
    for (int i = 0; i < q[x].size(); ++i) {
        p = &q[x][i];
        if (p->to ^ fa) {
            ++cnt;
            (pool + cnt)->fr = pool + x;
            (pool + cnt)->to = pool + p->to;
            (pool + cnt)->id = pool + cnt;
            //(pool + cnt)->id->ma = (pool + cnt)->id->v = 0;
            (pool + cnt)->ma = (pool + cnt) -> v = p->length;
            //(pool + cnt)->top = pool + x;
         //   cout << "x=" << x << " p->to = " << p->to << " cnt=" << cnt << " (pool + cnt) = " << (pool + cnt) << " (pool + cnt)->ma = " << (pool + cnt)->ma << '\n';
            //(pool + x) ->link(pool + cnt);
            (pool + cnt) -> top = pool + x;
            (pool + p->to)->top = pool + cnt;
            //(pool + cnt) -> link(pool + p->to);
            dfs(p->to, x);
        }
    }
}
int ret;
int ans[100005];
map<int, int>duan[100005];
int main() {
 //  freopen("tube.in", "r", stdin);
  // freopen("tube.out","w",stdout);
    init();
    R(n), R(m), R(t);
    for (int i = 1; i <= n + m; ++i) {
        pool[i] = node();
    }
    int x, y, z;
    for (int i = 1; i <= m; ++i) {
        R(x), R(y), R(z);
        if (x > y) swap(x, y);
        create(x, y, z);
        duan[x][y] = z;
    }
    sort(edge + 1, edge + tot + 1, cmp);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    int kind;
    for (int i = 1; i <= t ; ++i) {
        R(que[i].kind);
        switch (que[i].kind) {
        case 1: R(que[i].x), R(que[i].y); break;
        case 2: R(que[i].x), R(que[i].y);
            if (que[i].x > que[i].y) swap(que[i].x, que[i].y);
            mp[que[i].x][que[i].y] = 1; break;
        }
    }
    cnt = n;
    for (int i = 1; i <= tot; ++i) {
        x = edge[i].fr, y = edge[i].to;
        if (mp[x].find(y) == mp[x].end()) {
            if (getfather(x) ^ getfather(y)) {
                fa[fa[x]] = fa[y];
                create1(x, y, edge[i].length);
            }
        }
    }
    dfs(1, 1);
    int temp;
  //  for (int i = 1; i <= n; ++i) {
  ///      cout << "(pool+i) = " << (pool + i) << " (pool + i)->ma = " << (pool + i)->ma << '\n';
  //  }
    // (pool + 1)->evert();
    //  (pool + 4)->access();
    //  (pool + 4)->splay();
    //  for (int i = 1; i <= cnt; ++i) {
    //    cout << "pool + " << i << "= " << pool + i << " (pool +" << i << ")->fa = " << (pool + i)->fa << " relation() = " << (pool + i)->relation() << '\n';
    // }
    node *te;
    for (int i = t; i ; --i) {
        x = que[i].x, y = que[i].y;
        (pool + x)->split(pool + y); temp = (pool + x)->ma;te = (pool + x)->id;
        //   printf("i = %d, temp = %d, duan[%d][%d] = %d\n", i, temp, x, y, duan[x][y]);
        //    cout << "(pool + x)->id = " << (pool + x)->id << '\n';
        //   cout << "(pool + x)->id->fr = " << (pool + x)->id->fr << '\n';
        //   cout << "(pool + x)->id->to = " << (pool + x)->id->to << '\n';
        switch (que[i].kind) {
        case 1: ans[++ret] = temp; break;
        case 2: if (x > y)swap(x, y);
            if (temp > duan[x][y]) {
                //  (pool + cnt)->id->ma = (pool + cnt)->id->v = 0;
                (te->fr)->cut(te);
                //      puts("done");
                //if(te->c[1]!=null)
                (te->to)->cut(te);
                ++cnt;
                (pool + x)-> link((pool + cnt));
                (pool + y)-> link((pool + cnt));
                (pool + cnt)->fr = pool + x;
                (pool + cnt)->to = pool + y;
                (pool + cnt)->splay();
                (pool + cnt)->updata();
                (pool + cnt)->ma = (pool + cnt) -> v = duan[x][y];

            }
            break;
        }
    }
    for (int i = ret; i; i--) {
    	print(ans[i]);
    	print('\n');
    }
    flush(); 
    return 0;
}
