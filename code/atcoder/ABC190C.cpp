#include <bits/stdc++.h>
#define N 300007
#define inf 1000000007
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

int n, m, k, cnt[N], a[N], b[N], c[N], d[N], ans;

void dfs(int dep) {
  if (dep > k) {
    int tmp = 0;
    for (int i = 1; i <= m; ++i)
      tmp += (cnt[a[i]] && cnt[b[i]]);
    ans = max(ans, tmp); return;
  }
  ++cnt[c[dep]];
  dfs(dep + 1);
  --cnt[c[dep]];
  ++cnt[d[dep]];
  dfs(dep + 1);
  --cnt[d[dep]];
}

int main() {
  n = rd(); m = rd();
  for (int i = 1; i <= m; ++i) {
    a[i] = rd(); b[i] = rd();
  }
  k = rd();
  for (int i = 1; i <= k; ++i) {
    c[i] = rd(); d[i] = rd();
  }
  dfs(1);
  printf("%d\n", ans);
  return 0;
}