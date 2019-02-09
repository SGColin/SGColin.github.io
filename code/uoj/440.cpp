#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define gc getchar
#define mod 1000000007
using namespace std;

inline int qpow(int x, int t) {
  int res = 1;
  while (t) {
    if (t & 1) res = 1ll * res * x % mod;
    x = 1ll * x * x % mod; t >>= 1;
  }
  return res;
}

int ans[9] = {0, 2, 12, 112, 912, 7136, 56768, 453504, 3626752};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  if (n > m) swap(n, m);
  if (n == m) printf("%d\n", ans[n]);
  else if (n == 1) printf("%d\n", qpow(2, m));
  else {
    int tmp = ans[n] * 3 - (n > 3) * 3 * qpow(2, n);
    printf("%lld\n", 1ll * tmp * qpow(3, m - n - 1) % mod);
  }
  return 0;
}
