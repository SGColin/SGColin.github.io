#include<bits/stdc++.h>
using namespace std;

#define fr first
#define sc second
#define mp make_pair
#define pii pair<int, int>

int cnt[10000][13][32];

unordered_map<string, int> id;

int dat[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

inline bool leapyear(int y) {
    if (y % 400 == 0) return 1;
    if (y % 4 == 0 && y % 100 != 0) return 1;
    return 0;
}

inline void prework() {

    cin.tie(nullptr) -> sync_with_stdio(false);
    
    id["Jan"] = 1; id["Feb"] = 2; id["Mar"] = 3;
    id["Apr"] = 4; id["May"] = 5; id["Jun"] = 6;
    id["Jul"] = 7; id["Aug"] = 8; id["Sep"] = 9; 
    id["Oct"] = 10; id["Nov"] = 11; id["Dec"] = 12;

    int tot = 0;
    for (int y = 2000; y <= 9999; ++y)
        for (int m = 1; m <= 12; ++m) { 
            int lim = dat[m] + (m == 2) * leapyear(y);
            for (int d = 1; d <= lim; ++d) {
                cnt[y][m][d] = tot * 24; ++tot;
            }
        }
}

pii a[2507];

int v[100007];

deque<int> q;

int main() {
    prework();
    int n, m, y, d, h, S, T;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        string s;
        int mxt = m;
        for (int i = 1; i <= n; ++i) {
            cin >> s >> d >> y >> h >> a[i].sc;
            a[i].fr = cnt[y][id[s]][d] + h;
            mxt = max(mxt, a[i].fr);
        }
        cin >> T >> S;
        int ptr = 1;
        long long ans = 0;
        for (int i = 0; i <= mxt; ++i) {
            if (i < m) {
                cin >> v[i];
                while (!q.empty() && v[q.back()] + S * (i - q.back()) > v[i]) q.pop_back();
                q.push_back(i);
            }
            while (!q.empty() && i - q.front() > T) q.pop_front();
            for (; ptr <= n && a[ptr].fr == i; ++ptr)
                ans += 1ll * a[ptr].sc * (v[q.front()] + S * (i - q.front()));
        }
        cout << ans << endl;
        q.clear();
    }
    return 0;
}