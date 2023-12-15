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

#define N 200007

int cnt;

bool vis[N];

vector<int> e[N], re[N];

void dfs(int u) {
    ++cnt; vis[u] = true;
    for (auto v : e[u]) if (!vis[v]) dfs(v);
}

void rfs(int u) {
    ++cnt; vis[u] = true;
    for (auto v : re[u]) if (!vis[v]) rfs(v);
}

inline void work() {
    int n = rd(), m = rd();
    rep(i, 1, n) e[i].clear(), re[i].clear();
    rep(i, 1, m) {
        int u = rd(), v = rd();
        e[u].eb(v); re[v].eb(u);
    }
    rep(i, 1, n) vis[i] = false;
    cnt = 0; dfs(1); if (cnt < n) {puts("NO"); return;}
    rep(i, 1, n) vis[i] = false;
    cnt = 0; rfs(1); if (cnt < n) {puts("NO"); return;}
    puts("YES");
}

int main() {
    per(t, rd(), 1) work();
    return 0;
}
