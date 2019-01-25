#include <set>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100010
#define gc getchar
#define rg register
using namespace std;

multiset<int> s;

inline int rd() {
  rg int x = 0;
  rg bool f = 0;
  rg char c = gc();
  while (!isdigit(c)) {
    if (c == '-') f = 1;
    c = gc();
  }
  while(isdigit(c)) {
    x = x * 10 + (c ^ 48);
    c = gc();
  }
  return f ? -x : x;
}

int n, m, nowans, cnt[N];

int main() {
  n = rd(); m = rd();
  for (rg int i = 1; i <= n; ++i) s.insert(0);
  for (rg int i = 1, x; i <= m; ++i) {
    x = rd();
    s.erase(s.find(cnt[x]));
    s.insert(++cnt[x]);
    if(*s.begin() > nowans) {
      ++nowans;
      putchar('1');
    }
    else putchar('0');
  }
  puts("");
  return 0;
}
