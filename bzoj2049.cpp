
#include <bits/stdc++.h>
using namespace std;
struct node* null;
const int mod = 51061;
const int N = 100011;
struct node {
    bool rev;
    node *fa, *top, *c[2];
    node():fa(null) {
        c[0] = c[1] = null;
    }
    inline void reverse() {
        rev ^= 1;
        swap(c[1], c[0]);
    }
    inline void pushdown() {
        if (rev) {
            c[0]->reverse(), c[1]->reverse(), rev = 0;
        }
    }
    inline bool relation() {
        return fa->c[1] == this;
    }
    inline void rotate(const bool f) {
        node *o = fa;
        top = o->top;
        o->pushdown(), pushdown();
        (fa = o->fa)->c[o->relation()] = this;
        (o->c[f] = c[!f])->fa = o;
        (c[!f] = o)->fa = this;
    }
    inline void splay() {
        bool f;
        node *o = fa;
        for (pushdown(); o != null; o = fa) {
            if (o->fa == null) {
                rotate(o->c[1] == this);
            } else {
                (f = o->c[1] == this) == (o->fa->c[1] == o)
                ? (o->rotate(f), rotate(f)) : (rotate(f), rotate(!f));
            }
    }
    }
    inline void expose(node * p = null) {
        splay();
        //  cout << 32;
        if (c[1] != null) {
            c[1]->top = this;
            c[1]->fa = null;
        }
        (c[1] = p)->fa = this;
    }
    inline node* access() {
        node *x = this;
        for (x->expose(); x->top; x = x->top)
            x->top->expose(x);
        return x;
    }
    inline void evert() {
        access(); splay(); reverse();
    }
    inline void link(node *f) {
        node *x = access();
        //  cout << 2313;
        x->reverse(), x->top = f;
        //  cout << 41561;
    }
    inline void cut(node *y) {
        node *x = this;
        x->expose(), y->expose();
        if (x->top == y) x->top = NULL;
        if (y->top == x) y->top = NULL;
    }
    inline node* findroot() {
        node *f = this;
        f->access(), f->splay();
        while (f->pushdown(), f->c[0] != null)f = f->c[0];
        return f;
    }
} pool[N];
inline void init() {
    null = pool;
    null->fa = null;
}
inline char nextChar() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    if (s == t) {
        t = (s = buf) + fread(buf, 1, IN_LEN, stdin);
        if (s == t) return -1;
    }
    return *s++;
}
 
inline int read() {
    static int x = 0;
    static char c;
    for (x = 0, c = nextChar(); !isdigit(c); c = nextChar());
    for (; isdigit(c); c = nextChar())
        x = (x + (4 * x) << 1) + (c ^ '0');
    return x;
}
int n, q;
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    init();
    //cout << 233;
    n = read(), q = read();
    for (register int i = 1; i <= n; i++) pool[i] = node();
    char s;
    register int x,y;
    for (register int i = 1; i <= q; i++) {
        s = nextChar(), x = read(), y = read();
        switch(s) {
            case 'C':
                (pool+x)->link(pool+y);break;
            case 'D':
                (pool+x)->cut(pool+y);break;
            case 'Q':
                puts((pool+x)->findroot()==(pool+y)->findroot()?"Yes":"No");
                break;
        }
    }
    return 0;
}
