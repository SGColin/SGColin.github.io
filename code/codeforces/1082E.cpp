#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 500010
#define R register
#define gc getchar
using namespace std;

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

int n,m,cnt,ans,a[N],b[N];

int main(){
  n=rd(); m=rd();
  for(R int i=1,x;i<=n;++i)
    if((x=rd())==m) ++cnt;
    else{
      a[x]+b[x]>=cnt?a[x]+=b[x]-cnt:a[x]=0;
      b[x]=cnt; ans=max(ans,(++a[x]));
    }
  printf("%d\n",ans+cnt);
  return 0;
}
