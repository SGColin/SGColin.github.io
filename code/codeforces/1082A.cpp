#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
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

int n,x,y,d;

inline void work(){
  n=rd(); x=rd(); y=rd(); d=rd();
  if((y-x)%d==0){printf("%d\n",abs(y-x)/d);return;}
  int ans=inf;
  if((y-1)%d==0) ans=min(ans,(y-1)/d+(x+d-1)/d);
  if((n-y)%d==0) ans=min(ans,(n-y)/d+(n-x+d-1)/d);
  printf("%d\n",ans<inf?ans:-1);
}

int main(){
  int t=rd();
  while(t--) work();
  return 0;
}
