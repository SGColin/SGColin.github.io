#include <bits/stdc++.h>
#define N 300007
#define inf 1000000007
using namespace std;
typedef long long ll;

inline int rd() {
  int x = 0;
  bool f = 0;
  char c = getchar();
  for (; !isdigit(c); c = getchar()) if (c == '-') f = 1;
  for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return f ? -x : x;
}

int n, c[N], a[N];

inline int lowbit(int x) {
  return x & (-x);
}

inline void add(int x) {
  for(; x < N; x += lowbit(x)) ++c[x];
}

inline int calc(int x) {
  int res = 0;
  for (; x; x -= lowbit(x)) res += c[x];
  return res;
}

int main() {
  int n = rd();
  ll res = 0;
  for (int i = 1; i <= n; ++i) a[i] = rd() + 1;
  for (int i = n; i; --i) {
    res += calc(a[i]); add(a[i]);
  }
  printf("%lld\n", res);
  for (int i = 1; i < n; ++i) {
    res += (n - a[i]) - a[i] + 1;
    printf("%lld\n", res); 
  }
  return 0;
}