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
#define inf 2000000000
using namespace std;

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

int n,ans,a[N],tmp[N],len[N],xx[N];

inline void work(){
  for(R int i=n,l=0,x=0;i;--i)
    if(!a[i]) len[i]=l=0,xx[i]=x;
    else len[i]=++l,xx[i]=++x;
  for(R int i=1,l=0;i<=n;++i)
    if(a[i]){++l;ans=max(ans,l+len[i+1]+(xx[i+len[i+1]+1]>0));}
    else{ans=max(ans,l+len[i+1]+(xx[i+len[i+1]+1]>0)); l=0;}
}

int main(){
  n=rd();
  char c=gc();
  while(!isalpha(c)) c=gc();
  tmp[1]=a[1]=(c=='G');
  for(R int i=2;i<=n;++i) tmp[i]=a[i]=(gc()=='G');
  work();
  for(R int i=1;i<=n;++i) a[i]=tmp[n-i+1];
  work();
  printf("%d\n",ans);
  return 0;
}
