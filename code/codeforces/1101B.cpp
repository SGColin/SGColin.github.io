#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 500010
#define gc getchar
#define rg register
using namespace std;

char s[N];

int main() {
    scanf("%s",s);
    int p1=-1,p2=-1,m1=-1,m2=-1;
    int n =strlen(s);
    for (rg int i = 0; i < n; ++i) {
        if(p1 == -1&&s[i] == '[') p1 = i;
        if(p1!=-1 && m1 == -1&& s[i] == ':') m1 = i;
    }
    for (rg int i = n - 1; ~i; --i) {
        if(p2 == -1&&s[i] == ']') p2 = i;
        if(p2!=-1 && m2 == -1&& s[i] == ':') m2 = i;
    }
    if(p1==-1||p2==-1||m1==-1||m2==-1||p1>p2||m1>=m2){puts("-1");return 0;}
    int ans = 4;
    for (rg int i =m1 + 1; i < m2; ++i) ans += (s[i] =='|');
    printf("%d",ans);
    return 0;
}
