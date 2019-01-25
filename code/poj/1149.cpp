#include<cmath>
#include<vector>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 110
#define M 20010
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

int n,m,S,T,tot=1,hd[N],cnt[N*10];

struct edge{int to,nxt,f;}e[M<<1];

inline void add(int u,int v,int f){
  e[++tot].to=v; e[tot].f=f; e[tot].nxt=hd[u]; hd[u]=tot;
  e[++tot].to=u; e[tot].f=0; e[tot].nxt=hd[v]; hd[v]=tot;
}

vector<int> s[N*10];

struct Q{
  int x[N*10],hd,tl;
  inline void reset(){hd=1;tl=0;}
  inline void pop(){++hd;}
  inline void push(int a){x[++tl]=a;}
  inline int front(){return x[hd];}
  inline bool empty(){return hd>tl;}
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
  m=rd(); n=rd(); S=0; T=n+1;
  for(R int i=1;i<=m;++i) cnt[i]=rd();
  for(R int i=1,totp;i<=n;++i){
    totp=rd();
    while(totp--) s[rd()].push_back(i);
    add(i,T,rd());
  }
  for(R int i=1;i<=m;++i){
    if(!s[i].size()) continue;
    add(S,s[i][0],cnt[i]);
    for(R int j=1,lim=s[i].size();j<lim;++j) add(s[i][j-1],s[i][j],inf);
  }
  printf("%d\n",dinic());
  return 0;
}
