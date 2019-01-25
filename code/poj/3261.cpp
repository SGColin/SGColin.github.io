#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define N 20010
#define M 1000010
#define R register
#define gc getchar
using namespace std;

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

int n,t,s[N],cnt[M],sa[N],h[N],t1[N],t2[N],rk[N];

int ans,q[N],hd,tl;

inline void da(int n,int m){
  s[n++]=0;
  int *x=t1,*y=t2;
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
  hd=1; tl=0;
  for(R int i=1;i<n;++i){
    while(hd<=tl&&h[i]<h[q[tl]])--tl;
    q[++tl]=i;
    while(hd<=tl&&i-q[hd]+1>=t) ++hd;
    ans=max(ans,h[q[hd]]);
  }
}

int main(){
  n=rd(); t=rd();
  if(t==0){printf("%d\n",n);return 0;}
  for(R int i=0;i<n;++i) s[i]=rd()+1;
  da(n,M-1);
  printf("%d\n",ans);
  return 0;
}
