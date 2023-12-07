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

#define N 20007
#define M 200007
#define eb emplace_back
#define all(s) (s).begin(), (s).end()
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)

bool vis[N];

vector<int> e[N];

void work() {
    int n = rd(), m = rd();
    rep(i, 1, m) {
        int u = rd(), v = rd();
        e[u].eb(v); e[v].eb(u);
    }
    rep(i, 1, n) {
        rep(j, 1, n) vis[j] = false;
        for (auto v : e[i])
            for (auto j : e[v]) if (j != i) {
                if (vis[j]) {puts("2"); return;}
                vis[j] = true;
            }
    }
    puts("3");
}


/*

// Solution 2: 4-cycle counting

vector<int> e[N], re[N];

int d[N], cnt[N], x[M], y[M];

inline bool cmp(const int &x, const int &y) {
    return d[x] < d[y] || d[x] == d[y] && x < y;
}

inline void work() {
    int n = rd() * 2, m = rd();
    rep(i, 1, m) {
        x[i] = rd(); y[i] = rd();
        ++d[x[i]]; e[x[i]].eb(y[i]);
        ++d[y[i]]; e[y[i]].eb(x[i]);
    }
    rep(i, 1, m) cmp(x[i], y[i]) ? re[x[i]].eb(y[i]) : re[y[i]].eb(x[i]);
    rep(x, 1, n) {
        for (auto y: e[x])
            for (auto z: re[y])
                if (cmp(x, z)) {if (cnt[z]) {puts("2"); return;} cnt[z]++;}
        for (auto y: e[x]) 
            for (auto z: re[y]) cnt[z] = 0;
    }
    puts("3");
}
*/

int main() {
    work();
    return 0;
}
