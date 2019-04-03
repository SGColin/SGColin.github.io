#include <bits/stdc++.h>
#define N 5000005
#define mod 1000000007
using namespace std;

inline int rd() {
  int x = 0;
  char c = getchar();
  while (!isdigit(c)) c = getchar();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = getchar();
  }
  return x;
}

inline int qpow(int x, int t) {
  int res = 1;
  while (t) {
    if (t & 1) res = 1ll * res * x % mod;
    x = 1ll * x * x % mod; t >>= 1;
  }
  return res;
}

int n, pre[N], invpre[N];

int main() {
  n = rd();
  pre[0] = 1;
  for (int i = 1; i <= n; ++i) pre[i] = 1ll * pre[i - 1] * rd() % mod;
  invpre[n] = qpow(pre[n], mod - 2);
  for (int i = n; i; --i) {

  }
  return 0;
}
