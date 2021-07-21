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

int a, b;

inline int calc(int x) {
	if (x == 1) return 1e9;
	int res = 0, tmp = a;
	while (tmp) {tmp /= x; ++res;}
	return res;
}

inline void work() {
	a = rd(); 
	b = rd();
	int ans = 1e9;
	for (int i = 0; i <= 31; ++i) 
		ans = min(ans, calc(b + i) + i);
	printf("%d\n", ans);
}

int main(){
	int t = rd();
	while (t--) work();
    return 0;
}