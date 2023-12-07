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

void work() {
    int n = rd(), m = rd();
    vector<vector<int>> ty(n + 1, vector<int>(m + 1, 0));
    auto dp = ty;
    bool fl = false;
    rep(i, 1, n) rep(j, 1, m) {
        int x = rd();
        if (x == i + j) ty[i][j] = 1;
        else if (x == i + j - 1) ty[i][j] = -1;
        else if (x != -1) fl = true;
        if (ty[i][j - 1] == 1 || ty[i - 1][j] == 1) {
            if (ty[i][j] == -1) fl = true; ty[i][j] = 1;
        }
    }
    if (fl) {puts("0"); return;}
    int ans = 1;
    per(i, n, 1) per(j, m, 1) {
        if (i != n && ty[i + 1][j] == -1) ty[i][j] = -1;
        if (j != m && ty[i][j + 1] == -1) ty[i][j] = -1;
        if (ty[i][j] == 1) ans = 0;
    }
    rep(j, 1, m) if (ty[n][j] >= 0) {
        dp[n][j] = 1; if (ty[n][j] == 1) break;
    }
    per(i, n, 1) rep(j, 1, m) if (ty[i][j] >= 0) {
        if (ty[i - 1][j] >= 0) dp[i - 1][j] = (dp[i - 1][j] + dp[i][j]) % mod;
        if (ty[i - 1][j] <= 0 && j < m) dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % mod;
    }
    rep(i, 1, n) if (ty[i][m] >= 0) {
        ans = (ans + dp[i][m]) % mod;
        if (ty[i][m] == 1) break;
    }
    printf("%d\n", ans);
}

int main() {
    per(t, rd(), 1) work();
    return 0;
}