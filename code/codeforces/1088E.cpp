#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 300010
#define R register
#define gc getchar
#define inf 2000000000
using namespace std;
typedef long long ll;

inline ll rd(){
  ll x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

ll n,m=-inf,cnt,tot,val[N],hd[N];

struct edge{ll to,nxt;}e[N<<1];

inline void add(ll u,ll v){
  e[++tot].to=v; e[tot].nxt=hd[u]; hd[u]=tot;
  e[++tot].to=u; e[tot].nxt=hd[v]; hd[v]=tot;
}

inline ll dfs1(ll u,ll fa){
  ll sum=val[u];
  for(R ll i=hd[u],v;i;i=e[i].nxt)
    if((v=e[i].to)!=fa) sum+=max(0ll,dfs1(v,u));
  m=max(sum,m);
  return sum;
}

inline ll dfs2(ll u,ll fa){
  ll sum=val[u];
  for(R ll i=hd[u],v;i;i=e[i].nxt)
    if((v=e[i].to)!=fa) sum+=max(0ll,dfs2(v,u));
  if(sum==m) ++cnt,sum=0;
  return sum;
}

int main(){
  n=rd();
  for(R ll i=1;i<=n;++i) val[i]=rd();
  for(R ll i=1;i<n;++i) add(rd(),rd());
  dfs1(1,0); dfs2(1,0);
  printf("%I64d %I64d\n",m*cnt,cnt);
  return 0;
}
