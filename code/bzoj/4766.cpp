#include <cmath>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define gc getchar
using namespace std;
typedef long long ll;

ll n, m, mod;

inline ll mul(ll a, ll b) {
  ll res = 0;
  while (b) {
    if (b & 1) res = (res + a >= mod ? res + a - mod : res + a);
    a = (a + a >= mod ? a + a - mod : a + a); b >>= 1;
  }
  return res;
}


inline ll qpow(ll x, ll t) {
  ll res = 1;
  while (t) {
    if (t & 1) res = mul(res, x);
    x = mul(x, x); t >>= 1;
  }
  return res;
}

int main() {
  scanf("%lld%lld%lld", &n, &m, &mod);
  printf("%lld\n", mul(qpow(n, m - 1), qpow(m, n - 1)));
  return 0;
}
