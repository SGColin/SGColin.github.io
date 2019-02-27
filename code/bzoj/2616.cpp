
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 505
#define M 1000005
#define gc getchar
#define mod 1000000007
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

int fac[M], ifac[M], inv[M];

int n, m, a[N], stk[N], top;

int ch[N][2], h[N], f[N][N], tmp[N];

inline int mo(int x) {
   return x >= mod ? x - mod : x;
}

inline void init() {
   inv[0] = inv[1] = 1;
   fac[0] = fac[1] = 1;
   ifac[0] = ifac[1] = 1;
   for (int i = 2; i < M; ++i) {
       fac[i] = 1ll * fac[i - 1] * i % mod;
       inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
       ifac[i] = 1ll * ifac[i - 1] * inv[i] % mod;
   }
}

inline int C(int n, int m) {
   return n < m ? 0 : 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int dfs(int u) {
   f[u][0] = 1;
   int wid = 1;
   for (int i = 0, v; i <= 1; ++i)
       if ((v = ch[u][i]) != 0) {
           int swid = dfs(v);
           for (int j = 0; j <= wid + swid; ++j) tmp[j] = 0;
           for (int j = 0; j <= wid; ++j)
               for (int k = 0; k <= swid && j + k <= m; ++k)
                   tmp[j + k] = mo(tmp[j + k] + 1ll * f[u][j] * f[v][k] % mod);
           wid += swid;
           for (int j = 0; j <= wid; ++j) f[u][j] = tmp[j];
       }
   for (int i = min(m, wid); ~i; --i) {
       int sum = 0;
       for (int j = 0, nw; j <= i; ++j) {
           nw = 1ll * C(wid - (i - j), j) * C(h[u], j) % mod;
           nw = 1ll * nw * fac[j] % mod * f[u][i - j] % mod;
           sum = mo(sum + nw);
       }
       f[u][i] = sum;
   }
   return wid;
}

int main() {
   init();
   n = rd(); m = rd();
   for (int i = 1; i <= n; ++i) a[i] = rd();
   for (int i = 1; i <= n; ++i) {
       while (top && a[stk[top]] > a[i]) {
           ch[i][0] = stk[top]; -- top;
       }
       if (top) ch[stk[top]][1] = i;
       stk[++top] = i;
   }
   for (int i = 1; i <= n; ++i)
       for (int j = 0; j <= 1; ++j)
           if (ch[i][j]) h[ch[i][j]] = a[ch[i][j]] - a[i];
   h[stk[1]] = a[stk[1]];
   dfs(stk[1]);
   printf("%d\n", f[stk[1]][m]);
   return 0;
}
