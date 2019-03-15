#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 200005
#define gc getchar
#define inf 1000000000
#define mid ((l + r) >> 1)
using namespace std;

inline int rd() {
  int x = 0;
  char c = gc();
  while (!isdigit(c)) c = gc();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = gc();
  }
  return x;
}

char s[2][N];

int n, m, v[2][N];

struct matrix {
  int a[2][2];
  matrix(){
    a[0][0] = a[1][1] = a[0][1] = a[1][0] = inf;
  }
  matrix operator *(const matrix &x) {
    matrix res;
    for (int i = 0; i <= 1; ++i)
      for (int j = 0; j <= 1; ++j)
        for (int k = 0; k <= 1; ++k)
          res.a[i][j] = min(res.a[i][j], a[i][k] + x.a[k][j] + 1);
    return res;
  }
} u;

int root, ptr;

struct node{
  int ls, rs;
  matrix f;
} c[N << 1];

void build(int &rt, int l, int r) {
  rt = ++ptr;
  if (l == r) {
    for (int i = 0; i <= 1; ++i)
      for (int j = 0; j <= 1; ++j)
        if (v[i][l] && v[j][l]) c[rt].f.a[i][j] = (i ^ j);
    return;
  }
  build(c[rt].ls, l, mid);
  build(c[rt].rs, mid + 1, r);
  c[rt].f = c[c[rt].ls].f * c[c[rt].rs].f;
}

matrix query(int rt, int l, int r, int L, int R) {
  if (l >= L && r <= R) return c[rt].f;
  if (R <= mid) return query(c[rt].ls, l, mid ,L, R);
  if (L > mid) return query(c[rt].rs, mid + 1, r, L, R);
  return query(c[rt].ls, l, mid, L, R) * query(c[rt].rs, mid + 1, r, L, R);
}

int main() {
  n = rd(); m = rd();
  scanf("%s%s", s[0], s[1]);
  u.a[0][0] = u.a[1][1] = u.a[0][1] = u.a[1][0] = -1;
  for (int i = 1; i <= n; ++i) {
    v[0][i] = (s[0][i - 1] == '0');
    v[1][i] = (s[1][i - 1] == '0');
  }
  build(root, 1, n);
  for (int i = 1, x, y, l, r; i <= m; ++i) {
    x = rd(); y = rd();
    l = (x - 1) % n + 1;
    r = (y - 1) % n + 1;
    if (l > r) swap(x, y), swap(l, r);
    matrix res = query(root, 1, n, l ,r);
    int ans = res.a[x > n][y > n];
    if (ans < inf) printf("%d\n", ans);
    else puts("You have been confusional!");
  }
  return 0;
}
