#include <bits/stdc++.h>
#define N 500005
#define gc getchar
using namespace std;

inline int rd() {
  int x = 0;
  char c = gc();
  while (!isdigit(c)) c = gc();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = gc();
  }
  return x;
}

char s1[N], s2[N];

int len1, len2, cnt1[2], cnt2[2], nxt[N];

int main() {
  scanf("%s", s1 + 1);
  scanf("%s", s2 + 1);
  len1 = strlen(s1 + 1);
  len2 = strlen(s2 + 1);
  if (len1 < len2) {printf("%s", s1 + 1); return 0;}
  for (int i = 1; i <= len1; ++i) ++cnt1[s1[i] - '0'];
  for (int i = 1; i <= len2; ++i) ++cnt2[s2[i] - '0'];
  if (cnt1[0] < cnt2[0] || cnt1[1] < cnt2[1]) {printf("%s", s1 + 1); return 0;}
  for (int i = 2, j = 0; i <= len2; ++i) {
    while (j && s2[j + 1] != s2[i]) j = nxt[j];
    if (s2[j + 1] == s2[i]) ++j;
    nxt[i] = j;
  }
  int bd = nxt[len2];
  cnt1[0] -= cnt2[0];
  cnt1[1] -= cnt2[1];
  printf("%s", s2 + 1);
  for (int i = 1; i <= bd; ++i) --cnt2[s2[i] - '0'];
  while (1) {
    if (cnt1[0] < cnt2[0] || cnt1[1] < cnt2[1]) break;
    cnt1[0] -= cnt2[0]; cnt1[1] -= cnt2[1];
    for (int i = bd + 1; i <= len2; ++i) putchar(s2[i]);
  }
  while (cnt1[0]) {putchar('0'); --cnt1[0];}
  while (cnt1[1]) {putchar('1'); --cnt1[1];}
  return 0;
}
