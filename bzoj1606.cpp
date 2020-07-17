
#include <iostream>

using namespace std;

const int NUM = 50000 + 5;

int C, H;
int c[NUM], dp[NUM];

inline int max(int a, int b) {
if (a > b) return a;
return b;
}

int main() {
cin >> C >> H;
for (int i = 0; i < H; ++i) cin >> c[i];
for (int i = 0; i < H; ++i)
for (int v = C; v >= c[i]; --v)
dp[v] = max(dp[v], dp[v - c[i]] + c[i]);
cout << dp[C] << endl;
return 0;
}
