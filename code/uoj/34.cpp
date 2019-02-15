#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 2100000
#define gc getchar
using namespace std;

inline int rd() {
  int x = 0;
  bool f = 0;
  char c = gc();
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

struct C {
  double x, y;
  C(double _x = 0, double _y = 0) {x = _x; y = _y;}
};

C operator + (const C &a, const C &b) {
  return C(a.x + b.x, a.y + b.y);
}

C operator - (const C &a, const C &b) {
  return C(a.x - b.x, a.y - b.y);
}

C operator * (const C &a, const C &b) {
  return C(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

const double PI = acos(-1.0), eps = 0.5;

C a[N], b[N], w[N];

int n, m, bit, rev[N];

inline int Rev(int x) {
  int res = 0;
  for (int i = 1; i <= bit; ++i) {
    res = ((res << 1) | (x & 1)); x >>= 1;
  }
  return res;
}

inline void FFT(C *f, int bit, int o) {
  for (int i = 0; i < (1 << bit); ++i)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  int W;
  for (int i = 1; i <= bit; ++i)
    for (int j = 0; j < (1 << bit); j += (1 << i)) {
      W = 0;
      for (int k = j; k < j + (1 << (i - 1)); ++k) {
        f[k] = f[k] + w[W] * f[k + (1 << (i - 1))];
        f[k + (1 << (i - 1))] = f[k] - w[W] * f[k + (1 << (i - 1))] - w[W] * f[k + (1 << (i - 1))];
        W += o * (1 << (bit - i));
        if (W < 0) W += (1 << bit);
      }
    }
}

int main() {
  n = rd(); m = rd();
  int len = max(n, m) * 2 + 2;
  for (int i = 0; i <= n; ++i) a[i].x = rd();
  for (int i = 0; i <= m; ++i) b[i].x = rd();
  while ((1 << bit) <= len) ++bit;
  for (int i = 0; i < (1 << bit); ++i)
    if (!rev[i]) rev[rev[i] = Rev(i)] = i;
  w[0].x = 1;
  w[1] = C(cos(2 * PI / (1 << bit)), sin (2 * PI / (1 << bit)));
  for (int i = 2; i < (1 << bit); ++i) w[i] = w[i - 1] * w[1];
  FFT(a, bit, 1);
  FFT(b, bit, 1);
  for (int i = 0; i < (1 << bit); ++i) a[i] = a[i] * b[i];
  FFT(a, bit, -1);
  for (int i = 0; i < (1 << bit); ++i) a[i].x /= (1 << bit);
  for (int i = 0; i <= n + m; ++i) printf("%d ", (int)floor(a[i].x + eps));
  return 0;
}
