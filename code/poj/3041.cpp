#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 5010
#define M 200010
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

int n,m,S,T,tot=1,hd[N];

struct edge{int to,nxt,f;}e[M<<1];

inline void add(int u,int v,int f){
  e[++tot].to=v; e[tot].f=f; e[tot].nxt=hd[u]; hd[u]=tot;
  e[++tot].to=u; e[tot].f=0; e[tot].nxt=hd[v]; hd[v]=tot;
}

struct Q{
  int x[N*10],hd,tl;
  inline void pop(){++hd;}
  inline void reset(){hd=1;tl=0;}
  inline int front(){return x[hd];}
  inline bool empty(){return hd>tl;}
  inline void push(int a){x[++tl]=a;}
}q;


int d[N],h[N];

inline bool bfs(){
  for(R int i=S;i<=T;++i) d[i]=0;
  q.reset(); q.push(S); d[S]=1;
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
  for(R int &i=h[u],v;i;i=e[i].nxt)
    if(e[i].f&&d[v=e[i].to]==d[u]+1){
      tmp=dfs(v,min(flow-res,e[i].f));
      if(!tmp){d[v]=-1;continue;}
      res+=tmp; e[i].f-=tmp; e[i^1].f+=tmp;
      if(flow==res) return res;
    }
  return res;
}

inline int dinic(){
  int totf=0;
  while(bfs()){
    memcpy(h,hd,sizeof(hd));
    totf+=dfs(S,inf);
  }
  return totf;
}

int main(){
  m=rd(); n=rd(); S=0; T=m*2+3;
  for(R int i=1;i<=m;++i){add(S,i,1);add(i+m,T,1);}
  for(R int i=1,x,y;i<=n;++i){
    x=rd(); y=rd(); add(x,y+m,inf);
  }
  printf("%d\n",dinic());
  return 0;
}
