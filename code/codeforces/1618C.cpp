#include <bits/stdc++.h>
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

ll a[107];

ll gcd(ll a, ll b) {return b ? gcd(b, a % b) : a;}

inline void work() {
	int n = rd();
	ll go = 0, ge = 0;
	for (int i = 1; i <= n; ++i) {
		a[i] = rd();
		(i & 1) ? go = gcd(go, a[i]) : ge = gcd(ge, a[i]);
	}
	bool fl = 0;
	for (int i = 2; i <= n; i += 2)
		if (a[i] % go == 0) {fl = 1; break;}
	if (!fl) {printf("%lld\n", go); return;}
	fl = 0;
	for (int i = 1; i <= n; i += 2)
		if (a[i] % ge == 0) {fl = 1; break;}
	printf("%lld\n", fl ? 0 : ge);
}

int main() {
	for (int t = rd(); t; --t) work();
	return 0;
}