#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 100005
#define gc getchar
#define mid ((c[rt].l + c[rt].r) >> 1)
using namespace std;
using std::cin;
using std::cout;
using std::endl;
namespace IN {
    const int MAX_INPUT = 1000000;
    #define getc() (p1 == p2 && (p2 = (p1 = buf) + inbuf -> sgetn(buf, MAX_INPUT), p1 == p2) ? EOF : *p1++)
    char buf[MAX_INPUT], *p1, *p2;
    template <typename T> inline bool redi(T &x) {
        static std::streambuf *inbuf = cin.rdbuf();
        x = 0;
        register int f = 0, flag = false;
        register char ch = getc();
        while (!std::isdigit(ch)) {
            if (ch == '-') f = 1;
        ch = getc();
        }
        if (std::isdigit(ch)) x = x * 10 + ch - '0', ch = getc(),flag = true;
        while (std::isdigit(ch)) {
            x = x * 10 + ch - 48;
            ch = getc();
        }
        x = f ? -x : x ;
        return flag;
    }
    template <typename T,typename ...Args> inline bool redi(T& a,Args& ...args) {
       return redi(a) && redi(args...);
    }
    #undef getc
}

namespace OUT {
    template <typename T> inline void put(T x) {
        static std::streambuf *outbuf = cout.rdbuf();
        static char stack[21];
        static int top = 0;
        if (x < 0) {
            outbuf -> sputc('-');
            x=-x;
        }
        if (!x) {
            outbuf -> sputc('0');
            outbuf -> sputc('\n');
            return;
        }
        while (x) {
            stack[++top] = x % 10 + '0';
            x /= 10;
        }
        while (top) {
            outbuf -> sputc(stack[top]);
            -- top;
        }
        outbuf -> sputc('\n');
    }
    inline void putc (const char ch) {
        static std::streambuf *outbuf = cout.rdbuf();
        outbuf -> sputc(ch);
    }
    template <typename T> inline void put(const char ch,T x)
    {
        static std::streambuf *outbuf = cout.rdbuf();
        static char stack[21];
        static int top = 0;
        if (x < 0) {
            outbuf -> sputc('-');
            x=-x;
        }
        if (!x) {
            outbuf -> sputc('0');
            outbuf -> sputc(ch);
            return;
        }
        while (x) {
            stack[++top] = x % 10 + '0';
            x /= 10;
        }
        while (top) {
            outbuf -> sputc(stack[top]);
            --top;
        }
        outbuf -> sputc(ch);
    }
    template<typename T,typename ...Args> inline void put(T a,Args ...args) {
        put(a);put(args...);
    }
    template<typename T,typename ...Args> inline void put(const char ch,T a,Args ...args) {
        put(ch,a);put(ch,args...);
    }
}
using IN::redi;
using OUT::put;
using OUT::putc;

int n, m, w[N], tot, hd[N];

struct edge{int to, nxt;} e[N << 1];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

int f[N][2], g[N][2];

int fa[N], sz[N], son[N];

int cnt, dfn[N], id[N], top[N], ed[N];

struct matrix{
  int a[2][2];
  matrix(){a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0;}
  matrix operator * (const matrix &x) {
    matrix res;
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 2; ++j)
        for (int k = 0; k < 2; ++k)
          res.a[i][j] = max(res.a[i][j], a[i][k] + x.a[k][j]);
    return res;
  }
} v[N << 1];

void dfs1(int u) {
  sz[u] = 1;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa[u]) {
      fa[v] = u;
      dfs1(v); sz[u] += sz[v];
      if (sz[son[u]] < sz[v]) son[u] = v;
    }
}

void dfs2(int u) {
  id[dfn[u] = ++cnt] = u;
  if (!top[u]) top[u] = u;
  ed[top[u]] = u;
  if (son[u]) top[son[u]] = top[u], dfs2(son[u]);
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa[u] && v != son[u]) dfs2(v);
}

void dfs(int u) {
  f[u][1] = g[u][1] = w[u];
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa[u]) {
      dfs(v);
      f[u][0] += max(f[v][0], f[v][1]), f[u][1] += f[v][0];
      if (v != son[u]) g[u][0] += max(f[v][0], f[v][1]), g[u][1] += f[v][0];
    }
}

int ptr, rot[N];

struct node{int l, r, ls, rs;} c[N << 1];

void build(int &rt, int l, int r, int x) {
  rt = ++ptr;
  c[rt].l = l; c[rt].r = r;
  if (l == r) {
    v[rt].a[0][0] = v[rt].a[0][1] = g[id[l + x - 1]][0];
    v[rt].a[1][0] = g[id[l + x - 1]][1];
    return;
  }
  build(c[rt].ls, l, mid, x);
  build(c[rt].rs, mid + 1, r, x);
  v[rt] = v[c[rt].ls] * v[c[rt].rs];
}

void updata(int rt, int x, int u) {
  if (c[rt].l == c[rt].r) {
    v[rt].a[0][0] = v[rt].a[0][1] = g[u][0];
    v[rt].a[1][0] = g[u][1];
    return;
  }
  x <= mid ? updata(c[rt].ls, x, u) : updata(c[rt].rs, x, u);
  v[rt] = v[c[rt].ls] * v[c[rt].rs];
}

inline void modify(int u, int x) {
  g[u][1] += x - w[u]; w[u] = x;
  matrix lst, nw;
  while (u) {
    lst = v[rot[top[u]]];
    updata(rot[top[u]], dfn[u] - dfn[top[u]] + 1, u);
    nw = v[rot[top[u]]];
    u = fa[top[u]];
    g[u][0] += max(nw.a[0][0], nw.a[1][0]) - max(lst.a[0][0], lst.a[1][0]);
    g[u][1] += nw.a[0][0] - lst.a[0][0];
  }
}

int main() {
  redi(n, m);
  for (int i = 1; i <= n; ++i) redi(w[i]);
  for (int i = 1, a, b; i < n; ++i) {redi(a, b); add(a, b);}
  dfs1(1); dfs2(1); dfs(1);
  for (int i = 1; i <= n; ++i)
    if (i == top[i]) build(rot[i], 1, dfn[ed[i]] - dfn[i] + 1, dfn[i]);
  for (int i = 1, u, x; i <= m; ++i) {
    redi(u, x); modify(u, x);
    put(max(v[rot[1]].a[0][0], v[rot[1]].a[1][0]));
  }
  return 0;
}
