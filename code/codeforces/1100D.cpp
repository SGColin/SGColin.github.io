#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1000
#define gc getchar
#define rg register
#define mid ((l+r) >> 1)
using namespace std;
typedef long long ll;

int x[N], y[N], cnt[5];

inline int pos(int x,int y){
  if(x < 499 && y < 499) return 1;
  else if (x > 499 && y < 499) return 2;
  else if (x < 499 && y > 499) return 3;
  else return 4;
}

bool vis[1001][1001];

int main() {
  int nx, ny;
  scanf("%d%d",&nx,&ny);
  for (rg int i = 1; i <= 666; ++i) scanf("%d%d",&x[i],&y[i]);
  int id,xx,yy;
  while(nx != 500 || ny != 500) {
    if(nx > 500){
      printf("%d %d\n",nx - 1,ny);
      --nx;
    }
    else if(nx < 500){
      printf("%d %d\n",nx + 1,ny);
      ++nx;
    }
    else if(ny > 500){
      printf("%d %d\n",nx,ny - 1);
      --ny;
    }
    else if(ny < 500){
      printf("%d %d\n",nx,ny + 1);
      ++ny;
    }
    fflush(stdout);
    scanf("%d%d%d",&id,&xx,&yy);
    if(id == -1) return 0;
    x[id] = xx; y[id] = yy;
  }
  for (rg int i = 1; i <= 666; ++i) {
    ++cnt[pos(x[i],y[i])]; vis[x[i]][y[i]] = 1;
  }
  int mn = min(min(cnt[1],cnt[2]),min(cnt[3],cnt[4]));
  int dx,dy;
  if(cnt[1] == mn) {
    dx = 1; dy =1;
  }
  else if(cnt[2] == mn) {
    dx = -1; dy = 1;
  }
  else if(cnt[3] == mn) {
    dx  = 1; dy = -1;
  }
  else{
    dx = -1; dy = -1;
  }
  while(1) {
    if(!vis[nx + dx][ny + dy]){
      printf("%d %d\n",nx + dx,ny + dy);
      nx = nx + dx;  ny = ny + dy;
    }
    else{
      printf("%d %d\n",nx + dx,ny);
      nx = nx + dx;
    }
    fflush(stdout);
    scanf("%d%d%d",&id,&xx,&yy);
    if(id == -1) return 0;
    vis[x[id]][y[id]] = 0;
    x[id] = xx; y[id] = yy;
    vis[x[id]][y[id]] = 1;
  }
  return 0;
}
