#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll rd() {
    bool f = 0; ll x = 0;
    char c = getchar();
    for (; !isdigit(c); c = getchar()) f |= (c == '-');
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    return f ? -x : x;
}

#define N 57
#define fr first
#define sc second
#define pb push_back
#define mp make_pair
#define pii pair<ll, ll>

ll n, m, k, Q, a[N][N], b[N][N];

ll final_score;

vector<pii> s, tt;

inline bool all_empty() {
    for (ll i = 1; i <= n; ++i)
        for (ll j = 1; j <= m; ++j) if (a[i][j]) return 0;
    return 1;
}

inline bool check_valid_cell(ll x, ll y) {
    for (ll i = max(1ll, x - 2); i <= x; ++i)
        if (a[i][y] == a[x][y] && a[i + 1][y] == a[x][y] && a[i + 2][y] == a[x][y]) return 1;
    for (ll j = max(1ll, y - 2); j <= y; ++j)
        if (a[x][j] == a[x][y] && a[x][j + 1] == a[x][y] && a[x][j + 2] == a[x][y]) return 1;
    return 0;
}

inline bool cmp(pii a, pii b) {
    if (a.fr != b.fr) return a.fr > b.fr;
    return a.sc > b.sc;
}

inline ll calc_color_score() {
    if (tt.size() == 1) return 1000 + tt[0].sc * 10;
    if (tt.size() == 2) {
        if (tt[0].fr == 4) return 750 + tt[0].sc * 5;
        return 500 + tt[0].sc * 3 + tt[1].sc;
    }
    if (tt.size() == 3) {
        if (tt[0].fr == 3) return 300 + tt[0].sc * 3;
        return 200 + tt[0].sc + tt[1].sc + max(tt[0].sc, tt[1].sc);
    }
    if (tt.size() == 4) return 100 + tt[0].sc * 2;
    return 50 + tt[0].sc;
}

inline ll max_color() {
    ll tmp_color[5];
    ll mxans = 0;
    for (ll S = 0; S < 32; ++S) {
        for (ll i = 0; i < 5; ++i)
            tmp_color[i] = ((S & (1 << i)) ? s[i].fr : s[i].sc);
        if (tmp_color[0] < 0 || tmp_color[1] < 0 || tmp_color[2] < 0 || tmp_color[3] < 0 || tmp_color[4] < 0) continue;
        tt.clear();
        sort(tmp_color, tmp_color + 5);
        ll cnt = 1;
        for (ll i = 1; i < 5; ++i) 
            if (tmp_color[i] != tmp_color[i - 1]) {
                tt.pb(mp(cnt, tmp_color[i - 1]));
                cnt = 1;
            } else ++cnt;
        tt.pb(mp(cnt, tmp_color[4]));
        sort(tt.begin(), tt.end(), cmp);
        ll w = calc_color_score();
        mxans = max(mxans, w);
    }
    s.clear();
    return mxans;
}

bool vis[N][N], vis2[N][N];

inline bool check() {
    memset(vis, 0, sizeof(vis));
    bool fl = 0;
    for (ll i = 1; i <= n - 2; ++i)
        for (ll j = 1; j <= m; ++j) {
            if (a[i][j] == 0) continue;
            if (a[i][j] == a[i + 1][j] && a[i][j] == a[i + 2][j]) {
                vis[i][j] = 1;
                vis[i + 1][j] = 1;
                vis[i + 2][j] = 1;
                fl = 1;
            }
        }
    for (ll i = 1; i <= n; ++i)
        for (ll j = 1; j <= m - 2; ++j) {
            if (a[i][j] == 0) continue;
            if (a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2]) {
                vis[i][j] = 1;
                vis[i][j + 1] = 1;
                vis[i][j + 2] = 1;
                fl = 1;
            }
        }
    return fl;
}

bool del_color[107];

queue<pii> q;

const ll dx[4] = {1, 0, -1, 0};
const ll dy[4] = {0, 1, 0, -1};

inline void eliminate(ll cnt_round) {
    memset(vis2, 0, sizeof(vis2));
    for (ll i = 1; i <= n; ++i)
        for (ll j = 1; j <= m; ++j)
            if (vis[i][j] && !vis2[i][j]) {
                q.push(mp(i, j));
                ll tmpcnt = 0; // 计数连通块大小
                vis2[i][j] = 1;
                while (!q.empty()) { // 找和 (i, j) 一样颜色且会被消掉的连通块
                    ++tmpcnt;
                    ll nx = q.front().fr;
                    ll ny = q.front().sc; q.pop();
                    for (ll dr = 0; dr < 4; ++dr) {
                        ll tx = nx + dx[dr];
                        ll ty = ny + dy[dr];
                        if (tx < 1 || tx > n) continue;
                        if (ty < 1 || ty > m) continue;
                        if (!vis2[tx][ty] && vis[tx][ty] && a[tx][ty] == a[nx][ny]) {
                            vis2[tx][ty] = 1; q.push(mp(tx, ty));
                        }
                    } 
                }
                // 组合奖分
                final_score += 50 * (tmpcnt - 3) * (tmpcnt - 3);
                // prllf("type2 %lld\n", final_score);
            }
    for (ll i = 1; i <= n; ++i)
        for (ll j = 1; j <= m; ++j)
            if (vis[i][j]) q.push(mp(i, j));
    while (!q.empty()) {
        ll nx = q.front().fr;
        ll ny = q.front().sc; q.pop();
        final_score += a[nx][ny] * cnt_round;
        ll nwa = a[nx][ny];
        ll nwb = b[nx][ny];
        a[nx][ny] = b[nx][ny] = 0;
        if (nwb == 0) continue;
        if (nwb == 1) {
            for (ll j = 1; j <= m; ++j) 
                if (!vis[nx][j]) {vis[nx][j] = 1; q.push(mp(nx, j));}
        } else if (nwb == 2) {
            for (ll i = 1; i <= n; ++i)
                if (!vis[i][ny]) {vis[i][ny] = 1; q.push(mp(i, ny));}
        } else if (nwb == 3) {
            for (ll j = 1; j <= m; ++j) 
                if (!vis[nx][j]) {vis[nx][j] = 1; q.push(mp(nx, j));}
            for (ll i = 1; i <= n; ++i)
                if (!vis[i][ny]) {vis[i][ny] = 1; q.push(mp(i, ny));}
        } else if (nwb == 4) {
            for (ll i = max(1ll, nx - 1); i <= min(n, nx + 1); ++i)
                for (ll j = max(1ll, ny - 1); j <= min(m, ny + 1); ++j)
                    if (a[i][j] && !vis[i][j]) {vis[i][j] = 1; q.push(mp(i, j));}
        } else if (nwb == 5) {
            for (ll i = max(1ll, nx - 2); i <= min(n, nx + 2); ++i)
                for (ll j = max(1ll, ny - 2); j <= min(m, ny + 2); ++j)
                    if (a[i][j] && !vis[i][j]) {vis[i][j] = 1; q.push(mp(i, j));}
        } else {
            if (del_color[nwa]) continue;
            del_color[nwa] = 1;
            for (ll i = 1; i <= n; ++i)
                for (ll j = 1; j <= m; ++j)
                    if (a[i][j] == nwa && !vis[i][j]) {vis[i][j] = 1; q.push(mp(i, j));}
        }
    }
}

inline void dropdown() {
    for (ll j = 1; j <= m; ++j)
        for (ll i = n, nwx = n; i; --i) {
            if (a[i][j] != 0) {
                swap(a[i][j], a[nwx][j]);
                swap(b[i][j], b[nwx][j]);
                --nwx;
            }
        }
}

inline void print() {
    puts("");
    for (ll i = 1; i <= n; ++i) {
        for (ll j = 1; j <= m; ++j)
            if (a[i][j]) printf("%d(%d) ", a[i][j], b[i][j]);
            else printf(".(%d) ", b[i][j]);
        puts("");
    }
}

int main() {
    n = rd(); m = rd(); k = rd(); Q = rd();
    for (ll i = 1; i <= n; ++i) 
        for (ll j = 1; j <= m; ++j) a[i][j] = rd();
    for (ll i = 1; i <= n; ++i) 
        for (ll j = 1; j <= m; ++j) b[i][j] = rd();
    ll cnt_valid_round = 0;
    // prll();
    for (ll i = 1; i <= Q; ++i) {
        // puts("=============================================");
        ll xa = rd(), ya = rd(), xb = rd(), yb = rd();
        // prllf("%d %d %d %d\n", xa, ya, xb, yb);
        if (abs(xa - xb) + abs(ya - yb) != 1) continue; // 不相邻不合法
        if (a[xa][ya] == 0 || a[xb][yb] == 0) continue; // 空的不合法
        swap(a[xa][ya], a[xb][yb]);
        swap(b[xa][ya], b[xb][yb]);
        bool valid1 = check_valid_cell(xa, ya);
        bool valid2 = check_valid_cell(xb, yb);
        if (!valid1 && !valid2) { // 换完了不能消不合法，换回来
            swap(a[xa][ya], a[xb][yb]);
            swap(b[xa][ya], b[xb][yb]); continue;
        }

        // 操作的主颜色
        if (valid1) s.pb(mp(a[xa][ya], valid2 ? a[xb][yb] : -1));
        else s.pb(mp(a[xb][yb], -1));
        
        ll cnt_round = 0;
        while(check()) {++cnt_round; eliminate(cnt_round); dropdown();}
        // 连锁奖励
        final_score += 80 * (cnt_round - 1) * (cnt_round - 1);
        
        // 牌型奖励
        ++cnt_valid_round;
        if (cnt_valid_round % 5 == 0) final_score += max_color();
    }
    // 终局奖励
    if (cnt_valid_round == Q) final_score += 1000;
    if (all_empty()) final_score += 10000;
    printf("%lld\n", final_score);
    return 0;
}