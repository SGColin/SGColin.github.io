#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100005
#define gc getchar
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

int n, tot, hd[N];

struct edge {int to, nxt;} e[N << 1];

inline void add(int u, int v) {
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
}

double ans;

void dfs(int u, int fa, int d) {
  ans += 1.0 / (double) d;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) dfs(v, u, d + 1);
}

int main() {
  n = rd();
  for (int i = 1; i < n; ++i) add(rd(), rd());
  dfs(1, 0, 1);
  printf("%.10lf", ans);
  return 0;
}
