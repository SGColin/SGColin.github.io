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

int a[N];

inline void work() {
    int n = rd(), xsum = 0;
    rep(i, 1, n) xsum ^= (a[i] = rd());
    if (xsum != 0) {
        printf("YES\n2\n1 1\n2 %d\n", n);
        return;
    }
    int p = 1; while (p <= n && a[p] == 0) ++p;
    if (p >= n) {puts("NO"); return;}
    xsum = 0;
    rep(i, p + 1, n - 1) {
        xsum ^= a[i];
        if (xsum != 0 && xsum != a[p]) {
            printf("YES\n3\n1 %d\n%d %d\n%d %d\n", p, p + 1, i, i + 1, n);
            return;
        }
    }
    puts("NO");
    /* 
    // Solution 2
    set<pii> s;
    int cur = 0;
    rep(i, 1, n) {
        cur ^= a[i];
        if (cur != 0 && !s.empty()) {
            int pos = 0;
            if (cur != s.begin() -> first) pos = s.begin() -> second;
            if (cur != (--s.end()) -> first) pos = (--s.end()) -> second;
            if (pos) {
                puts("YES\n3");
                printf("%d %d\n", 1, pos);
                printf("%d %d\n", pos + 1, i);
                printf("%d %d\n", i + 1, n);
                return;
            }
        }
        if (cur != 0) s.insert(make_pair(cur, i));
    }
    puts("NO");
    */
}

int main() {
    per(t, rd(), 1) work();
    return 0;
}