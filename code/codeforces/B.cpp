#include <bits/stdc++.h>
#define N 107
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

ll f[41], sum[41];

inline void init() {
	f[0] = f[2] = 0; f[1] = 1; f[3] = f[4] = 4;
	for (int i = 5; i <= 40; ++i) 
		f[i] = 4ll * (f[i - 2] + f[i - 3] + f[i - 4]);
	for (int i = 1; i <= 40; ++i)
		sum[i] = sum[i - 1] + f[i];
}

int main() {
	//while (scanf("%d", &n) != EOF) work();
	init();
	for (int t = rd(); t; --t) printf("%lld\n", sum[rd()]);
	return 0;
}