#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 100005
#define gc getchar
#define rg register
#define mid ((l + r) >> 1)
#define inf 1000000005
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

int rot[N], ptr;

inline int newnode(){ return ++ptr; }

struct node {
  int ls, rs, sum;
} c[N * 35];

void build(int &rt, int lst, int l, int r, int x) {
  rt = newnode();
  c[rt] = c[lst];
  c[rt].sum += x;
  if (l == r) return;
  if (x <= mid) build(c[rt].ls, c[lst].ls, l, mid, x);
  else build(c[rt].rs, c[lst].rs, mid + 1, r, x);
}

int query(int rtl, int rtr, int l, int r, int R) {
  if (r <= R) return c[rtr].sum - c[rtl].sum;
  int ans = query(c[rtl].ls, c[rtr].ls, l, mid, R);
  if (R > mid) ans += query(c[rtl].rs, c[rtr].rs, mid + 1, r, R);
  return ans;
}

int main() {
  int n = rd();
  for (rg int i = 1; i <= n; ++i)
    build(rot[i], rot[i - 1], 1, inf, rd());
  int m = rd(), l, r, now, ans;
  while (m--) {
    l = rd(); r = rd();
    ans = 0;
    now = query(rot[l - 1], rot[r], 1, inf , ans + 1);
    while (now > ans) {
      ans = now;
      now = query(rot[l - 1], rot[r], 1, inf, ans + 1);
    }
    printf("%d\n", ans + 1);
  }
  return 0;
}
