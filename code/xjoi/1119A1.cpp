#include <bits/stdc++.h>
using namespace std;

int n, nw, cnt = 1, ptr = 3;

int main() {
  scanf("%d", &n);
  if (n == 0) {puts("0 0"); return 0;}
  puts("1 2\n2 3");
  while (nw + 2 * cnt <= n) {
    nw += 2 * cnt; ++cnt; ptr += 2;
    printf("1 %d\n%d %d\n", ptr - 1, ptr - 1, ptr);
  }
  for (int i = nw; i < n; ++i, ++ptr, ++nw) printf("%d %d\n", ptr, ptr + 1);
  puts("0 0");
  return 0;
}
