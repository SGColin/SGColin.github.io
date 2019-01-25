#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 210
#define M 2010
#define R register
#define gc getchar
#define inf 2000000000
using namespace std;

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

int n,m,S,T,sum,tot=1,hd[N],deg[N];

struct edge{int to,nxt,f;}e[M<<1];

inline void add(int u,int v,int f){
  e[++tot].to=v; e[tot].f=f; e[tot].nxt=hd[u]; hd[u]=tot;
  e[++tot].to=u; e[tot].f=0; e[tot].nxt=hd[v]; hd[v]=tot;
}

struct Q{
  int x[N*10],hd,tl;
  inline void reset(){hd=1;tl=0;}
  inline void pop(){++hd;}
  inline void push(int a){x[++tl]=a;}
  inline int front(){return x[hd];}
  inline bool empty(){return hd>tl;}
}q;

int h[N],d[N];

inline bool bfs(){
  q.reset();
  for(R int i=S;i<=T;++i) d[i]=0;
  d[S]=1; q.push(S);
  while(!q.empty()){
    int u=q.front(); q.pop();
    for(R int i=hd[u],v;i;i=e[i].nxt)
      if(e[i].f&&!d[v=e[i].to]){
        d[v]=d[u]+1; q.push(v);
      }
  }
  return d[T]>0;
}

int dfs(int u,int flow){
  if(u==T||!flow) return flow;
  int res=0,tmp;
  for(R int i=hd[u],v;i;i=e[i].nxt)
    if(e[i].f&&d[v=e[i].to]==d[u]+1){
      tmp=dfs(v,min(flow-res,e[i].f));
      if(!tmp){d[v]=-1;continue;}
      res+=tmp; e[i].f-=tmp; e[i^1].f+=tmp;
      if(flow==res) return res;
    }
  return res;
}

inline int dinic(){
  int totf;
  while(bfs()){
    memcpy(h,hd,sizeof(hd));
    totf+=dfs(S,inf);
  }
  return totf;
}

inline void work(){
  n=rd(); m=rd();
  tot=1; sum=0; S=0; T=n+1;
  for(R int i=S;i<=T;++i) hd[i]=deg[i]=0;
  for(R int i=1,u,v,f;i<=m;++i){
    u=rd(); v=rd(); f=rd();
    if(f){++deg[u];--deg[v];}
    else{++deg[u];--deg[v];add(u,v,1);}
  }
  for(R int i=1;i<=n;++i){
    if(deg[i]&1){puts("impossible");return;}
    if(deg[i])deg[i]>0?add(S,i,deg[i]/2):add(i,T,-deg[i]/2);
    sum+=(deg[i]>0)*(deg[i]/2);
  }
  puts(dinic()==sum?"possible":"impossible");
}

int main(){
  int t=rd();
  while(t--) work();
  return 0;
}
