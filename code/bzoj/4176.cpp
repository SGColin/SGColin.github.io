/*
Author: SGColin
Problem: BZOJ 4176
Algorithm: Mobius Inversion
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 6000005
#define mod 1000000007
using namespace std;

bool vis[N];

int n, mu[N], prm[N];

inline int mo(int x) {return x >= mod ? x - mod : x;}

inline void init() {
  mu[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) mu[i] = mod - 1, prm[++prm[0]] = i;
    for (int j = 1, k; j <= prm[0] && (k = i * prm[j]) < N; ++j) {
      vis[k] = 1;
      if (i % prm[j]) mu[k] = mod - mu[i];
      else {mu[k] = 0; break;}
    }
  }
  for (int i = 1; i < N; ++i) mu[i] = mo(mu[i] + mu[i - 1]);
}

map<int, int> s;

inline int gets(int x) {
  if (x < N) return mu[x];
  if (s.find(x) != s.end()) return s[x];
  int res = 1;
  for (int l = 2, r; l <= x; l = r + 1) {
    r = x / (x / l);
    res = (res - 1ll * (r - l + 1) * gets(x / l) % mod + mod) % mod;
  }
  return s[x] = res;
}

inline int getf(int x) {
  int res = 0;
  for (int l = 1, r; l <= x; l = r + 1) {
    r = x / (x / l);
    res = (res + 1ll * (r - l + 1) * (x / l)) % mod;
  }
  return res;
}

inline int sqr(int x) {return 1ll * x * x % mod;}

inline int calc(int l, int r) {
  return ((gets(r) - gets(l - 1)) % mod + mod) % mod;
}

int main() {
  init();
  scanf("%d", &n);
  int res = 0;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    res = (res + 1ll * sqr(getf(n / l)) * calc(l, r)) % mod;
  }
  printf("%d\n", res);
  return 0;
}
