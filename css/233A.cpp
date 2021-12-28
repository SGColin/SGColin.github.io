#include <bits/stdc++.h>
#define N 200007
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define pii pair<int, int>
using namespace std;
typedef long long ll;

inline int rd() {
    int x = 0;
    bool f = 0;
    char c = getchar();
    for (; !isdigit(c); c = getchar()) f |= (c == '-');
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    return f ? -x : x;
}

int n, Q, ans[N], pos[N];

pii q[N];

inline bool cmp(pii a, pii b) {
	if (a.fr != b.fr) return a.fr > b.fr;
	return a.sc < b.sc;
}

double v, res[N];

int main() {
	int n = rd();
	res[n] = rd();
	v = rd();
	for (int i = 1; i <= n; ++i) pos[i] = rd();
	sort(pos + 1, pos + 1 + n);
	for (int i = 1; i <= n; ++i) 
		res[n - i] = res[n - i + 1] + pos[i];
	for (int i = 0; i <= n; ++i) res[i] /= v;
	Q = rd();
	for (int i = 1; i <= Q; ++i) {
		q[i].fr = rd(); q[i].sc = i;
	}
	sort(q + 1, q + 1 + Q, cmp);
	int ptr = 0;
	for (int i = 1; i <= Q; ++i) {
		while (ptr <= n && res[ptr] >= q[i].fr) ++ptr;
		ans[q[i].sc] = ptr;
	}
	for (int i = 1; i <= Q; ++i) 
		printf("%d\n", ans[i] == n + 1 ? -1 : ans[i]);
    return 0;
}