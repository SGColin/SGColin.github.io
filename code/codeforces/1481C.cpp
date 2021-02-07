#include <bits/stdc++.h>
#define N 100007
using namespace std;
typedef long long ll;

inline int rd() {
	int x = 0;
	bool f = 0;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if (c == '-') f = 1;
	for(; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	return f ? -x : x;
}

bool vis[N];

vector<int> s[N], tmp;

int n, m, cnt[N], a[N], b[N], c[N], pos[N], ptr[N];

inline void work() {
	n = rd(); m = rd();
	for (int i = 1; i <= n; ++i) {
		a[i] = rd(); vis[i] = 0; 
		s[i] = tmp; ptr[i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		b[i] = rd(); 
		vis[b[i]] = 1;
		if (b[i] != a[i]) s[b[i]].push_back(i);
	}
	for (int i = 1; i <= m; ++i) c[i] = rd(); 
	if (!vis[c[m]]) {
		puts("NO"); return;
	}
	if (s[c[m]].size() == 0) {
		for (int i = 1; i <= n; ++i) 
			if (b[i] == c[m]) pos[m] = i;
	} 
	else pos[m] = s[c[m]][ptr[c[m]]++];
	for (int i = m - 1; i; --i) {
		if (ptr[c[i]] >= s[c[i]].size()) pos[i] = pos[m];
		else pos[i] = s[c[i]][ptr[c[i]]++];
	}
	for (int i = 1; i <= n; ++i)
		if (ptr[i] < s[i].size()) {
			puts("NO"); return;
		}
	puts("YES");
	for (int i = 1; i <= m; ++i) printf("%d ", pos[i]);
	puts("");
}

int main() {
	int t = rd();
	while (t--) work();
	return 0;
}