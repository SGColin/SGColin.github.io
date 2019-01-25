#include<cmath>
#include<queue>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 2010
#define R register
#define gc getchar
#define inf 90000000000000000ll
using namespace std;
typedef long long ll;

inline ll rd(){
  ll x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

ll n,m,S,T,tot=1,sum,hd[N];

struct edge{ll to,nxt,f;}e[N<<3];

inline void add(ll u,ll v,ll f){
  e[++tot].to=v; e[tot].f=f; e[tot].nxt=hd[u]; hd[u]=tot;
  e[++tot].to=u; e[tot].f=0; e[tot].nxt=hd[v]; hd[v]=tot;
}

ll h[N],d[N];

queue<ll> q;

inline bool bfs(){
  memset(d,0,sizeof(d));
  q.push(S); d[S]=1;
  while(!q.empty()){
    ll u=q.front(); q.pop();
    for(R ll i=hd[u],v;i;i=e[i].nxt)
      if(e[i].f&&d[v=e[i].to]==0){
        d[v]=d[u]+1; q.push(v);
      }
  }
  return d[T]>0;
}

ll dfs(ll u,ll flow){
  if(u==T||flow==0) return flow;
  ll res=0,tmp;
  for(R ll &i=h[u],v;i;i=e[i].nxt)
    if(e[i].f&&d[v=e[i].to]==d[u]+1){
      tmp=dfs(v,min(e[i].f,flow-res));
      if(tmp==0){d[v]=-1;continue;}
      e[i].f-=tmp; e[i^1].f+=tmp;res+=tmp;
      if(res==flow) return res;
    }
  return res;
}

inline ll dinic(){
  ll totf=0;
  while(bfs()){
    memcpy(h,hd,sizeof(hd));
    totf+=dfs(S,inf);
  }
  return totf;
}

int main(){
  n=rd(); m=rd();
  S=0; T=n+m+1;
  for(R ll i=1;i<=n;++i) add(i,T,rd());
  for(R ll i=1,u,v,w;i<=m;++i){
    u=rd(); v=rd(); sum+=(w=rd());
    add(S,n+i,w); add(n+i,u,inf); add(n+i,v,inf);
  }
  printf("%I64d\n",sum-dinic());
  return 0;
}
