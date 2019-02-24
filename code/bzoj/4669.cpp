#pragma GCC optimize(2)
#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 1001
#define M 10001
#define gc getchar
#define INF 2000000000
using namespace std;

inline int rd() {
    int x = 0;
    bool f = 0;
    char c = gc();
    while (!isdigit(c)) {
        if (c == '-') f = 1;
        c = gc();
    }
    while (isdigit(c)) {
        x = x * 10 + (c ^ 48);
        c = gc();
    }
    return f ? -x : x;
}

int n, m, S, T, k, tot, hd[N];

int dis[N], mn[N], id[N], pre[N];

struct edge{
    int to, nxt, w, f;
} e[M];

inline void add(int u, int v, int f){
    e[++tot].to = v; e[tot].w = 1;
    e[tot].f = f; e[tot].nxt = hd[u]; hd[u] = tot;
    e[++tot].to = u; e[tot].w = -1;
    e[tot].f = 0; e[tot].nxt = hd[v]; hd[v] = tot;
}

bool vis[N];

queue<int> q;

bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    int inf = dis[S];
    dis[S] = 0; q.push(S);
    vis[S] = 1; mn[S] = inf;
    while (!q.empty()) {
        int u = q.front();
        vis[u] = 0; q.pop();
        for (int i = hd[u], v; i; i = e[i].nxt)
          if(e[i].f > 0 && dis[v = e[i].to] > dis[u] + e[i].w) {
              dis[v] = dis[u] + e[i].w;
              mn[v] = min(mn[u], e[i].f);
              id[v] = i; pre[v] = u;
              if (!vis[v]) vis[v] = 1, q.push(v);
          }
    }
    return dis[T] < inf;
}

void mcmf(){
  int sum = 0, lst = 0, ans = INF;
    while (spfa()) {
        for (int i = T; i != S; i = pre[i]) {
            e[id[i]].f -= mn[T]; e[id[i] ^ 1].f += mn[T];
        }
        k -= mn[T] + (dis[T] - lst) * sum;
        sum += mn[T]; lst = dis[T];
        ans = min(ans, dis[T] + (int)ceil(max(k, 0) / (1.0 * sum)));
        if (k <= 0) break;
    }
    if (ans == INF) puts("No solution");
    else printf("%d\n", ans);
}

inline void work() {
    S = 0; T = n - 1; tot = 1;
    memset(hd, 0, sizeof(hd));
    for (int i = 1, u, v, w; i <= m; ++i) {
        u = rd(); v = rd(); w = rd(); add(u, v, w);
    }
    if (k == 0) {puts("0"); return;}
    mcmf();
}

int main() {
    while (scanf("%d%d%d", &n, &m, &k) != EOF) work();
    return 0;
}
