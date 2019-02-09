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

inline int rd() {
  int x = 0;
  bool f = 0;
  char c = gc();
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

int n, res;

int main() {
  n = rd();
  for (int i = 1, lst = 0, x; i <= n; ++i) {
    x = rd();
    res += max(0, x - lst);
    lst = x;
  }
  printf("%d\n", res);
  return 0;
}
