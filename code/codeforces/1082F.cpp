#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 510
#define gc getchar
#define R register
using namespace std;

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

char ss[N];

int n,m,w,ptr,root,len,s[N];

inline int newnode(){return ++ptr;}

struct node{int w,ch[10];}c[N<<1];

inline void insert(int &rt,int p){
  if(!rt) rt=newnode();
  if(p==len){c[rt].w+=w;return;}
  insert(c[rt].ch[s[p]],p+1);
}

int top,stk[N],d[N],f[N][N][11],g[N][N][11];

void dfs(int u){
  stk[++top]=u;
  for(R int i=0,v;i<10;++i)
    if((v=c[u].ch[i])>0){
      d[v]=d[u]+1; dfs(v);
      for(R int j=1;j<=top;++j)
        for(R int k=m;~k;--k){
          f[u][stk[j]][k]+=f[v][stk[j]][0];
          g[u][stk[j]][k]+=f[v][u][0];
          for(R int x=k;~x;--x){
            f[u][stk[j]][k]=min(f[u][stk[j]][k],f[u][stk[j]][k-x]+f[v][stk[j]][x]);
            g[u][stk[j]][k]=min(g[u][stk[j]][k],g[u][stk[j]][k-x]+f[v][u][x]);
          }
        }
    }
  for(R int j=1;j<=top;++j)
    for(R int k=m;~k;--k)
      if(k) f[u][stk[j]][k]=min(g[u][stk[j]][k-1],f[u][stk[j]][k]+c[u].w*(d[u]-d[stk[j]]));
      else f[u][stk[j]][k]+=c[u].w*(d[u]-d[stk[j]]);
  --top;
}

int main(){
  n=rd(); m=rd();
  for(R int i=1;i<=n;++i){
    scanf("%s",ss); len=strlen(ss);
    for(R int j=0;j<len;++j) s[j]=ss[j]-'0';
    w=rd(); insert(root,0);
  }
  dfs(root);
  printf("%d",f[root][root][m]);
  return 0;
}
