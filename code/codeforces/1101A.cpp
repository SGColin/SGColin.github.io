#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define gc getchar
#define rg register
using namespace std;
typedef long long ll;

inline ll rd() {
    ll x = 0;
    bool f = 0;
    char c = gc();
    while (!isdigit(c)) {
        if (c == '-') f == 1;
        c = gc();
    }
    while (isdigit(c)) {
        x = (x * 10 + (c ^ 48));
        c = gc();
    }
    return f ? -x : x;
}

inline void work() {
    ll l = rd(), r = rd(), x = rd();
    if(x < l || x > r) printf("%I64d\n",x);
    else printf("%I64d\n",x*((r/x) + 1));
}

int main() {
    int t = rd();
    while (t--) work();
    return 0;
}
