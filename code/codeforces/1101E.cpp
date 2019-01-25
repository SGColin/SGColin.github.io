#include <set>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 200010
#define gc getchar
#define rg register
using namespace std;

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

int n, x, y, mx1, mx2;

int main() {
  n = rd();
  char c;
	while (n--) {
		c = gc();
		while (c != '+' && c != '?') c = gc();
		x = rd(); y = rd();
		if (c == '+') {
			mx1 = max(mx1, min(x, y));
			mx2 = max(mx2, max(x, y));
		}
		else {
			if (mx1 > min(x, y) || mx2 > max(x, y)) puts("NO");
			else puts("YES");
		}
	}
  return 0;
}
