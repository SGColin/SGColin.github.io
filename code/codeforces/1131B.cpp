#include <bits/stdc++.h>
#define gc getchar
using namespace std;

int n, ans;

int main() {
  scanf("%d", &n);
  for (int i = 1, x, y, lstx, lsty, lst; i <= n; ++i) {
    scanf("%d%d", &x, &y);
    ans += max(0, min(x, y) - max(lst, max(lstx, lsty)) + 1);
    lst = min(x, y) + 1;
    lstx = x; lsty = y;
	 }
  printf("%I64d\n", ans);
  return 0;
}
