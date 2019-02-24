#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>
#define N 1000002
#define R register
using namespace std;
typedef unsigned long long ull;
const int mod=19260817;
int tong[30],n,n2;
ull dis[30],ji[30];
long long ans;
map<ull,int>mp2[28];
const int base=233;
char s[N];

inline ull t(int l,int r){return dis[r]-dis[l];}

inline void hassh(){
    memset(tong,0,sizeof(tong));
    for(int i=1;i<=n2;++i)tong[s[i-1]-'a']^=1;
    for(int i=1;i<=26;++i)dis[i]=dis[i-1]+(ull)tong[i-1]*ji[i];
}
inline ull ch(int x){return t(0,x-1)*base+t(x,26);}

int main(){
    scanf("%d",&n);
    ji[0]=1;
    for(R int i=1;i<=26;++i)ji[i]=ji[i-1]*base;
    for(R int i=1;i<=n;++i){
        scanf("%s",s);n2=strlen(s);
        hassh();
        for(R int j=1;j<=26;++j)ans+=mp2[j][ch(j)];
        ans-=mp2[27][dis[26]]*25;
        for(R int j=1;j<=26;++j)mp2[j][ch(j)]++;
        mp2[27][dis[26]]++;
    }
    printf("%I64d",ans);
    return 0;
}
