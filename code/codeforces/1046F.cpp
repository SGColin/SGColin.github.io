#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 200005
#define R register
#define gc getchar
using namespace std;
typedef long long ll;

inline ll rd(){
  ll x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

ll n,w,ans,lim,num[N];

int main(){
  n=rd();
  for(R ll i=1;i<=n;++i) num[i]=rd();
  lim=rd(); w=rd();
  for(R ll i=1,tmp;i<=n;++i){
    ans+=(tmp=num[i]/(lim+w));
    if(num[i]-tmp*(lim+w)>lim) ++ans;
  }
  printf("%I64d\n",ans*w);
  return 0;
}
