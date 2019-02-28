#include <bits/stdc++.h>
#define N 262145
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

void print(int x, bool f) {
  if (!x && f) return;
  print(x / 10, 1);
  putchar('0' + x % 10);
  if (!f) putchar(' ');
}

struct Complex {
  double x, y;
  Complex(double _x = 0, double _y = 0) {x = _x; y = _y;}
};

Complex operator + (const Complex &a, const Complex &b) {
  return Complex(a.x + b.x, a.y + b.y);
}

Complex operator - (const Complex &a, const Complex &b) {
  return Complex(a.x - b.x, a.y - b.y);
}

Complex operator * (const Complex &a, const Complex &b) {
  return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

const double PI = acos(-1.0), eps = 0.5;

Complex a[N], b[N];

int n, m, rev[N];

inline int Rev(int n) {
  int len = 1, bit = 0;
  while (len <= n) ++bit, len <<= 1;
  for (int i = 0; i < len; ++i)
    rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (bit - 1)));
  return len;
}

inline void FFT(Complex *f, int len, int o) {
    for (int i = 0; i < len; ++i)
      if (rev[i] > i) swap(f[i], f[rev[i]]);
    for (int i = 1; i < len; i <<= 1) {
      Complex wn = Complex(cos(PI / i) , o * sin(PI / i));
      for (int j = 0; j < len; j += (i << 1)) {
        Complex w = Complex(1, 0), x, y;
        for (int k = 0; k < i; ++k, w = w * wn) {
          x = f[j + k]; y = w * f[i + j + k];
          f[i + j + k] = x - y; f[j + k] = x + y;
        }
      }
    }
    if (o == -1) for (int i = 0; i < len; ++i) f[i].x /= len;
}

int main() {
  n = rd(); m = rd();
  for (int i = 0; i <= n; ++i) a[i].x = rd();
  for (int i = 0; i <= m; ++i) b[i].x = rd();
  int len = Rev(n + m);
  FFT(a, len, 1); FFT(b, len, 1);
  for (int i = 0; i < len; ++i) a[i] = a[i] * b[i];
  FFT(a, len, -1);
  for (int i = 0; i <= n + m; ++i) print((int)floor(a[i].x + eps), 0);
  return 0;
}
