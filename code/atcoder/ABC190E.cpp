#include <bits/stdc++.h>
#define N 100007
using namespace std;
typedef long long ll;

inline int rd() {
  int x = 0;
  bool f = 0;
  char c = getchar();
  for (; !isdigit(c); c = getchar()) if (c == '-') f = 1;
  for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return f ? -x : x;
}

struct edge{int to, nxt;}e[N << 1];

int n, m, k, tot, hd[N], c[N], dis[17][N];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

queue<int> q;

void bfs(int u, int t) {
  q.push(u);
  dis[t][u] = 0;
  while(!q.empty()) {
    u = q.front(); q.pop();
    for (int i = hd[u], v; i; i = e[i].nxt) 
      if (dis[t][v = e[i].to] > dis[t][u] + 1) {
        dis[t][v] = dis[t][u] + 1; q.push(v);
      }
  }
}

int f[1 << 18][18]; 

int main() {
  n = rd(); m = rd();
  memset(f, 0x3f, sizeof(f));
  memset(dis, 0x3f, sizeof(dis));
  for (int i = 1; i <= m; ++i) add(rd(), rd());
  k = rd();
  for (int i = 0; i < k; ++i) {
    c[i] = rd(); bfs(c[i], i);
  }
  int inf = f[0][0];
  for (int i = 0; i < k; ++i) f[1 << i][i] = 1;
  for (int s = 1; s < (1 << k); ++s)
    for (int i = 0; i < k; ++i) {
        if (f[s][i] == inf) continue;
        for (int j = 0; j < k; ++j)
          if ((s & (1 << j)) == 0) {
            f[s | (1 << j)][j] = min(f[s | (1 << j)][j], f[s][i] + dis[i][c[j]]);
          }
    }
  int ans = inf;
  int SS = (1 << k) - 1;
  for (int i = 0; i < k; ++i)
    if (f[SS][i] != inf) ans = min(ans, f[SS][i]);
  if (ans == inf) puts("-1");
  else printf("%d\n", ans);
  return 0;
}