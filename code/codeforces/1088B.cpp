#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 100010
#define R register
#define gc getchar
using namespace std;

int n,k,a[N],s[N];

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

int main(){
  n=rd(); k=rd();
  for(R int i=1;i<=n;++i) a[i]=rd();
  sort(a+1,a+1+n);
  for(R int i=1;i<=n;++i) s[i]=a[i]-a[i-1];
  for(R int i=1;i<=n;++i)
    if(s[i]>0){
      printf("%d\n",s[i]);
      --k; if(!k) return 0;
    }
  while(k--) puts("0");
  return 0;
}
