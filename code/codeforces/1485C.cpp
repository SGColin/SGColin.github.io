#include <bits/stdc++.h>
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

inline void work() {
	int a = rd();
	int b = rd();
	if (a == 1) {
		puts("0"); return;
	}
	ll lim = min((int)sqrt(a + 1), b);
	ll ans = lim * (lim - 1) / 2;
	for (int l = lim + 1, r, t; l <= b; l = r + 1) {
		t = (a / (l + 1));
		if (t == 0) break;
		r = min(b, a / t - 1);
		ans += 1ll * (r - l + 1) * t;
	}
	printf("%lld\n", ans);
}

int main(){
	int t = rd();
	while (t--) work();
    return 0;
}