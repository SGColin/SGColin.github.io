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

#define N 507

int b[N][N];

bool a[N][N];

inline void work() {
    int n = rd();
    rep(i, 1, n) rep(j, 1, n) {
        char c = getchar();
        while (!isdigit(c)) c = getchar();
        a[i][j] = (c == '1');
    }
    rep(i, 1, n) rep(j, 1, n) if (a[i][j] != a[j][i]) {puts("NO"); return;}
    rep(i, 1, n) rep(j, 1, n) b[i][j] = (a[i][j] ? 1 : (i == j ? 0 : 1e9));
    rep(k, 1, n) rep(i, 1, n) rep(j, 1, n) b[i][j] = min(b[i][j], b[i][k] + b[k][j]);
    rep(i, 1, n) if (b[1][i] > n) {puts("NO"); return;}
    rep(i, 1, n) rep(j, 1, n) if ((b[i][j] & 1) != a[i][j]) {puts("NO"); return;}
    puts("YES");
    vector<pii> ans;
    rep(i, 1, n) rep(j, i + 1, n) if (a[i][j]) ans.eb(i, j);
    printf("%d\n", (int)ans.size());
    for (auto [u, v] : ans) printf("%d %d\n", u, v);
}

int main() {
    per(t, rd(), 1) work();
    return 0;
}
