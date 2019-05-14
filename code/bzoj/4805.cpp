/*
Author: SGColin
Problem: BZOJ 4805
Algorithm: Dujiao sieve
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 5000005
using namespace std;
typedef long long ll;

inline int rd() {
  int x = 0;
  scanf("%d", &x);
  return x;
}

bool vis[N];

ll n, phi[N], prm[N];

inline void init() {
  phi[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!phi[i]) phi[i] = i - 1, prm[++prm[0]] = i;
    for (int j = 1, k; j <= prm[0] && (k = i * prm[j]) < N; ++j) {
      if (i % prm[j]) phi[k] = phi[i] * phi[prm[j]];
      else {phi[k] = phi[i] * prm[j]; break;}
    }
  }
  for (int i = 1; i < N; ++i) phi[i] += phi[i - 1];
}

map<int, ll> s;

inline ll gets(int x) {
  if (x < N) return phi[x];
  if (s.find(x) != s.end()) return s[x];
  ll res = 1ll * x * (x + 1) / 2;
  for (int l = 2, r; l <= x; l = r + 1) {
    r = x / (x / l);
    res -= 1ll * (r - l + 1) * gets(x / l);
  }
  return s[x] = res;
}

int main() {
  init();
  printf("%lld\n", gets(rd()));
  return 0;
}
