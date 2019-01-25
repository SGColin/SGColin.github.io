#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 80010
#define gc getchar
#define rg register
#define lowbit(x) (x & -x)
#define IL __inline__ __attribute__((always_inline))
#define fastcall __attribute__((optimize("-O3")))
using namespace std;

char *TT,*mo,but[(1<<15)+2];
#define getchar() ((TT==mo&&(mo=(TT=but)+fread(but,1,1<<15,stdin)),TT==mo)?0:*TT++)

fastcall IL int rd()
{
    int x=0,ch=0;
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x;
}

fastcall void print(int x){if(x<0)putchar('-'),x=-x;if(x>=10)print(x/10);putchar(x%10+'0');}

int n, m, mx, tot, hd[N], w[N];

struct edge {
  int to, nxt;
} e[N << 1];

IL void add(const int &u, const int &v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

int c[N];

IL void modify(rg int p, const int &x) {
  for (; p <= n; p += lowbit(p)) c[p] += x;
}

IL int query(rg int p) {
  rg int res = 0;
  for(; p; p -= lowbit(p)) res += c[p];
  return res;
}

int d[N], f[N], sz[N], son[N];

 void dfs1(int u, int fa){
  sz[u] = 1;
  for (rg int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) {
      d[v] = d[u] + 1; f[v] = u;
      dfs1(v, u); sz[u] += sz[v];
      if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

int cnt, dfn[N], top[N];

 void dfs2(int u,int fa) {
  dfn[u] = ++cnt;
  if (!top[u]) top[u] = u;
  if (son[u]) top[son[u]] = top[u], dfs2(son[u], u);
  for (rg int i = hd[u], v; i; i = e[i].nxt)
    if (!dfn[v = e[i].to]) dfs2(v, u);
}

IL int lca(int u, int v) {
  while (top[u] != top[v]) {
    if (d[top[u]] < d[top[v]]) swap(u, v);
    u = f[top[u]];
  }
  return (d[u] > d[v] ? v : u);
}

IL int sumx(int u, int v) {
  int res =0 ;
  while (top[u] != top[v]) {
    if (d[top[u]] < d[top[v]]) swap(u, v);
    res += query(dfn[u]) - query(dfn[top[u]] - 1);
    u = f[top[u]];
  }
  if (d[u] < d[v]) swap(u, v);
  res += query(dfn[u]) - query(dfn[v] - 1);
  return res;
}

int totq, totc, ans[N];

struct Q {
  int id, u, v, x;
} q[N * 3], ql[N * 3], qr[N * 3];

void solve(int l, int r, int st, int ed) {
  if (st > ed) return;
  if (l == r) {
    for (rg int i = st; i <= ed; ++i)
      if (q[i].id > 0) ans[q[i].id] = l;
    return;
  }
  int mid = (l + r) >> 1, totl = 0, totr = 0;
  for (rg int i = st; i <= ed; ++i)
    if(q[i].id <= 0) {
      if (q[i].x <= mid) ql[++totl] = q[i];
      else {
        qr[++totr] = q[i];
        modify(dfn[q[i].u], q[i].id < 0 ? -1 : 1);
      }
    }
    else {
      int res = sumx(q[i].u, q[i].v);
      if (res >= q[i].x) qr[++totr] = q[i];
      else q[i].x -= res, ql[++totl] = q[i];
    }
  for (rg int i = 1; i <= totr; ++i)
    if(qr[i].id <= 0) modify(dfn[qr[i].u], qr[i].id < 0 ? 1 : -1);
  for (rg int i = 1; i <= totl; ++i) q[st + i - 1] = ql[i];
  for (rg int i = 1; i <= totr; ++i) q[st + totl + i - 1] = qr[i];
  solve(l, mid, st, st + totl - 1);
  solve(mid + 1, r, st + totl, ed);
}

int main() {
  n = rd(); m = rd();
  for (rg int i = 1; i <= n; ++i) {
    mx = max(mx, w[i] = rd());
    q[++totq] = (Q){0, i, 0, w[i]};
  }
  for (rg int i = 1; i < n; ++i) add(rd(), rd());
  dfs1(1, 0); dfs2(1, 0);
  for (rg int i = 1, op, u, v; i <= m; ++i) {
    op = rd(); u = rd(); v =rd();
    if (!op) {
      mx = max(mx, v);
      q[++totq] = (Q){-1, u, 0, w[u]};
      q[++totq] = (Q){0, u, 0, w[u] = v};
    }
    else {
      ++totc;
      if (op > d[u] + d[v] - d[lca(u, v)] * 2 + 1) ans[totc] = -1;
      else q[++totq] = (Q){totc, u, v, op};
    }
  }
  solve(0, mx, 1, totq);
  for (rg int i = 1; i <= totc; ++i)
    if(ans[i] != -1) { print(ans[i]); putchar('\n'); }
    else puts("invalid request!");
  return 0;
}
