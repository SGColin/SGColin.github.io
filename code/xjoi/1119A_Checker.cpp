#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define gc getchar
#define N 10005
using namespace std;

int n, ans, tot, hd[N], sz[N], cntson[N];

struct edge{int to, nxt;} e[N << 1];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

inline void dfs(int u, int fa) {
  sz[u] = 1;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) {
      dfs(v, u); sz[u] += sz[v];
      if (u != 1) ans += cntson[v];
      ++cntson[u];
    }
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) ans += max(0, cntson[v] * (cntson[u] - 1));
}

int main() {
  int x, y;
  while (scanf("%d%d", &x, &y) != EOF) {
    if (!x || !y) break;
    add(x, y); n = max(n, max(x, y));
  }
  dfs(1, 0);
  printf("%d\n", ans);
  return 0;
}
