#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n;

int main() {
  scanf("%d", &n);
  puts(n & 1 ? "black" : "white\n1 2");
  return 0;
}
