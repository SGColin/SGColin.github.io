#include <bits/stdc++.h>
#define N 1007
using namespace std;
typedef long long ll;

int n, m, a[N][N];

inline void work() {
	char c;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			for(c = getchar(); !isalpha(c) && c != '*'; c = getchar());
			a[i][j] = c - 'a';
		}
	if (m & 1) {
		puts("YES");
		int x = 1;
		for (int i = 1; i <= m + 1; ++i) {
			x = 3 - x; printf("%d ", x);
		}
		puts(""); return;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) 
			if (a[i][j] == a[j][i]){
				puts("YES");
				int t = m / 2;
				printf("%d ", i);
				for (int k = 1; k <= t; ++k) printf("%d %d ", j, i);
				puts(""); return; 
			}
	for (int i = 1, pos1, pos2; i <= n; ++i) {
		pos1 = pos2 = 0;
		for (int j = 1; j <= n; ++j) {
			if (i == j) continue;
			if (a[i][j] == 0) pos1 = j;
			else pos2 = j;
		}
		if (pos1 != 0 && pos2 != 0) {
			puts("YES");
			int t = m / 4;
			if (m % 4 == 2) printf("%d ", pos1);
			printf("%d ", i);
			for (int j = 1; j <= t; ++j) printf("%d %d ", pos1, i);
			for (int j = 1; j <= t; ++j) printf("%d %d ", pos2, i);
			if (m % 4 == 2) printf("%d", pos2);
			puts("");
			return;
		} 
	}
	puts("NO");
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) work();
	return 0;
}