#include <bits/stdc++.h>
#define N 200007
using namespace std;

#define fa(x) (x == 1 ? 0 : (1ll << (__lg(x - 1) + 1)) - x)

int dis(int x, int y) {
	return x == y ? 0 : (x < y ? dis(x, fa(y)) : dis(fa(x), y)) + 1;
}

int n, a[N];

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	int mxd = 0, pa, pb;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		int d = dis(a[i], a[1]);
		if (d > mxd) {mxd = d; pa = i;}
	}
	mxd = 0;
	for (int i = 1; i <= n; ++i) {
		int d = dis(a[i], a[pa]);
		if (d > mxd) {mxd = d; pb = i;}
	}
	cout << pa << " " << pb << " " << mxd;
	return 0;
}