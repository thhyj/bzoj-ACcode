
#include <cstdio>
#include <set>
using namespace std;
struct Seg { int l, r; } a[100005];
set<int> ss;
int main() {
    int t, tot = 0, l, r, del; char op[8];
    set<int>::iterator x;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", op);
        if (op[0] == 'A') {
            scanf("%d%d", &l, &r);
            // Case 1
            for (del = 0; ; ) {
                x = ss.lower_bound(l);
                if (x != ss.end() && *x <= r)
                    ss.erase(a[*x].l), ss.erase(a[*x].r), ++del;
                else break;
            }
            // Case 2
            x = ss.lower_bound(r + 1);
            if (x != ss.end() && a[*x].l < l && a[*x].r > r)
                    ss.erase(a[*x].l), ss.erase(a[*x].r), ++del;
            a[l] = a[r] = (Seg) { l, r };
            ss.insert(l); ss.insert(r);
            tot += 1 - del;
            printf("%d\n", del);
        } else printf("%d\n", tot);
    }
    return 0;
}
