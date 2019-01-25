#include<cmath>
#include<queue>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define N 1010
#define R register
#define gc getchar
using namespace std;

bool vis[N][N],val[N][N];

int n,m,a,l,r,ans;

const int dx[9]={0,1,2,0,0,1,2,2};

const int dy[9]={0,0,0,1,2,2,1,2};

inline void work(int x,int y){
  for(R int i=0;i<8;++i) if(!val[x+dx[i]][y+dy[i]]) return;
  for(R int i=0;i<8;++i) vis[x+dx[i]][y+dy[i]]=1;
}

inline bool check(){
  for(R int i=1;i<=n-2;++i)
    for(R int j=1;j<=m-2;++j)
      if(val[i][j]) work(i,j);
  for(R int i=1;i<=n;++i)
    for(R int j=1;j<=m;++j)
      if(val[i][j]&&(!vis[i][j])) return 0;
  return 1;
}

int main(){
  scanf("%d%d",&n,&m);
  char c=gc();
  while(c!='#'&&c!='.') c=gc();
  for(R int i=1;i<=n;++i)
    for(R int j=1;j<=m;++j){
      val[i][j]=(c=='#');
      if(i!=n||j!=m){c=gc();while(c!='#'&&c!='.') c=gc();}
    }
  puts(check()?"YES":"NO");
  return 0;
}
