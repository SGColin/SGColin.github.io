#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define gc getchar
using namespace std;
typedef long long ll;

ll n1, n2, m1, m2;

int main() {
  scanf("%I64d%I64d%I64d%I64d",&n1,&m1,&n2,&m2);
  printf("%I64d\n", (n2 + m1 + m2) * 2 + 4);
  return 0;
}
