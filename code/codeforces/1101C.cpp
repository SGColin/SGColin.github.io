#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 200010
#define gc getchar
#define rg register
using namespace std;

inline int rd() {
    rg int x = 0;
    rg bool f = 0;
    rg char c = gc();
    while (!isdigit(c)) {
        if (c=='-') f = 1;
        c = gc();
    }
    while (isdigit(c)) {
        x = x * 10 + (c ^ 48);
        c = gc();
    }
    return f ? -x : x;
}

struct node{
    int l,r,id;
}c[N];

int ans[N];

inline bool cmp(node x, node y) {
    return x.l == y.l? x.r < y.r: x.l < y.l;
}

inline void work() {
    int n = rd();
    for (rg int i = 1; i<= n; ++i) {
        c[i].l = rd(); c[i].r = rd();
        c[i].id = i;
    }
    sort(c+1,c+1+n,cmp);
    int nowr = c[1].r;
    for(rg int i =2; i<= n;++i) {
        if(c[i].l > nowr) {
            for (rg int j = 1; j < i ;++j) ans[c[j].id]  = 1;
            for (rg int j = i; j <= n; ++j) ans[c[j].id] = 2;
            for (rg int j = 1; j <= n; ++j) printf("%d ",ans[j]);
            puts("");return;
        }
        nowr = max(nowr,c[i].r);
    }
    puts("-1");
}
int main() {
    int t = rd();
    while(t--) work();
    return 0;
}
