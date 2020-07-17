
#include <cstdio>
#include <ctime>
#include <queue>
#include <algorithm>
#include <vector>
#include <stack>

const int MAXN = 20000;
const int MAXN_LOG = 14;
const int MAXL = 60;

struct Node {
    std::vector<Node *> adj;
    Node *fa, *ch, *top;
    bool vis;
    int dep, size, dfn;
    long long w;
} N[MAXN + 1];

inline void addEdge(int u, int v) {
    N[u].adj.push_back(&N[v]);
    N[v].adj.push_back(&N[u]);
}

struct LinearBasis {
    // std::vector<long long> v;
    long long a[MAXL + 1];

    LinearBasis() {
        std::fill(a, a + MAXL + 1, 0);
    }

    LinearBasis(long long *x, int n) {
        build(x, n);
    }

    void insert(long long t) {
        for (int j = MAXL; j >= 0; j--) {
            if (!t) return;
            if (!(t & (1ll << j))) continue;

            if (a[j]) t ^= a[j];
            else {
                for (int k = 0; k < j; k++) if (t & (1ll << k)) t ^= a[k];
                for (int k = j + 1; k <= MAXL; k++) if (a[k] & (1ll << j)) a[k] ^= t;
                a[j] = t;
                break;
            }
        }
    }

    void build(long long *x, int n) {
        std::fill(a, a + MAXL + 1, 0);

        for (int i = 1; i <= n; i++) {
            insert(x[i]);
        }
    }

    long long queryMax() {
        long long res = 0;
        for (int i = 0; i <= MAXL; i++) res ^= a[i];
        return res;
    }

    void mergeFrom(const LinearBasis &other) {
        for (int i = 0; i <= MAXL; i++) insert(other.a[i]);
    }

    static LinearBasis merge(const LinearBasis &a, const LinearBasis &b) {
        LinearBasis res = a;
        for (int i = 0; i <= MAXL; i++) res.insert(b.a[i]);
        return res;
    }
};

struct SegT {
    int l, r, mid;
    SegT *lc, *rc;
    LinearBasis lb;

    SegT(int l, int r, SegT *lc, SegT *rc) : l(l), r(r), mid(l + (r - l) / 2), lc(lc), rc(rc), lb(LinearBasis::merge(lc->lb, rc->lb)) {}
    SegT(int l, int r, SegT *lc, SegT *rc, long long x) : l(l), r(r), mid(l + (r - l) / 2), lc(lc), rc(rc), lb(&x - 1, 1) {}

    LinearBasis query(int l, int r) {
        if (l <= this->l && r >= this->r) return lb;
        else if (r <= mid) return lc->query(l, r);
        else if (l > mid) return rc->query(l, r);
        else return LinearBasis::merge(lc->query(l, r), rc->query(l, r));
    }

    static SegT *build(int l, int r, long long *a) {
        if (l == r) return new SegT(l, r, NULL, NULL, a[l]);
        else {
            int mid = l + (r - l) / 2;
            return new SegT(l, r, build(l, mid, a), build(mid + 1, r, a));
        }
    }
} *seg;

int n, root;

inline void split() {
    std::stack<Node *> s;
    s.push(&N[root]);
    N[root].dep = 1;

    while (!s.empty()) {
        Node *v = s.top();
        if (!v->vis) {
            v->vis = true;
            for (Node **p = &v->adj.front(), *u = v->adj.front(); p <= &v->adj.back(); u = *++p) {
                if (!u->dep) {
                    u->fa = v;
                    u->dep = v->dep + 1;
                    s.push(u);
                }
            }
        } else {
            v->size = 1;
            for (Node **p = &v->adj.front(), *u = v->adj.front(); p <= &v->adj.back(); u = *++p) {
                v->size += u->size;
                if (!v->ch || v->ch->size < u->size) v->ch = u;
            }
            s.pop();
        }
    }

    for (int i = 1; i <= n; i++) N[i].vis = false;

    int ts = 0;
    static Node *seq[MAXN + 1];
    s.push(&N[root]);
    while (!s.empty()) {
        Node *v = s.top();
        if (!v->vis) {
            v->vis = true;

            v->top = (!v->fa || v != v->fa->ch) ? v : v->fa->top;
            seq[v->dfn = ++ts] = v;
            for (Node **p = &v->adj.front(), *u = v->adj.front(); p <= &v->adj.back(); u = *++p) {
                if (u != v->fa && u != v->ch) {
                    s.push(u);
                }
            }
            if (v->ch) s.push(v->ch);
        } else {
            s.pop();
        }
    }

    static long long x[MAXN + 1];
    for (int i = 1; i <= n; i++) x[i] = seq[i]->w;

    seg = SegT::build(1, n, x);
}

inline long long query(int u, int v) {
    Node *a = &N[u], *b = &N[v];
    LinearBasis lb;
    while (a->top != b->top) {
        if (a->top->dep < b->top->dep) std::swap(a, b);
        lb.mergeFrom(seg->query(a->top->dfn, a->dfn));
        a = a->top->fa;
    }
    if (a->dep > b->dep) std::swap(a, b);
    lb.mergeFrom(seg->query(a->dfn, b->dfn));
    return lb.queryMax();
}

/*
int f[MAXN + 1][MAXN_LOG + 1], logn;
LinearBasis g[MAXN + 1][MAXN_LOG + 1];

inline void prepare() {
    std::queue<Node *> q;
    q.push(&N[root]);
    N[root].dep = 1;

    f[root][0] = root;
    g[root][0] = LinearBasis(&N[root].w - 1, 1);

    while (!q.empty()) {
        Node *v = q.front();
        q.pop();

        for (Node **p = &v->adj.front(), *u = v->adj.front(); p <= &v->adj.back(); u = *++p) {
            if (!u->dep) {
                u->dep = v->dep + 1;
                f[u - N][0] = v - N;

                long long a[2];
                a[0] = u->w, a[1] = v->w;
                g[u - N][0] = LinearBasis(a - 1, 2);

                q.push(u);
            }
        }
    }

    while ((1 << (logn + 1)) <= n) logn++;

    for (int j = 1; j <= logn; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
            g[i][j] = LinearBasis::merge(g[i][j - 1], g[f[i][j - 1]][j - 1]);
        }
    }
}

inline long long query(int u, int v) {
    if (N[u].dep < N[v].dep) std::swap(u, v);

    LinearBasis lb;

    if (N[u].dep > N[v].dep) {
        for (int i = logn; i >= 0; i--) {
            if (N[f[u][i]].dep >= N[v].dep) {
                lb.mergeFrom(g[u][i]);
                u = f[u][i];
            }
        }
    }

    if (u != v) {
        for (int i = logn; i >= 0; i--) {
            if (f[u][i] != f[v][i]) {
                lb.mergeFrom(g[u][i]);
                lb.mergeFrom(g[v][i]);
                u = f[u][i];
                v = f[v][i];
            }
        }

        lb.mergeFrom(g[u][0]);
        lb.mergeFrom(g[v][0]);

        u = f[u][0];
        v = f[v][0];
    }

    lb.insert(N[u].w);
    return lb.queryMax();
}
*/

int main() {
    int q;
    scanf("%d %d", &n, &q);

    // srand((n * q) ^ 20000528);
    // root = rand() % n + 1;
    root = 1;

    for (int i = 1; i <= n; i++) scanf("%lld", &N[i].w);

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    // for (int i = 1; i <= n; i++) std::random_shuffle(N[i].adj.begin(), N[i].adj.end());

    split();
    // prepare();

    while (q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%lld\n", query(u, v));
    }

    return 0;
}
