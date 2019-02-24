#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 205
#define N 50005
#define gc getchar
#define mod 1000000007ll
using namespace std;
typedef long long ll;

inline int rd() {
    int x = 0;
    char c = gc();
    while (!isdigit(c)) c = gc();
    while (isdigit(c)) {
        x = x * 10 + (c ^ 48); c = gc();
    }
    return x;
}

int n, a, b;

ll c[M][M], s[N][M] = {1};

int main() {
    for (int i = 0; i < M; ++i) {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
    for (int i = 1; i < N; ++i)
        for (int j = 1; j <= min(i, M - 1); ++j)
            s[i][j] = ((i - 1) * s[i - 1][j] + s[i - 1][j - 1]) % mod;
    int t = rd();
    while (t--) {
        n = rd(); a = rd(); b = rd();
        printf("%lld\n", s[n - 1][a + b - 2] * c[a + b - 2][a - 1] % mod);
    }
    return 0;
}
