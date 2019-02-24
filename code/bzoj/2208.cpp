#include <cmath>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 2005
#define gc getchar
using namespace std;

char c;

int n, ans;

bitset<N> f[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      c = gc();
      while(!isdigit(c)) c = gc();
      f[i][j] = c - '0';
    }
  for (int i =1; i <= n; ++i) f[i][i] = 1;
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      if (f[i][k]) f[i] |= f[k];
  for (int i = 1; i <= n; ++i) ans += f[i].count();
  printf("%d\n",ans);
  return 0;
}
