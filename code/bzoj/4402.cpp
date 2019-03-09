#include <bits/stdc++.h>
#define N 4000005
#define mod 1000000007
using namespace std;

int n, m, ans, fac[N], inv[N], ifac[N];

inline int mo(int x) {return x >= mod ? x - mod : x;}

inline int C(int n, int m) {
  if (n == 0) return 1;
  if (n < m) return 0;
  return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int main() {
  fac[0] = fac[1] = 1;
  inv[0] = inv[1] = 1;
  ifac[0] = ifac[1] = 1;
  for (int i = 2; i < N; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    ifac[i] = 1ll * ifac[i - 1] * inv[i] % mod;
  }
  scanf("%d%d", &n, &m);
  if (n && m) ans = 1;
  for (int i = 2; i <= m; ++i) {
    ans = mo(ans + C((n - i) / 2 + i - 1, i - 1));
    ans = mo(ans + C((n - i - 1) / 2 + i - 1, i - 1));
  }
  printf("%d", ans);
  return 0;
}
