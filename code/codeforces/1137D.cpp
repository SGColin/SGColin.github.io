#include <bits/stdc++.h>
using namespace std;

int cnt;

char s[20];

inline void rd() {
  fflush(stdout);
  scanf("%d", &cnt);
  for (int x = cnt; x; --x) scanf("%s", s);
}

int main() {
  do {
    puts("next 0 1"); rd();
    puts("next 0"); rd();
  } while (cnt == 3);
  do {
    puts("next 0 1 2 3 4 5 6 7 8 9"); rd();
  } while (cnt == 2);
  puts("done");
  return 0;
}
