#include <bits/stdc++.h>
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

int main() {
  ll n;
  scanf("%lld", &n);
  int ans = 0;
  for (ll len = 1; len <= 1e7; ++len) {
    ll sum = len * (len - 1) / 2;
    if (n <= sum) break;
    if ((sum - n) % len == 0) ++ans;
  }
  printf("%d\n", ans * 2);
  return 0;
}