#include <bits/stdc++.h>
#define N 100007
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

int main() {
  int a = rd();
  int b = rd();
  int c = rd();
  if (c == 1) --b;
  if (a > b) puts("Takahashi");
  else puts("Aoki");
  return 0;
}