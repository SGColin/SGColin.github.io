#include <bits/stdc++.h>
#define N 100005
#define inf 2000000000
#define rg register
using namespace std;

char buf[1 << 21], *p1 = buf, *p2 = buf;
inline int getc(){
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1<<21, stdin),p1 == p2)?EOF:*p1++;
}

inline int rd() {
    int ret = 0;
    char ch = getc();
    while (!isdigit(ch)) ch = getc();
    while (isdigit(ch)) {
      ret = ret * 10 + ch - 48;
      ch = getc();
    }
    return ret;
}

inline void print(int x){
  if (x < 0) putchar('-'), x = -x;
  rg int y = 10, len = 1;
  while (y <= x) {y *= 10; ++len;}
  while (len--) {y /= 10; putchar(x / y + 48); x %= y;}
  putchar('\n');
}

int n, m, tot = 1, totr, hd[N], hdr[N];

struct road{int to, nxt;} r[N << 2];

struct edge{int to, nxt, w;} e[N << 2];

inline void adde(int u, int v, int w = 0) {
  e[++tot].to = v; e[tot].w = w;
  e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].w = w;
  e[tot].nxt = hd[v]; hd[v] = tot;
}

inline void addr(int u, int v) {
  r[++totr].to = v; r[totr].nxt = hdr[u]; hdr[u] = totr;
}

bool br[N << 2];

int tcnt, tdfn[N], low[N];

vector<int> rem, u;

void tarjan(int u, int id) {
  tdfn[u] = low[u] = ++tcnt;
  for (rg int i = hd[u], v; i; i = e[i].nxt) {
    v = e[i].to;
    if (!tdfn[v]) {
        tarjan(v, i);
      low[u] = min(low[u], low[v]);
        if (low[v] > tdfn[u]) rem.push_back(i), br[i] = br[i ^ 1] = 1;
    } else if (i != (id ^ 1))   low[u] = min(low[u], tdfn[v]);
  }
}

int cnt_dcc, bl[N];

void dfs(int u) {
    bl[u] = cnt_dcc;
    for (rg int i = hd[u]; i; i = e[i].nxt)
        if (!bl[e[i].to] && !br[i]) dfs(e[i].to);
}

int d[N], f[N], sz[N], son[N], cnt_block, bl_block[N];

void dfs1(int u) {
  sz[u] = 1;
  bl_block[u] = cnt_block;
  for (rg int i = hdr[u], v; i; i = r[i].nxt)
    if ((v = r[i].to) != f[u]) {
      f[v] = u; d[v] = d[u] + 1;
      dfs1(v); sz[u] += sz[v];
      if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

int cnt, dfn[N], ed_dfn[N], topf[N];

void dfs2(int u) {
  dfn[u] = ++cnt;
  if (!topf[u]) topf[u] = u;
  if (son[u]) topf[son[u]] = topf[u], dfs2(son[u]);
  for (rg int i = hdr[u], v; i; i = r[i].nxt)
    if ((v = r[i].to) != f[u] && v != son[u]) dfs2(v);
  ed_dfn[u] = cnt;
}

inline int lca(int u, int v) {
  while (topf[u] != topf[v]) {
    if (d[topf[u]] < d[topf[v]]) swap(u, v);
    u = f[topf[u]];
  }
  return d[u] < d[v] ? u : v;
}

bool vis[N];

inline bool cmp(int x, int y) {return dfn[x] < dfn[y];}

int S, T, k, tots, s[N << 1], stk[N], top, ans;

void dfs3(int u, int sum) {
  vis[u] = 1;
  if (u == T) {ans = sum; return;}
  if (ans < inf) return;
  for (rg int i = hd[u], v; i; i = e[i].nxt) {
    v = e[i].to;
    if (!vis[v = e[i].to]) dfs3(v, sum + e[i].w * br[i]);
    if (ans < inf) return;
  }
}

inline int uniq() {
  int ptr = 0;
  for (rg int i = 1; i <= tots; ++i) {
    s[++ptr] = s[i];
    while (s[i] == s[i + 1] && i <= tots) ++i;
  }
  return ptr;
}

inline void work() {
  tot = 1;
  rem = u;
  tcnt = top = 0;
  S = bl[rd()]; T = bl[rd()]; k = rd();
  s[1] = S; s[tots = 2] = T;
  for (rg int i = 1, x, y; i <= k; ++i) {
    x = bl[rd()]; y = bl[rd()];
    s[++tots] = x; s[++tots] = y; adde(x, y, 1);
  }
  sort(s + 1, s + 1 + tots, cmp);
  tots = uniq();
  for (rg int i = 2, lim = tots; i <= lim; ++i)
    if (bl_block[s[i]] == bl_block[s[i - 1]]) s[++tots] = lca(s[i - 1], s[i]);
  sort(s + 1, s + 1 + tots, cmp);
  tots = uniq();
  for (rg int i = 1, u; i <= tots; ++i) {
    u = s[i];
    while (top && ed_dfn[stk[top]] < dfn[u]) --top;
    stk[++top] = u;
    if (top >= 2) adde(stk[top], stk[top - 1], d[stk[top]] - d[stk[top - 1]]);
  }
  for (rg int i = 1; i <= tots; i++)
    if (!tdfn[s[i]]) tarjan(s[i], 0);
  ans = inf; dfs3(S, 0);
  print(ans < inf ? ans : -1);
  for (rg int i = 1; i <= tots; ++i){
    vis[s[i]] = 0;
    hd[s[i]] = tdfn[s[i]] = low[s[i]] = 0;
  }
  for (int i = rem.size() - 1; ~i; --i) br[rem[i]] = br[rem[i] ^ 1] = 0;
}

int main() {
  n = rd(); m = rd();
  for (rg int i = 1; i <= m; ++i) adde(rd(), rd());
  for (rg int i = 1; i <= n; i++)
    if (!tdfn[i]) tarjan(i, 0);
  for (rg int i = 1; i <= n; i++)
    if (!bl[i]) {++cnt_dcc; dfs(i);}
  for (rg int i = 2, x, y; i <= tot; i++) {
    x = e[i].to; y = e[i ^ 1].to;
    if (bl[x] != bl[y]) addr(bl[x], bl[y]);
  }
  for (rg int i = 0; i <= n; ++i) hd[i] = tdfn[i] = low[i] = 0;
  for (rg int i = 0; i <= tot; ++i) br[i] = 0;
  for (rg int i = 1; i <= cnt_dcc; ++i)
    if(!dfn[i]) {++cnt_block; dfs1(i); dfs2(i);}
  int q = rd();
  while (q--) work();
  return 0;
}
