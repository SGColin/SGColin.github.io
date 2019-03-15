#include <bits/stdc++.h>
#define M 20
#define N 1000005
#define mod 998244353
using namespace std;
typedef long long ll;

inline int rd() {
  int x = 0;
  char c = getchar();
  while (!isdigit(c)) c = getchar();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = getchar();
  }
  return x;
}

inline int mo(int x) {
  if (x < 0) x += mod;
  return x >= mod ? x - mod : x;
}

inline void mul(int &x, int y) {
  x = 1ll * x * y % mod;
}

int qpow(int x, int t = mod - 2) {
  int res = 1;
  while (t) {
    if (t & 1) mul(res, x);
    mul(x, x); t >>= 1;
  }
  return res;
}

int n, m, tot, hd[N];

struct E{int to, nxt;} e[N << 1];

int fa[N], sz[N], bs[N], dep[N], topf[N];

void dfs1(int u, int fafa) {
  sz[u] = 1;
  fa[u] = fafa;
  dep[u] = dep[fafa] + 1;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fafa) {
      dfs1(v, u); sz[u] += sz[v];
      if (sz[v] > sz[bs[u]]) bs[u] = v;
    }
}

void dfs2(int u, int fafa, int tftf) {
  topf[u] = tftf;
  if (bs[u]) dfs2(bs[u], u, tftf);
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fafa && v != bs[u]) dfs2(v, u, v);
}

int lca(int u, int v) {
  while (topf[u] != topf[v]) {
    if (dep[topf[u]] < dep[topf[v]]) swap(u, v);
    u = fa[topf[u]];
  }
  return dep[u] < dep[v] ? u : v;
}

int lstson(int u, int v) {
  if (u == v) return 0;
  while (topf[u] != topf[v]) {
    if (fa[topf[u]] == v) return topf[u];
    u = fa[topf[u]];
  }
  return bs[v];
}

map<ll, int> mp, zmp;

int z1[N], z2[N], tag1[N], tag2[N];

inline ll gethash(ll x, ll y) {
  if (x > y) swap(x, y);
  return 1000000000ll * x + y;
}

struct Q {int u, v, x, y, l, p, np;} q[N];

inline void mark(Q nw) {
  if (nw.np) {
    int inv = qpow(nw.np);
    if (nw.x) {
      mul(tag1[nw.x], nw.np);
      mul(tag2[nw.u], nw.np); mul(tag2[nw.x], inv);
    }
    if (nw.y) {
      mul(tag1[nw.y], nw.np);
      mul(tag2[nw.v], nw.np); mul(tag2[nw.y], inv);
    }
    if (nw.x && nw.y) {
      ll t = gethash(nw.x, nw.y);
      if (mp.count(t)) mul(mp[t], inv);
      else mp[t] = inv;
    }
  } else {
    if (nw.x) {
      ++z1[nw.x];
      ++z2[nw.u]; --z2[nw.x];
    }
    if (nw.y) {
      ++z1[nw.y];
      ++z2[nw.v]; --z2[nw.y];
    }
    if (nw.x && nw.y) --zmp[gethash(nw.x, nw.y)];
  }
}

void dfs(int u, int fafa) {
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fafa) {
      mul(tag1[v], tag1[u]); z1[v] += z1[u];
      dfs(v, u);
      mul(tag2[u], tag2[v]); z2[u] += z2[v];
    }
}

inline int calc(Q nw) {
  int ans = nw.p, die = 0;
  if (nw.x) {
    die += z1[nw.u] - z1[nw.l] + z2[nw.x];
    mul(ans, tag1[nw.u]); mul(ans, qpow(tag1[nw.l]));
    mul(ans, tag2[nw.x]);
  }
  if (nw.y) {
    die += z1[nw.v] - z1[nw.l] + z2[nw.y];
    mul(ans, tag1[nw.v]); mul(ans, qpow(tag1[nw.l]));
    mul(ans, tag2[nw.y]);
  }
  if (nw.x && nw.y) {
    ll t = gethash(nw.x, nw.y);
    if (mp.count(t)) mul(ans, mp[t]);
    if (zmp.count(t)) die += zmp[t];
  }
  if (nw.np) {mul(ans, qpow(nw.np));}
  else --die;
  return die ? 0 : ans;
}

int main() {
  n = rd(); m = rd();
  for (int i = 1, u, v; i < n; ++i) {
    u = rd(); v = rd();
    e[++tot] = (E){v, hd[u]}; hd[u] = tot;
    e[++tot] = (E){u, hd[v]}; hd[v] = tot;
  }
  dfs1(1, 0); dfs2(1, 0, 1);
  for (int i = 0; i < N; ++i) tag1[i] = tag2[i] = 1;
  for (int i = 1; i <= m; ++i) {
    q[i].u = rd(); q[i].v = rd();
    q[i].p = rd(); q[i].np = mo(1 - q[i].p);
    swap(q[i].p, q[i].np);
    q[i].l = lca(q[i].u, q[i].v);
    q[i].x = lstson(q[i].u, q[i].l);
    q[i].y = lstson(q[i].v, q[i].l);
    mark(q[i]);
  }
  int sum = 0;
  dfs(1, 0);
  for (int i = 1; i <= m; ++i) sum = mo(sum + calc(q[i]));
  printf("%d\n", sum);
  return 0;
}
