#include <bits/stdc++.h>
#define N 107
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

int n, m, l, a[N], b[N], c[N];

inline bool check(int pos) {
	for (int i = 1; i < pos; ++i)
		if (b[i] == 0) return 0;
	for (int i = pos + l; i <= m; ++i)
		if (b[i] == 0) return 0;
	for (int i = 1; i <= l; ++i)
		if (b[pos + i - 1] != c[i]) return 0;
	return 1;
}

int main() {
	ll x = rd();
	ll y = rd();
	if (x == y) {puts("YES"); return 0;}
	while (x) {a[++n] = (x & 1); x >>= 1;}
	reverse(a + 1, a + 1 + n);
	while (y) {b[++m] = (y & 1); y >>= 1;}
	reverse(b + 1, b + 1 + m);
	l = n;
	for (int i = 1; i <= n; ++i) c[i] = a[i];
	while (c[l] == 0) --l;
	// for (int i = 1; i <= n; ++i) printf("%d", a[i]); puts("");
	// for (int i = 1; i <= m; ++i) printf("%d", b[i]); puts("");
	// for (int i = 1; i <= l; ++i) printf("%d", c[i]); puts("");
	for (int i = 1; i <= m - l + 1; ++i)
		if (check(i)) {puts("YES"); return 0;}
	reverse(c + 1, c + 1 + l);
	for (int i = 1; i <= m - l + 1; ++i)
		if (check(i)) {puts("YES"); return 0;}
	l = n;
	for (int i = 1; i <= n; ++i) c[i] = a[i];
	c[++l] = 1;
	for (int i = 1; i <= m - l + 1; ++i)
		if (check(i)) {puts("YES"); return 0;}
	reverse(c + 1, c + 1 + l);
	for (int i = 1; i <= m - l + 1; ++i)
		if (check(i)) {puts("YES"); return 0;}
	puts("NO");
	return 0;
}