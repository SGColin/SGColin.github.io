#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 500005
using namespace std;

int n, h;

double c[N], mn, d, r = 0.0, eps = 1e-12;

struct P {
  double x, y;
} p[N], O;

inline double sqr(double x) {return x * x;}

inline double dis(P a, P b) {
  return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

inline bool inc(P x) {
  return dis(x, O) <= r + eps;
}

inline P calc(const P &x1,const P &x2,const P &x3) {
    P ans;
    double a = x2.x - x1.x, b = x2.y - x1.y;
    double c = x3.x - x2.x, d = x3.y - x2.y;
    double e = x2.x * x2.x + x2.y * x2.y - x1.x * x1.x - x1.y * x1.y;
    double f = x3.x * x3.x + x3.y * x3.y - x2.x * x2.x - x2.y * x2.y;
    ans.x = (f * b - e * d) / (c * b - a * d) / 2.0;
    ans.y = (a * f - e * c) / (a * d - b * c) / 2.0;
    return ans;
}
int main() {
  srand(23333);
  scanf("%d%d%lf%lf", &n, &h, &mn, &d);
  for (int i = 0; i <= h; ++i) scanf("%lf", &c[i]);
  for (int i = 1; i <= n; ++i)
    scanf("%lf%lf", &p[i].x, &p[i].y);
  for(int i = 1; i <= 20; ++i) random_shuffle(p + 1, p + 1 + n);
  for (int i = 1; i <= n; ++i)
    if (!inc(p[i])) {
      O = p[i]; r = 0.0;
      for (int j = 1; j < i; ++j)
        if (!inc(p[j])) {
          O = (P){(p[i].x + p[j].x) / 2, (p[i].y + p[j].y) / 2};
          r = dis(p[i], O);
          for (int k = 1; k < j; ++k)
            if (!inc(p[k])) {
              O = calc(p[i], p[j], p[k]);
              r = dis(p[i], O);
            }
        }
    }
  int ansh = 0;
  double ans = max((r - d), mn) * c[0], ansr = r - d;
  for (int i = 1; i <= h; ++i) {
    if (i > d) break;
    double dlt = sqrt(sqr(d) - sqr(i));
    double nw = max((r - dlt), mn) * c[i];
    if (nw < ans) {
      ansh = i; ansr = max(r - dlt, mn); ans = nw;
    }
  }
  printf("%.10lf\n%.10lf %.10lf %d %.10lf\n", ans, O.x, O.y, ansh, ansr);
  return 0;
}
