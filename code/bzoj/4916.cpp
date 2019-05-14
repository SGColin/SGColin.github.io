/*
Author: SGColin
Problem: BZOJ 4916
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
#define inv 166666668
#define mod 1000000007
using namespace std;
typedef long long ll;

inline int rd() {
  int x = 0;
  scanf("%d", &x);
  return x;
}

bool vis[N];

int n, phi[N], prm[N];

inline int mo(int x) {return x >= mod ? x - mod : x;}

inline void init() {
  phi[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!phi[i]) phi[i] = i - 1, prm[++prm[0]] = i;
    for (int j = 1, k; j <= prm[0] && (k = i * prm[j]) < N; ++j) {
      if (i % prm[j]) phi[k] = 1ll * phi[i] * phi[prm[j]] % mod;
      else {phi[k] = 1ll * phi[i] * prm[j] % mod; break;}
    }
  }
  for (int i = 1; i < N; ++i) phi[i] = (1ll * phi[i] * i+ phi[i - 1]) % mod;
}

map<int, int> s;

inline int sqrs(int x) {
  return 1ll * x * (x + 1) % mod * (2 * x + 1) % mod * inv % mod;
}

inline int calc(int l, int r) {
  return 1ll * (l + r) * (r - l + 1) / 2 % mod;
}

inline int gets(int x) {
  if (x < N) return phi[x];
  if (s.find(x) != s.end()) return s[x];
  int res = sqrs(x);
  for (int l = 2, r; l <= x; l = r + 1) {
    r = x / (x / l);
    res = ((res - 1ll * calc(l, r) * gets(x / l)) % mod + mod) % mod;
  }
  return s[x] = res;
}

int main() {
  init();
  puts("1");
  printf("%d\n", gets(rd()));
  return 0;
}
