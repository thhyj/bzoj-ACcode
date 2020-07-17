
#include <cstdio>
#include <iostream>
using namespace std;
long long s, t, p, q, L;
int Gcd(int a, int b) { return b ? Gcd(b, a % b) : a; }
long long exGcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) return x = 1, y = 0, a;
    long long r = exGcd(b, a % b, y, x);
    y -= (a / b) * x;
    return r;
}

int main() {
    cin >> s >> t >> p >> q >> L;
    long long a = (p - q + L) % L, b = L, c = (t - s + L) % L;
    long long x, y, G = Gcd(a, b);
    if (c % G != 0) {
        puts("Impossible");
        return 0;
    }
    a /= G, b /= G, c /= G;
    exGcd(a, b, x, y);
    x = (x % b + b) % b;
    x = x * c % b;
    cout << x << endl;
    return 0;
}
