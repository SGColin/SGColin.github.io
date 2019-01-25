#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define mod 10007
#define gc getchar
#define rg register
using namespace std;

inline int rd() {
    rg int x = 0;
    rg bool f = 0;
    rg char c = gc();
    while (!isdigit(c)) {
        if (c == '-') f == 1;
        c = gc();
    }
    while (isdigit(c)) {
        x = (x * 10 + (c ^ 48)) % mod;
        c = gc();
    }
    return f ? -x : x;
}

inline int C3(int x) {
    return x * (x + 1) % mod * (x + 2) % mod * 1668 % mod;
}

int main() {
    printf("%d\n", C3(rd()));
    return 0;
}
