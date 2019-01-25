#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
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

ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}

inline ll qpow(ll x,ll t){
  ll res=1;
  while(t){
    if(t&1) res*=x;
    x*=x; t>>=1;
  }
  return res;
}

int main(){
  ll n,m,ans;
  while(2333){
    m=rd(); n=rd();
    if(!n&&!m) break;
    ans=(n&1)?n*qpow(m,n/2+1):n/2*(qpow(m,n/2)+qpow(m,n/2+1));
    for(R int i=0;i<n;++i) ans+=qpow(m,gcd(i,n));
    printf("%lld\n",ans/n/2);
  }
  return 0;
}
