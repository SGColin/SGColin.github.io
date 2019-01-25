#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 200010
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

int n, a[N], bit[31];

inline int insert(int x){
  for (rg int i = 30; ~i; --i) {
    if(x & (1 << i)) {
      if(!bit[i]) {
        bit[i] = x; return 1;
      }
      x ^= bit[i];
    }
  }
  return 0;
}

int main() {
  n = rd();
  for (rg int i = 1; i <= n; ++i) a[i] = rd() ^ a[i - 1];
  if (!a[n]){ puts("-1"); return 0; }
  int ans = insert(a[n]);
  for (rg int i = n - 1; i; --i) ans += insert(a[i]);
  printf("%d\n", ans);
  return 0;
}
