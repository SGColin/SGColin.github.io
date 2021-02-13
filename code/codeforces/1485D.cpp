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

const int L = 720720;

int main(){
	int n = rd();
	int m = rd();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1, x; j <= m; ++j) {
			x = rd();
			if ((i + j) & 1) printf("%d ", L);
			else printf("%d ", L + x * x * x * x);
		}
		puts("");
	}
    return 0;
}