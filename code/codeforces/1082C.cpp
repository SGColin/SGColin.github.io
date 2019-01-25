#include<cmath>
#include<vector>
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
typedef long long ll;

inline ll rd(){
  ll x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

ll n,m,ans,sum[N];

vector<ll> s[N];

inline bool cmp(ll x,ll y){return x>y;}

int main(){
  n=rd(); m=rd();
  for(R ll i=1,x,y;i<=n;++i){
    x=rd(); y=rd(); s[x].push_back(y);
  }
  for(R ll i=1;i<=m;++i){
    sort(s[i].begin(),s[i].end(),cmp);
    for(R ll j=0,tot=0;j<s[i].size();++j){
      tot+=s[i][j]; if(tot<0) break;
      sum[j+1]+=tot;
    }
  }
  for(R ll i=1;i<=n;++i) ans=max(ans,sum[i]);
  printf("%I64d\n",ans);
  return 0;
}
