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

#define eb emplace_back
#define all(s) (s).begin(), (s).end()
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)

#define N 1007

map<int, int> f;

int a[N][N], tot;

vector<int> x[N * N], y[N * N];

int main() {
    int n = rd(), m = rd();
    rep(i, 1, n) rep(j, 1, m) {
        int w = rd();
        if (!f[w]) f[w] = ++tot;
        x[f[w]].eb(i); y[f[w]].eb(j);
    }
    ll ans = 0;
    auto calc = [&](vector<int> &s) {
        sort(all(s));
        int cnt = 0;
        ll sum = 0;
        for (auto w : s) {
            ans += w * cnt - sum;
            sum += w; ++cnt;
        }
    };
    rep(i, 1, tot) {calc(x[i]); calc(y[i]);}
    printf("%lld\n", ans * 2);
    return 0;
}