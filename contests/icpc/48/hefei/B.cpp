#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tii;

inline int rd() {
	int x = 0;
	bool f = 0;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) f |= (c == '-');
	for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	return f ? -x : x;
}

#define N 507
#define mod 998244353

inline void add(int &a, int b) {a = (a + b >= mod ? a + b - mod : a + b);}

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)

int a[N], sum[N], dp[N][N], c[N][N];

int main() {
	int n = rd();
	rep(i, 1, n) sum[i] = sum[i - 1] + (a[i] = rd());
	c[0][0] = 1;
	rep(i, 1, sum[n]) {
		c[i][0] = 1;
		rep(j, 1, i) add(c[i][j], c[i - 1][j - 1] + c[i - 1][j]);
	}
	dp[0][0] = 1;
	rep(i, 0, n - 1) 
		rep(j, 0, sum[i]) if (dp[i][j]) {
			add(dp[i + 1][j], dp[i][j]);
			rep(k, j + 1, sum[i + 1] - 1) { 
				// If the boundary is complicated, use if instead of directly calculate
				int lb = max(0, a[i + 1] - (k - j)), ub = min(a[i + 1] - 1, sum[i + 1] - k - 1);
				rep(x, lb, ub) add(dp[i + 1][k], 1ll * dp[i][j] * c[k - j - 1][a[i + 1] - x - 1] % mod);
			}
		}
	int ans = 0;
	rep(i, 0, sum[n]) add(ans, dp[n][i]);
	printf("%d\n", ans);
	return 0;
}