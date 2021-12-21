#include <bits/stdc++.h>
#define N 100007
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

int n, a[N], ans[N];

inline int query(int a, int b, int c) {
	printf("? %d %d %d\n", a + 1, b + 1, c + 1);
	fflush(stdout);
	return rd();
}

inline void work() {
	int n = rd();
	for (int i = 0; i < n; ++i) a[i] = -1;
	for (int i = 0; i < n; ++i)
		ans[i] = query(i, (i + 1) % n, (i + 2) % n);
	int pos0, pos1, cnt = 0;
	for (int i = 0; i < n; ++i)
		if (ans[i] != ans[(i + 1) % n]) {
			if (ans[i] == 1) {
				a[i] = 1; a[(i + 3) % n] = 0;
			} else {
				a[i] = 0; a[(i + 3) % n] = 1;
			}
			if (a[i] != -1) {
				a[i] == 0 ? pos0 = i : pos1 = i;
			}
		}
	for (int i = 0; i < n; ++i) {
		if (a[i] == -1) a[i] = query(i, pos0, pos1);
		cnt += (a[i] == 0);
	}
	printf("! %d", cnt);
	for (int i = 0; i < n; ++i) 
		if (a[i] == 0) printf(" %d", i + 1);
	puts("");
	fflush(stdout);
}

int main() {
	for (int t = rd(); t; --t) work();
	return 0;
}