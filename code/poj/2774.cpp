#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 100010
#define M 200010
#define R register
using namespace std;

char s1[N],s2[N];

int ans,len1,len2,s[M],sa[M],h[M],rk[M],t1[M],t2[M],cnt[M];

inline void da(int n,int m){
  s[n++]=0;
  int *x=t1,*y=t2;
  for(R int i=0;i<n;++i) ++cnt[x[i]=s[i]];
  for(R int i=1;i<m;++i) cnt[i]+=cnt[i-1];
  for(R int i=n-1;~i;--i) sa[--cnt[x[i]]]=i;
  for(R int k=1,p;p<n&&k<=n;k<<=1,m=p){
    p=0;
    for(R int i=n-k;i<n;++i) y[p++]=i;
    for(R int i=0;i<n;++i) if(sa[i]>=k) y[p++]=sa[i]-k;
    for(R int i=0;i<=m;++i) cnt[i]=0;
    for(R int i=0;i<n;++i) ++cnt[x[y[i]]];
    for(R int i=1;i<=m;++i) cnt[i]+=cnt[i-1];
    for(R int i=n-1;~i;--i) sa[--cnt[x[y[i]]]]=y[i];
    swap(x,y); x[sa[0]]=0; p=1;
    for(R int i=1;i<n;++i)
      x[sa[i]]=(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k])?p-1:p++;
  }
  --n; h[0]=0;
  for(R int i=0;i<n;++i) sa[i]=sa[i+1];
  for(R int i=0;i<n;++i) rk[sa[i]]=i;
  for(R int i=0,p=0;i<n;++i){
    if(!rk[i]) continue;
    if(p) --p;
    while(s[i+p]==s[sa[rk[i]-1]+p]) ++p;
    h[rk[i]]=p;
  }
  for(R int i=1;i<n;++i)
    if((sa[i]<len1&&sa[i-1]>len1)||(sa[i]>len1&&sa[i-1]<len1)) ans=max(ans,h[i]);
}

int main(){
  scanf("%s",s1);
  int tot=(len1=strlen(s1));
  for(R int i=0;i<tot;++i) s[i]=s1[i];
  s[tot]=233;
  scanf("%s",s2); len2=strlen(s2);
  for(R int i=0;i<len2;++i) s[++tot]=s2[i];
  da(tot+1,256);
  printf("%d\n",ans);
  return 0;
}
