#include <bits/stdc++.h>
#define mod 1000000007
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

map<ll, ll> f, nul;

inline void work() {
	f = nul;
	int n = rd();
	ll ans = 1, tot = 0, tmp;
	for (int i = 1, x; i <= n; ++i) {
		tmp = (ans - f[-tot] + mod) % mod;
		f[-tot] = (f[-tot] + tmp) % mod;
		ans = (ans + tmp) % mod;
		tot += rd();
	}
	printf("%lld\n", ans);
}

int main(){
	nul[0] = 1;
	int t = rd();
	while(t--) work();
    return 0;
}