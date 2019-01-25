#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 1000005
#define gc getchar
#define rg register
#define mod 1000000007
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

int n, k, ans, pw[N], inv[N], fac[N], invfac[N];

inline int C(int n, int m) {
  return 1ll * fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
  n = rd(); k = rd();
  inv[0] = inv[1] = 1;
  fac[0] = fac[1] = 1;
  invfac[0] = invfac[1] = 1;
  pw[0] = 1; pw[1] = 2;
  for (rg int i = 2; i <= n; ++i) {
    fac[i] = (1ll * fac[i-1] * i) % mod;
    inv[i] = (1ll * (mod - mod / i) * inv[mod % i]) % mod;
    invfac[i] = (1ll * invfac[i - 1] * inv[i]) % mod;
    pw[i] = pw[i - 1] * 2 % mod;
  }
  for (rg int i = n, tmp = 2, x; i >= k; --i) {
    x = 1ll * C(i, k) * C(n, i) % mod * (tmp - 1) % mod;
    ans = ((ans + (((i - k) & 1) ? -1 : 1) * x) % mod + mod) % mod;
    tmp = (1ll * tmp * tmp) % mod;
  }
  printf("%d\n", ans);
  return 0;
}
