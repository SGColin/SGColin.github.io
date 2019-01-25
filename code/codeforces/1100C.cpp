#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100010
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

double n,r;

double pi = acos(-1);

int main() {
  scanf("%lf%lf",&n,&r);
  printf("%.10lf",r*sin(pi/n)/(1.0 - sin(pi/n)));
  return 0;
}
