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

int main() {
  int n = rd();
  int s = rd();
  int d = rd();
  int x, y;
  for (int i = 1; i <= n; ++i){
    x = rd(); y = rd();
    if (x < s && y > d) {
      puts("Yes"); return 0;
    }
  }
  puts("No");
  return 0;
}