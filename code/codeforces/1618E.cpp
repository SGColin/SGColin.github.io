#include <bits/stdc++.h>
#define N 100007
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

ll n, b[N], a[N], dlt[N];

inline ll pre(ll x) {return (x == 1 ? n : x - 1);}

inline ll nxt(ll x) {return (x == n ? 1 : x + 1);}

inline void work() {
	n = rd();
	for (int i = 1; i <= n; ++i) b[i] = rd();
	a[1] = 0;
	ll sum = 0;
	for (int i = 1; i <= n; ++i) {
		dlt[i] = 2 * b[i] - b[pre(i)] - b[nxt(i)];
		if (dlt[i] % n != 0) {puts("NO"); return;}
		dlt[i] /= n; a[nxt(i)] = a[i] + dlt[i];
		if (i < n) sum += (n - i + 1) * a[nxt(i)];
	}
	sum = b[1] - sum;
	ll tot = 1ll * (n + 1) * n / 2;
	if (sum % tot != 0) {puts("NO"); return;}
	sum /= tot;
	for (int i = 1; i <= n; ++i) {
		a[i] += sum;
		if (a[i] < 1 || a[i] > 1000000000) {puts("NO"); return;}
	}
	puts("YES");
	for (int i = 1; i <= n; ++i) printf("%lld ", a[i]);
	puts("");
}

int main() {
	for (int t = rd(); t; --t) work();
	return 0;
}