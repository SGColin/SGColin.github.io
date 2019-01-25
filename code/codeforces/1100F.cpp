#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 500005
#define gc getchar
#define rg register
#define mid ((l+r) >> 1)
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

int n, m, a[N], ans[N];

struct BIT{
  int x,t;
}bit[31];

struct Q{int id,l,r;}q[N];

inline bool cmp(Q x, Q y) {
  return x.r < y.r;
}

inline void insert(int x,int t){
  for (rg int i = 30; ~i; --i) {
    if (x & (1 << i )) {
      if(t > bit[i].t) {
        int tmp = bit[i].x;
        int tmpt = bit[i].t;
        bit[i].t = t;
        bit[i].x = x;
        x = tmp ^ bit[i].x; t = tmpt;
      }
      else x ^= bit[i].x;
    }
  }
}

inline int query(int p){
  int res = 0;
  for (rg int i = 30; ~i; --i)
    if(bit[i].t >= p) {
      if(res < (res ^ bit[i].x)) res = res ^ bit[i].x;
    }
  return res;
}

int main() {
  n = rd();
  for (rg int i = 1; i <= n; ++i) a[i] = rd();
  m = rd();
  for (rg int i = 1; i <= m; ++i) {
    q[i].id = i; q[i].l = rd(); q[i].r = rd();
  }
  sort(q + 1, q + 1 + m, cmp);
  for (rg int i = 1, ptr = 1; i <= n; ++i) {
    insert(a[i],i);
    while (q[ptr].r == i) {
      ans[q[ptr].id] = query(q[ptr].l);
      ++ptr;
    }
  }
  for (rg int i = 1; i <= m; ++i) printf("%d\n",ans[i]);
  return 0;
}
