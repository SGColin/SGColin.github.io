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

char s[N], t[N];

int cnt[100];

inline void work() {

}

int main() {
	for (int t = rd(); t; --t) work();
	return 0;
}