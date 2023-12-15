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

bool vis[N];

int a[N], dif, w[N], cntodd, totodd;

void dfs(int u) {vis[u] = true; if (!vis[a[u]]) dfs(a[u]);}

int main() {
    int n = rd(), q = rd();
    auto upd = [&](int p) {w[p] = ((p + a[p]) & 1); dif += (a[p] != p); cntodd += w[p];};
    auto del = [&](int p) {dif -= (a[p] != p); cntodd -= w[p];};
    totodd = (n & 1);
    rep(i, 1, n) {a[i] = rd(); upd(i);}
    rep(i, 1, n) if (!vis[i]) {totodd ^= 1; dfs(i);} 
    rep(i, 1, q) {
        int u = rd(), v = rd();
        del(u); del(v); swap(a[u], a[v]);
        upd(u); upd(v); totodd ^= 1;
        if (!dif) puts("-1");
        else if (totodd) printf("%d\n", n);
        else printf("%d\n", cntodd ? n - 1 : n - 2);
    }
    return 0;
}