#include<cmath>
#include<queue>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define R register
#define gc getchar
using namespace std;

int n,ans=1,tmp;

int main(){
  scanf("%d",&n);
  while(n){
    if(n==3){printf("%d %d %d",ans,ans,ans*3);return 0;}
    if(n==2){printf("%d %d",ans,ans*2);return 0;}
    if(n==1){printf("%d",ans);return 0;}
    tmp=(n+1)/2;
    for(R int i=1;i<=tmp;++i) printf("%d ",ans);
    n=n/2; ans<<=1;
  }
  return 0;
}
