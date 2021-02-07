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

inline int tr(char c) {
	if (c == 'L') return 0;
	if (c == 'R') return 1;
	if (c == 'D') return 2;
	if (c == 'U') return 3; 
	return 0;
}

int cnt[4];

char s[100007];

inline void work() {
	cnt[0] = cnt[1] = cnt[2] = cnt[3] = 0;
	int tx = rd(); 
	int ty = rd();
	scanf("%s", s);
	int len = strlen(s);
	for (int i = 0; i < len; ++i) ++cnt[tr(s[i])];
	bool f = 1;
	if (tx > 0) f &= (cnt[1] >= tx);
	else f &= (cnt[0] >= -tx);
	if (ty > 0) f &= (cnt[3] >= ty);
	else f &= (cnt[2] >= -ty);
	puts(f ? "YES" : "NO");
}

int main() {
	int t = rd();
	while (t--) work();
	return 0;
}