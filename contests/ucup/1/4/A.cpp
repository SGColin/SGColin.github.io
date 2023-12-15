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

vector<int> s;

deque<int> q;

inline void work() {
    s.clear();
    q.clear();
    int n = rd();
    rep(i, 1, n) s.eb(rd());
    sort(all(s));
    bool fl = false;
    for (auto x : s) {
        if (fl) q.push_front(x);
        else q.push_back(x);
        fl = 1 - fl;
    }
    ll ans = 0;
    rep(i, 0, n - 1) ans += 1ll * q[i] * q[(i + 1) % n];
    printf("%lld\n", ans);
}

int main() {
    per(t, rd(), 1) work();
    return 0;
}