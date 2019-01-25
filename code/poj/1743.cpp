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

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

int n,a[N],s[N],sa[N],rk[N],h[N],t1[N],t2[N],cnt[N];

inline void da(int n,int m){
  s[n++]=0;
  int *x=t1,*y=t2;
  for(R int i=0;i<m;++i) cnt[i]=0;
  for(R int i=0;i<n;++i) ++cnt[x[i]=s[i]];
  for(R int i=1;i<m;++i) cnt[i]+=cnt[i-1];
  for(R int i=n-1;~i;--i) sa[--cnt[s[i]]]=i;
  for(R int k=1,p;p<=n&&k<=n;k<<=1,m=p){
    p=0;
    for(R int i=n-k;i<n;++i) y[p++]=i;
    for(R int i=0;i<n;++i) if(sa[i]>=k) y[p++]=sa[i]-k;
    for(R int i=1;i<m;++i) cnt[i]=0;
    for(R int i=0;i<n;++i) ++cnt[x[y[i]]];
    for(R int i=1;i<m;++i) cnt[i]+=cnt[i-1];
    for(R int i=n-1;~i;--i) sa[--cnt[x[y[i]]]]=y[i];
    swap(x,y); x[sa[0]]=0; p=1;
    for(R int i=1;i<n;++i)
      x[sa[i]]=(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k])?p-1:p++;
  }
  --n;
  for(R int i=0;i<n;++i) sa[i]=sa[i+1];
  for(R int i=0;i<n;++i) rk[sa[i]]=i;
  h[0]=0;
  for(R int i=0,p=0;i<n;++i){
    if(!rk[i]) continue;
    if(p) --p;
    while(s[i+p]==s[sa[rk[i]-1]+p]) ++p;
    h[rk[i]]=p;
  }
}

inline bool valid(int x){
  for(R int i=0,mn,mx;i<n;++i){
    mn=mx=sa[i];
    while(h[i+1]>=x&&i+1<n){
      ++i;
      mn=min(mn,sa[i]);
      mx=max(mx,sa[i]);
    }
    if(mx-mn>x) return 1;
  }
  return 0;
}

inline void work(){
  for(R int i=0;i<n;++i) a[i]=rd();
  s[0]=a[0]+100;
  for(R int i=1;i<n;++i) s[i]=a[i]-a[i-1]+100;
  da(n,210);
  int l=0,r=(n>>1),mid;
  while(l<r){
    mid=((l+r+1)>>1);
    valid(mid)?l=mid:r=mid-1;
  }
  printf("%d\n",l>3?l+1:0);
}

int main(){
  while(233){
    n=rd();
    if(n==0) break;
    work();
  }
  return 0;
}
