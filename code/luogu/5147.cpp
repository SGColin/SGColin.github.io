#include <cmath>
#include <cstdio>
using namespace std;

int n;

double ans, e = 0.57721566490153286060651209;

int main() {
  scanf("%d", &n);
  ans = (n > 1);
  if (n <= 1000000) {
    for (int i = 1; i < n; ++i) ans += 1.0 / (double) i;
    printf("%.5lf", ans);
  } else printf("%.5lf\n", 1.0 + log(n) + e);
  return 0;
}
