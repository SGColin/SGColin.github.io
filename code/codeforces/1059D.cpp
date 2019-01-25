#include<cmath>
#include<queue>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define R register
#define gc getchar
#define N 100010
using namespace std;

bool f=0;

const double eps=1e-8;

int n;

struct point{double x,y;}p[N];

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

inline bool valid(double x){
  double l=-(double)1e18,r=(double)1e18,dlt;
  for(R int i=1;i<=n;++i){
  	if(p[i].y>x+x) return 0;
    dlt=sqrt(p[i].y*(2*x-p[i].y));
    l=max(l,p[i].x-dlt); r=min(r,p[i].x+dlt);
  }
  return (r-l+eps>=0.0);
}

int main(){
  n=rd();
  for(R int i=1;i<=n;++i){
    p[i].x=(double)rd();
    p[i].y=(double)rd();
    if(p[i].y<0.0) f=1;
  }
  if(f==1) for(R int i=1;i<=n;++i){
      p[i].y=-p[i].y;
      if(p[i].y<0.0) {puts("-1");return 0;}
  }
  int t=0;
  R double l=0.0,r=(double)1e18,mid;
  while(t<=300){
    mid=(l+r)/2.0; ++t;
    valid(mid)?r=mid:l=mid;
  }
  printf("%.10lf",l);
  return 0;
}
