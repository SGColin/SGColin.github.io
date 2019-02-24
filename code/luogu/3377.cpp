#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 150005
#define gc getchar
#define ls son[x][0]
#define rs son[x][1]
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

bool fl[N];

int n, m, f[N], w[N], dis[N] = {-1}, son[N][2];

int find(int x) {return x == f[x] ? x : f[x] = find(f[x]);}

int merge(int x, int y) {
  if (!x || !y) return x + y;
  if (w[x] > w[y] || (w[x] == w[y] && x > y)) swap(x, y);
  rs = merge(rs, y);
  f[ls] = f[rs] = f[x] = x;
  if (dis[ls] < dis[rs]) swap(ls, rs);
  dis[x] = dis[rs] + 1;
  return x;
}

inline int pop(int x) {
  fl[x] = 1;
  f[ls] = f[rs] = f[x] = merge(ls, rs);
  return x;
}

int main() {
  n = rd(); m = rd();
  for (int i = 1; i <= n; ++i) f[i] = i, w[i] = rd();
  for (int i = 1, op, x, y; i <= m; ++i) {
    op = rd();
    if (op == 1) {
      x = rd(); y = rd();
      if (fl[x] || fl[y]) continue;
      x = find(x); y = find(y);
      if(x != y) f[x] = f[y] = merge(x, y);
    } else {
      x = rd();
      printf("%d\n", fl[x] ? -1 : w[pop(find(x))]);
    }
  }
  return 0;
}
