#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100010
#define gc getchar
#define rg register
using namespace std;

inline int rd() {
  rg int x = 0;
  rg bool f = 0;
  rg char c = gc();
  while (!isdigit(c)) {
    if (c == '-') f = 1;
    c = gc();
  }
  while(isdigit(c)) {
    x = x * 10 + (c ^ 48);
    c = gc();
  }
  return f ? -x : x;
}

int n, m, tot, hd[N], deg[N], id[N];

struct road { int u, v, w; }a[N];

struct edge { int w, to, nxt; }e[N];

inline void add(int u, int v, int w) {
  a[++tot] = (road){u, v, w};
  e[tot].to = v; e[tot].w = w;
  e[tot].nxt = hd[u]; hd[u] = tot;;
}

queue<int> q;

inline bool valid(int x) {
  for (rg int i = 1; i <= n; ++i) deg[i] = 0;
  for (rg int i = 1; i <= m; ++i)
    if (a[i].w > x) ++deg[a[i].v];
  for (rg int i = 1; i <= n; ++i) if(!deg[i]) q.push(i);
  int cnt = 0;
  while(!q.empty()) {
    int u = q.front();
    id[u] = ++cnt; q.pop();
    for (rg int i = hd[u], v; i; i = e[i].nxt)
      if (e[i].w > x) {
        --deg[v = e[i].to];
        if (!deg[v]) q.push(v);
      }
  }
  for (rg int i = 1; i <= n; ++i) if(deg[i]) return 0;
  return 1;
}

bool rev[N];

int main() {
  n = rd(); m = rd();
  int l = 0, r = 0;
  for (rg int i = 1,u,v,w; i <= m; ++i) {
    u = rd(); v = rd();
    r = max(r, (w = rd())); add(u, v, w);
  }
  while (l < r) {
    int mid = (l + r) >> 1;
    valid(mid) ? r = mid : l = mid + 1;
  }
  valid(l);
  int cnt = 0;
  for (rg int i = 1; i <= m; ++i)
    if(a[i].w <= l) {
      rev[i] = (id[a[i].u] > id[a[i].v]) ;
      cnt += rev[i];
    }
  printf("%d %d\n", l, cnt);
  for (rg int i = 1; i <= m; ++i) if(rev[i]) printf("%d ",i);
  return 0;
}
