#include <bits/stdc++.h>
#define N 500007
using namespace std;
typedef long long ll;

inline int rd() {
	int x = 0;
	bool f = 0;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) 
		if (c == '-') f = 1;
	for(; isdigit(c); c = getchar())
		x = x * 10 + (c ^ 48);
	return f ? -x : x;
}

int n, a[N], cnt[N];

int l[N], r[N], f[N];

int main() {
	n = rd();
	for (int i = 1; i <= n; ++i) {
		a[i] = rd();
		if (!l[a[i]]) l[a[i]] = i;
		r[a[i]] = i;
	}
	for (int i = n; i; --i) {
		++cnt[a[i]];
		f[i] = f[i + 1];
		if (i != l[a[i]]) f[i] = max(f[i], cnt[a[i]]);
		else f[i] = max(f[i], cnt[a[i]] + f[r[a[i]] + 1]);
	}
	printf("%d\n", n - f[1]);
	return 0;
}