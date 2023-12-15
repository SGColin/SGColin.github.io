#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

inline int rd() {
    int x = 0;
    bool f = 0;
    char c = getchar();
    for (; !isdigit(c); c = getchar()) f |= (c == '-');
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    return f ? -x : x;
}

#define eb emplace_back
#define all(s) (s).begin(), (s).end()
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)

#define N 200007

char s[N];

int n, m, k, pre[N], sum[N], dp[N][6], mn[N][6];

int main() {
	n = rd(); m = rd(); k = rd();
	scanf("%s", s + 1);
	int lst = 0;
	rep(i, 1, n) {
		pre[i] = lst;
		sum[i] = sum[i - 1];
		if (s[i] == '0') {lst = i; ++sum[i];}
	} 
	auto valid = [&](int l) {
		rep(i, 0, n) rep(j, 1, k) dp[i][j] = 1e9;
		rep(j, 1, k) mn[0][j] = dp[0][j];
		rep(i, 1, n) {
			if (i >= l && (i == n || s[i + 1] == '0')) {
				rep(j, 1, k) 
					dp[i][j] = min(dp[i][j], mn[max(0, pre[i - l + 1] - 1)][j - 1] + sum[i] - sum[i - l]);
				if (dp[i][k] <= m) return true;
			}
			rep(j, 1, k) mn[i][j] = min(mn[i - 1][j], dp[i][j]);
		}
		return false;
	};
	if (!valid(1)) {puts("-1"); return 0;}
	int l = 1, r = n;
	while (l < r) {
		int mid = (l + r + 1) / 2;
		valid(mid) ? l = mid : r = mid - 1;
	}
	printf("%d\n", l);
	return 0;
}