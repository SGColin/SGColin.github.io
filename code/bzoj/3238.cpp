/*
Author: SGColin
Problem: BZOJ 3238
Algorithm: Suffix Automaton
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 1000005
using namespace std;
typedef long long ll;

struct node {
  int fa, mx, sz, tr[26];
} c[N];

char ss[N];

int n, m, lst = 1, tot, ptr = 1, hd[N];

inline int newnode(int mx, int sz = 0) {
  c[++ptr].mx = mx; c[ptr].sz = sz; return ptr;
}

inline void extend(int x) {
  int p = lst;
  int np = newnode(c[p].mx + 1, 1);
  lst = np;
  for (;p && !c[p].tr[x]; p = c[p].fa) c[p].tr[x] = np;
  if (!p) {c[np].fa = 1; return;}
  int q = c[p].tr[x];
  if (c[q].mx == c[p].mx + 1) c[np].fa = q;
  else {
    int nq = newnode(c[p].mx + 1);
    c[nq].fa = c[q].fa;
    for (int i = 0; i < 26; ++i) c[nq].tr[i] = c[q].tr[i];
    c[q].fa = c[np].fa = nq;
    for (;c[p].tr[x] == q; p = c[p].fa) c[p].tr[x] = nq;
  }
}

struct edge {int to, nxt;} e[N];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
}

ll ans = 0;

inline void dfs(int u) {
  for (int i = hd[u], v; i; i = e[i].nxt) {
    dfs(v = e[i].to);
    ans -= 2ll * c[v].sz * c[u].sz * c[u].mx;
    c[u].sz += c[v].sz;
  }
}

int main() {
  scanf("%s", ss + 1);
  n = strlen(ss + 1);
  for (int i = n; i; --i) extend(ss[n - i + 1] - 'a');
  for (int i = 2; i <= ptr; ++i) add(c[i].fa, i);
  ans = 1ll * (n - 1) * n * (n + 1) / 2;
  dfs(1); printf("%lld\n", ans);
  return 0;
}

/*
Author: SGColin
Problem: BZOJ 3238
Algorithm: Suffix Array
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 500010
#define R register
using namespace std;
typedef long long ll;

char ss[N];

ll ans,h[N],s[N],sa[N],cnt[N],t1[N],t2[N];

inline void da(ll n,ll m){
  ll *x=t1,*y=t2;
  s[n++]=0;
  for(R ll i=0;i<m;++i) cnt[i]=0;
  for(R ll i=0;i<n;++i) ++cnt[x[i]=s[i]];
  for(R ll i=1;i<m;++i) cnt[i]+=cnt[i-1];
  for(R ll i=n-1;~i;--i) sa[--cnt[x[i]]]=i;
  for(R ll k=1,p=0;p<n&&k<=n;k<<=1,m=p){
    p=0;
    for(R ll i=n-k;i<n;++i) y[p++]=i;
    for(R ll i=0;i<n;++i) if(sa[i]>=k) y[p++]=sa[i]-k;
    for(R ll i=0;i<m;++i) cnt[i]=0;
    for(R ll i=0;i<n;++i) ++cnt[x[y[i]]];
    for(R ll i=1;i<m;++i) cnt[i]+=cnt[i-1];
    for(R ll i=n-1;~i;--i) sa[--cnt[x[y[i]]]]=y[i];
    swap(x,y); p=1; x[sa[0]]=0;
    for(R ll i=1;i<n;++i) x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
  }
  --n; h[0]=0;
  for(R ll i=0;i<n;++i) sa[i]=sa[i+1];
  for(R ll i=0;i<n;++i) x[sa[i]]=i;
  for(R ll i=0,p=0;i<n;++i){
    if(!x[i]) continue;
    if(p) --p;
    while(s[i+p]==s[sa[x[i]-1]+p]) ++p;
    h[x[i]]=p;
  }
}

struct s{ll x,cnt;}stk[N];

ll top=0;

int main(){
  scanf("%s",ss);
  ll n=strlen(ss);
  for(R ll i=0;i<n;++i) s[i]=ss[i];
  da(n,256);
  ans=n*(n-1)*(n+1)/2;
  for(R ll i=0,cnt=1,sum=0;i<n;++i,cnt=1){
    while(top&&stk[top].x>=h[i]){
      cnt+=stk[top].cnt;
      sum-=stk[top].x*stk[top].cnt;
      --top;
    }
    stk[++top].x=h[i];
    stk[top].cnt=cnt;
    sum+=stk[top].x*stk[top].cnt;
    ans-=sum*2;
  }
  printf("%lld\n",ans);
}
