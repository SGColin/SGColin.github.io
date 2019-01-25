#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 110
#define gc getchar
#define rg register
using namespace std;
typedef long long ll;

inline int rd() {
  rg int x = 0;
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

int s[N];

int main() {
  int n = rd(), k = rd(), sum = 0, ans = 0;
  for (rg int i = 1; i <= n; ++i) {
    s[i] = (rd() == 1);
    sum += (s[i] ? 1 : -1);
  }
  for (rg int b = 0; b <= n; ++b) {
    int cnt = 0;
    for (rg int i = 1; i <= n; ++i)
      if (abs(i - b) % k == 0) cnt += (s[i] ? -1 : 1);
    ans = max(ans, abs(sum + cnt));
  }
  printf("%d\n",ans);
  return 0;
}
