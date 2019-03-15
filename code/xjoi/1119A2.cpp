#include <bits/stdc++.h>
using namespace std;

int n, cnt;

inline void work1() {
  if (n == 0) {puts("0 0"); return;}
  if (n == 1) {puts("1 2\n2 3\n3 4\n0 0"); return;}
  puts("1 2\n2 3");
  cnt = 4;
  while (n--) printf("3 %d\n", cnt++);
  puts("0 0");
}

inline void work2() {
  int x = 100;
  int y = n / 100 - 2;
  int rem = n - x * (y + 1) - y;
  puts("1 2"); cnt = 3;
  for (int i = 1; i <= x; ++i) {
    printf("1 %d\n", cnt); ++cnt;
  }
  for (int i = 1; i <= y + 1; ++i) {
    printf("2 %d\n", cnt); ++cnt;
  }
  for (int i = 1; i <= rem; ++i) {
    printf("%d %d\n", cnt - 1, cnt); ++cnt;
  }
  puts("0 0");
}

int main() {
  scanf("%d", &n);
  (n <= 497) ? work1() : work2();
  return 0;
}
