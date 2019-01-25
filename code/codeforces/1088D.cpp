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

inline int query(int x,int y){
  printf("? %d %d\n",x,y);
  fflush(stdout);
  int ans;
  scanf("%d",&ans);
  return ans;
}

int main(){
  int a,b,mx=query(0,0);
  for(R int i=29,tmp,ans1,ans2;~i;--i){
    tmp=(1<<i);
    ans1=query(a+tmp,b);
    ans2=query(a,b+tmp);
    if(ans1!=ans2){
      if(ans1==1) continue;
      a+=tmp; b+=tmp;
    }
    else{
      if(mx==1) a+=tmp;
      else b+=tmp;
      mx=ans1;
    }
  }
  cout<<"! "<<a<<' '<<b<<endl;
  return 0;
}
