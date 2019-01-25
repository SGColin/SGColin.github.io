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
typedef long long ll;

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

bool vis[N];

int prm[N];

inline void Linear_shaker(int n){
  for(R int i=2;i<=n;++i){
    if(!vis[i]) prm[++prm[0]]=i;
    for(R int j=1,k;j<=prm[0]&&(k=i*prm[j])<=n;++j){
      vis[k]=1; if(i%prm[j]==0) break;
    }
  }
}

inline int phi(int x,int mod){
  int res=x;
  for(R int i=1;prm[i]*prm[i]<=x;++i)
    if(x%prm[i]==0){
      res-=res/prm[i];
      while(x%prm[i]==0) x/=prm[i];
      if(x==1) break;
    }
  if(x>1) res-=res/x;
  return res%mod;
}

inline int qpow(int x,int t,int mod){
  int res=1;
  x%=mod;
  while(t){
    if(t&1) (res*=x)%=mod;
    (x*=x)%=mod; t>>=1;
  }
  return res;
}

int main(){
  int n,mod,ans;
  Linear_shaker(1e5);
  for(R int t=rd();t;t--){
    n=rd(); mod=rd(); ans=0;
    for(R int i=1,j;i*i<=n;++i)
      if(n%i==0){
        j=n/i;
        (ans+=qpow(n,i-1,mod)*phi(j,mod))%=mod;
        if(i!=j) (ans+=qpow(n,j-1,mod)*phi(i,mod))%=mod;
      }
    printf("%d\n",ans);
  }
  return 0;
}
