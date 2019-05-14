/*
Author: SGColin
Problem: BZOJ 4566
Algorithm: Suffix Automaton
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 400005
using namespace std;
typedef long long ll;

char ss[N];

int n, tot = 1, lst = 1;

struct node {
  int fa, mx, sz, cnt, tr[26];
} c[N];

inline int newnode(int mx, int sz = 0) {
  c[++tot].mx = mx; c[tot].sz = sz; return tot;
}

inline void extend(int x) {
  int p = lst;
  int np = newnode(c[p].mx + 1, 1);
  lst = np;
  for (; p && !c[p].tr[x]; p = c[p].fa) c[p].tr[x] = np;
  if (!p) {c[np].fa = 1; return;}
  int q = c[p].tr[x];
  if (c[q].mx == c[p].mx + 1) c[np].fa = q;
  else {
    int nq = newnode(c[p].mx + 1);
    c[nq].fa = c[q].fa;
    for (int i = 0; i < 26; ++i) c[nq].tr[i] = c[q].tr[i];
    c[q].fa = c[np].fa = nq;
    for (; c[p].tr[x] == q; p = c[p].fa) c[p].tr[x] = nq;
  }
}

int bkt[N], seq[N];

inline void rsort() {
  for (int i = 1; i <= tot; ++i) ++bkt[c[i].mx];
  for (int i = 1; i <= tot; ++i) bkt[i] += bkt[i - 1];
  for (int i = 1; i <= tot; ++i) seq[bkt[c[i].mx]--] = i;
}

ll ans;

inline void match(int len) {
  int p = 1, x;
  int ptr = 1, nw = 0;
  while (ptr <= len) {
    x = ss[ptr] - 'a';
    if (c[p].tr[x]) {++nw; p = c[p].tr[x];}
    else {
      while (p && !c[p].tr[x]) p = c[p].fa;
      if (!p) p = 1, nw = 0;
      else {nw = c[p].mx + 1; p = c[p].tr[x];}
    }
    ++c[c[p].fa].cnt;
    ans += 1ll * (nw - c[c[p].fa].mx) * c[p].sz;
    ++ptr;
  }
}

int main() {
  scanf("%s", ss + 1);
  n = strlen(ss + 1);
  for (int i = 1; i <= n; ++i) extend(ss[i] - 'a');
  rsort();
  for (int i = tot; i; --i)
    c[c[seq[i]].fa].sz += c[seq[i]].sz;
  scanf("%s", ss + 1);
  n = strlen(ss + 1); match(n);
  for (int i = tot; i; --i)
    c[c[seq[i]].fa].cnt += c[seq[i]].cnt;
  for (int i = 1; i <= tot; ++i)
    ans += 1ll * c[i].cnt * c[i].sz * (c[i].mx - c[c[i].fa].mx);
  printf("%lld\n", ans);
  return 0;
}
