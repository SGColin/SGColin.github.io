#include <bits/stdc++.h>
#define N 100007
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

int n, q, k, a[N];

ll sum[N];

int main(){
	n = rd();
	q = rd();
	k = rd();
	a[0] = 1;
	a[n + 1] = k;
	for (int i = 1; i <= n; ++i) a[i] = rd();
	for (int i = 1; i <= n; ++i) 
		sum[i] = sum[i - 1] + a[i + 1] - a[i - 1] - 2;
	for (int i = 1, l, r; i <= q; ++i) {
		l = rd(); r = rd();
		if (l == r) printf("%d\n", k - 1);
		else printf("%lld\n", sum[r - 1] - sum[l] + k - a[r - 1] - 1 + a[l + 1] - 2);
	}
    return 0;
}