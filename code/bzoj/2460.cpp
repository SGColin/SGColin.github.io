#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1010
#define gc getchar
#define rg register
using namespace std;
typedef long long ll;

inline ll rd() {
  rg ll x = 0;
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

ll n, bit[62];

struct node { ll w; ll x; } c[N];

inline bool cmp(node x, node y) { return x.w > y.w; }

inline ll insert(ll x) {
  for (rg ll i = 61; ~i; --i)
    if (x & (1ll << i)) {
      if (!bit[i]) { bit[i] = x; return 1; }
      x ^= bit[i];
    }
  return 0;
}

int main() {
  n = rd();
  for (rg ll i = 1; i <= n; ++i) {
    c[i].x = rd(); c[i].w = rd();
  }
  ll ans = 0;
  sort(c + 1, c + 1 + n, cmp);
  for (rg ll i = 1; i <= n; ++i) ans += insert(c[i].x) * c[i].w;
  printf("%lld\n", ans);
  return 0;
}
