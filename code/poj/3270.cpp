#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 10010
#define inf 2000000000
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
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48);
    c = gc();
  }
  return f ? -x : x;
}

bool vis[N];

int n, id[N], w[N];

inline bool cmp(int x, int y) { return w[x] < w[y]; }

int main() {
  n = rd();
  for (rg int i = 1; i <= n; ++i) id[i] = i, w[i] = rd();
  sort(id + 1, id + 1 + n, cmp);
  int Mn = w[id[1]], ans = 0;
  for (rg int i = 1, p, sum, mn, cnt; i <= n; ++i)
    if (!vis[i]) {
      p = i;
      mn = inf;
      sum = cnt =0;
      while (!vis[p]) {
        vis[p] =1;
        ++cnt; sum += w[id[p]];
        mn = min(mn, w[id[p]]);
        p = id[p];
      }
      ans += min(sum + (cnt - 2) * mn, sum + (cnt + 1) * Mn + mn);
    }
  printf("%d\n",ans);
  return 0;
}
