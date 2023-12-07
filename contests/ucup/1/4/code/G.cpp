#include <bits/stdc++.h>
using namespace std;

#define N 24

int n, ans[N], nei[N], dp[1 << (N - 1)];

int main() {
    scanf("%d", &n);
    for (int u = 0; u < n; ++u) {
        char s[N + 10]; scanf("%s", s);
        for (int v = 0; v < n; ++v) if (s[v] == '1') nei[u] |= (1 << v);
    }
    dp[0] = 1;
    int U = (1 << (n - 1)) - 1;
    for (int S = 1; S <= U; ++S)
        for (int ts = S, v; ts; ts &= ~-ts) {
            v = __builtin_ffs(ts);
            if (dp[S ^ (1 << (v - 1))] & nei[v]) dp[S] |= (1 << v);
        } 
    ans[0] = dp[U];
    for (int ts = dp[U]; ts; ts &= ~-ts) ans[__builtin_ffs(ts) - 1] |= 1; 
    for (int S = 1; S <= U; ++S) {
        int T = dp[(U ^ S)];
        for (int ts = dp[S]; ts; ts &= ~-ts) ans[__builtin_ffs(ts) - 1] |= T;
    }
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) putchar('0' + ((ans[u] >> v) & 1));
        puts("");
    }
    return 0;
}