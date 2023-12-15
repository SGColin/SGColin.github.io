#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

#define eb emplace_back
#define all(s) (s).begin(), (s).end()
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)

int n;

vector<char> sc[60];

vector<int> tar;

bool use[256];

char ans[60];

int tr(char c) {return islower(c) ? c - 'a' : c - 'A' + 26;}

bool check() {
    vector<int> tmp;
    rep(i, 0, n - 1) rep(j, 0, n - 1) {
        int w = i * j;
        tmp.eb(w < n ? tr(ans[w]) : tr(ans[w / n]) * 52 + tr(ans[w % n]));
    }
    sort(all(tmp));
    return tar == tmp;
}

bool dfs(int pos) {
    if (pos == n) return check();
    for (auto x : sc[pos]) 
        if (!use[x]) {
            use[x] = true;
            ans[pos] = x;
            if (dfs(pos + 1)) return true;
            use[x] = false;
        }
    return false;
}

inline void work() {
    cin >> n;
    tar.clear();
    memset(use, 0, sizeof(use));
    vector<int> cnt1(n, 0), cnt2(n, 0);
    rep(i, 0, n - 1) rep(j, 0, n - 1) {
        int w = i * j;
        ++cnt2[w % n];
        if (w >= n) ++cnt1[w / n];
    }
    map<pii, vector<int>> f;
    rep(i, 0, n - 1) f[{cnt1[i], cnt2[i]}].push_back(i);

    map<char, int> c1, c2;
    set<char> ch;
    rep(i, 1, n * n) {
        string s; cin >> s;
        int l = s.length();
        if (l == 1) {
            ++c2[s[0]]; ch.insert(s[0]);
            tar.eb(tr(s[0]));
        } else {
            ++c1[s[0]]; ch.insert(s[0]);
            ++c2[s[1]]; ch.insert(s[1]);
            tar.eb(tr(s[0]) * 52 + tr(s[1]));
        }
    }
    sort(all(tar));
    rep(i, 0, n - 1) sc[i].clear();
    for (auto x : ch) {
        pii c = make_pair(c1[x], c2[x]);
        for (auto p : f[c]) sc[p].push_back(x);
    }
    dfs(0);
    rep(i, 0, n - 1) putchar(ans[i]); puts("");
}

int main() {
    int t; cin >> t;
    while(t--) work();
    return 0;
}