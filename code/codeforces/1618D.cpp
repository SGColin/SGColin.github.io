#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int rd() {
	int x = 0;
	bool f = 0;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) f |= (c == '-');
	for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	return f ? -x : x;
}

int a[107];

inline void work() {
	int n = rd();
	int k = rd();
	for (int i = 1; i <= n; ++i) a[i] = rd();
	sort(a + 1, a + 1 + n);
	int ans = 0;
	for (int i = 1; i <= n - 2 * k; ++i) ans += a[i];
	for (int i = 1; i <= k; ++i) ans += a[n - k - i + 1] / a[n - i + 1];
	printf("%d\n", ans);
}

int main() {
	for (int t = rd(); t; --t) work();
	return 0;
}