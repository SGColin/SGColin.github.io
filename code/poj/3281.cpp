#include<cmath>
#include<queue>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 10100
#define R register
#define gc getchar
#define inf 200000000
using namespace std;

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

int n,m1,m2,cnt,f[N],l[N],r[N],c[N];

int s,t,tot=1,hd[N],h[N],dp[N];

struct edge{int w,to,nxt;}e[N*100];

inline void add(int u,int v,int w){
  e[++tot].to=v; e[tot].w=w;
  e[tot].nxt=hd[u]; hd[u]=tot;
}

queue<int> q;

inline bool bfs(){
  for(R int i=0;i<=cnt;++i) dp[i]=0;
  dp[s]=1; q.push(s);
  while(!q.empty()){
    int u=q.front(); q.pop();
    for(R int i=hd[u],v;i;i=e[i].nxt)
      if(e[i].w&&(!dp[v=e[i].to])){
        dp[v]=dp[u]+1; q.push(v);
      }
  }
  return dp[t]>0;
}

inline int dfs(int u,int flow){
  if(u==t||!flow) return flow;
  int res=0,tmp;
  for(R int &i=h[u];i;i=e[i].nxt)
    if(e[i].w&&(dp[e[i].to]==dp[u]+1)){
      tmp=dfs(e[i].to,min(e[i].w,flow-res));
      e[i].w-=tmp; e[i^1].w+=tmp; res+=tmp;
      if(res==flow) return res;
    }
  return res;
}

inline int dinic(){
  int res=0;
  while(bfs()){
    for(R int i=0;i<=cnt;++i) h[i]=hd[i];
    res+=dfs(s,inf);
  }
  return res;
}

int main(){
  n=rd(); m1=rd(); m2=rd();
  for(R int i=1;i<=m1;++i) f[i]=++cnt;
  for(R int i=1;i<=n;++i) l[i]=++cnt,r[i]=++cnt;
  for(R int i=1;i<=m2;++i) c[i]=++cnt;
  s=0; t=++cnt;
  for(R int i=1;i<=m1;++i){add(s,f[i],1);add(f[i],s,0);}
  for(R int i=1;i<=n;++i){add(l[i],r[i],1);add(r[i],l[i],0);}
  for(R int i=1;i<=m2;++i){add(c[i],t,1);add(t,c[i],0);}
  for(R int i=1,a,b,x;i<=n;++i){
    a=rd(); b=rd();
    for(R int j=1;j<=a;++j){
      x=rd();  add(f[x],l[i],1); add(l[i],f[x],0);
    }
    for(R int j=1;j<=b;++j){
      x=rd();  add(r[i],c[x],1); add(c[x],r[i],0);
    }
  }
  printf("%d\n",dinic());
  return 0;
}
