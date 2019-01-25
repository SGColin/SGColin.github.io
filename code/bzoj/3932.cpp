#include <cmath>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100005
#define M 4000005
#define gc getchar
#define rg register
#define mid ((l+r) >> 1)
using namespace std;
typedef long long ll;

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

int n, m, tot, tmp[N];

vector<int> s[N];

int rot[N], ptr;

inline int newnode() { return ++ptr; }

struct node {
  ll sum;
  int ls, rs, cnt;
}c[M];

inline void update(int &rt, int l, int r, int x) {
  int lst = rt;
  rt = newnode();
  c[rt] = c[lst];
  c[rt].sum += x;
  c[rt].cnt += (x < 0 ? -1 : 1);
  if (l == r) return;
  if (abs(x) <= tmp[mid]) update(c[rt].ls, l, mid, x);
  else update(c[rt].rs, mid + 1, r, x);
}

inline ll query(int rt, int l, int r, int k) {
  if (c[rt].cnt <= k) return c[rt].sum;
  if (l == r) return c[rt].sum / c[rt].cnt * k;
  if (c[c[rt].ls].cnt >= k) return query(c[rt].ls, l, mid, k);
  return c[c[rt].ls].sum + query(c[rt].rs, mid + 1, r, k - c[c[rt].ls].cnt);
}

int main() {
  m = rd(); n = rd();
  for (rg int i = 1, l, r, x; i <= m; ++i) {
    l = rd(); r = rd();
    tmp[++tmp[0]] = x = rd();
    s[l].push_back(x);
    s[r + 1].push_back(-x);
  }
  sort(tmp + 1, tmp + 1 + tmp[0]);
  for (rg int i = 1; i <= tmp[0]; ++i) {
    tmp[++tot] = tmp[i];
    while (tmp[i + 1] == tmp[i]) ++i;
  }
  for (rg int i = 1; i <= n; ++i) {
    rot[i] = rot[i-1];
    for (rg int j = s[i].size() - 1; ~j; --j) update(rot[i], 1, tot, s[i][j]);
  }
  rg ll pre = 1;
  for (rg int i = 1, t, k; i <= n; ++i) {
    t = rd();
    k = 1 + (pre * rd() + rd()) % rd();
    pre = query(rot[t], 1, tot, k);
    printf("%lld\n", pre);
  }
  return 0;
}
