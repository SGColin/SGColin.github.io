#include <set>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 50005
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

multiset<int> s;

int n, m, tot, sum, hd[N];

struct edge{
  int w, to, nxt;
} e[N << 1];

inline void add(int u, int v, int w) {
  e[++tot].to = v; e[tot].w = w;
  e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].w = w;
  e[tot].nxt = hd[v]; hd[v] = tot;
}

int mid, cnt, f[N];

void dfs(int u, int fa) {
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) dfs(v, u);
  s.clear();
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa){
      if (f[v] + e[i].w >= mid) {
        ++cnt; continue;
      }
      s.insert(f[v] + e[i].w);
    }
  multiset<int>::iterator ptr;
  while (!s.empty()) {
    int mn = *s.begin();
    s.erase(s.begin());
    ptr = s.lower_bound(mid - mn);
    if (ptr == s.end()) f[u] = max(f[u], mn);
    else {
      s.erase(ptr); ++cnt;
    }
  }
}

inline bool valid() {
  cnt = 0;
  for (int i = 1; i <= n; ++i) f[i] = 0;
  dfs(1, 0);
  return cnt >= m;
}

int main() {
  n = rd(); m = rd();
  for (int i = 1, u, v, w; i < n; ++i) {
    u = rd(); v = rd();
    w = rd(); sum += w;
    add(u, v, w);
  }
  int l = 0, r = sum / m + 1;
  while (l < r) {
    mid = (l + r + 1) >> 1;
    valid() ? l = mid : r = mid - 1;
  }
  printf("%d\n", l);
  return 0;
}
