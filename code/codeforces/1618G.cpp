#include <bits/stdc++.h>
#define N 400007
#define pii pair<int, int>
#define fr first
#define sc second
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;

inline ll rd() {
	ll x = 0;
	bool f = 0;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) f |= (c == '-');
	for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	return f ? -x : x;
}

int n, m, k, a[N], pos[N], b[N];

int fa[N], cnt[N];

int find(int x) {
	return x == fa[x] ? x : (fa[x] = find(fa[x]));
}

ll nw, sum[N], ans[N];

inline bool cmp(int x, int y) {return a[x] < a[y];}

vector<pii> dlt, qry;

inline ll pro(int x) {
	return sum[x] - sum[x - cnt[x]];
}

inline void merge(int x) {
	int y = find(x + 1);
	nw -= pro(x);
	nw -= pro(y);
	fa[x] = y;
	cnt[y] += cnt[x];
	nw += pro(y);
}

int main() {
	//pos[i]: the real postition of the number ranked i
	n = rd(); m = rd(); k = rd(); 
	for (int i = 1; i <= n + m; ++i) pos[i] = i, a[i] = rd();
	sort(pos + 1, pos + 1 + n + m, cmp);
	for (int i = 1; i <= n + m; ++i) {
		fa[i] = i; 
		cnt[i] = (pos[i] <= n);
		sum[i] = sum[i - 1] + a[pos[i]];
		if (i < n + m) dlt.pb(mp(a[pos[i + 1]] - a[pos[i]], i));
	}
	sort(dlt.begin(), dlt.end());
	for (int i = 1; i <= k; ++i) qry.push_back(mp(rd(), i));
	sort(qry.begin(), qry.end());
	for (int i = 1; i <= n; ++i) nw += a[i];
	for (int i = 0, ptr = 0; i < k; ++i) {
		while (ptr < dlt.size() && dlt[ptr].fr <= qry[i].fr) {
			merge(dlt[ptr].sc); ++ptr;
		}
		ans[qry[i].sc] = nw;
	}
	for (int i = 1; i <= k; ++i) printf("%lld\n", ans[i]);
	return 0;
}