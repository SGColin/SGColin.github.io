#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

inline int rd() {
    int x = 0;
    bool f = 0;
    char c = getchar();
    for (; !isdigit(c); c = getchar()) f |= (c == '-');
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    return f ? -x : x;
}

#define mod 998244353
#define eb emplace_back
#define all(s) (s).begin(), (s).end()
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)

inline int fpow(int x, int t) {
    x = x % mod;
    int res = 1;
    for (; t; t >>= 1, x = 1ll * x * x % mod)
        if (t & 1) res = 1ll * res * x % mod;
    return res;
}

inline void work() {
    int n = rd(), k = rd();
    int g = __gcd(n, k);
    int m = n / g;
    int w = (fpow(2, m) + mod - 1) % mod;
    printf("%lld\n", (fpow(w, g) + 1ll * g * fpow(w, g - 1)) % mod);
}

int main() {
    per(t, rd(), 1) work();
    return 0;
}