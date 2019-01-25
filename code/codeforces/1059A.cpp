#include<cmath>
#include<queue>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define N 100010
#define R register
#define gc getchar
using namespace std;

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

int n,m,a,l,r,ans;

int main(){
  n=rd(); m=rd(); a=rd();
  for(R int i=1;i<=n;++i){
    l=rd(); ans+=(l-r)/a;
    r=l+rd();
  }
  ans+=(m-r)/a;
  printf("%d\n",ans);
  return 0;
}
