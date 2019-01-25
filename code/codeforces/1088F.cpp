#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define N 500010
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

ll n,m,mn=inf,tot,hd[N],val[N];

struct edge{ll to,nxt;}e[N<<1];

inline void add(ll u,ll v){
  e[++tot].to=v; e[tot].nxt=hd[u]; hd[u]=tot;
  e[++tot].to=u; e[tot].nxt=hd[v]; hd[v]=tot;
}

ll res,t,f[N][20];

inline void dfs(ll u,ll fa){
  ll ans=val[fa]+val[u];
  f[u][0]=fa;
  for(R ll i=1;i<=t;++i){
    f[u][i]=f[f[u][i-1]][i-1];
    if(f[u][i]!=0) ans=min(ans,val[f[u][i]]*(i+1)+val[u]);
    else ans=min(ans,val[m]*(i+1)+val[u]);
  }
  if(u!=m) res+=ans;
  for(R ll i=hd[u],v;i;i=e[i].nxt) if((v=e[i].to)!=fa) dfs(v,u);
}

int main(){
  t=log2(n=rd())+1;
  for(R ll i=1;i<=n;++i){
    val[i]=rd();
    if(val[i]<mn) m=i,mn=val[i];
  }
  for(R ll i=1;i<n;++i) add(rd(),rd());
  dfs(m,0);
  printf("%I64d\n",res);
  return 0;
}
