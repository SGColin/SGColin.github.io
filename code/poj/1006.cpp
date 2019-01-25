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

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

int main(){
  int a,b,c,d,ans,cnt=0;
  while("colin"){
    a=rd(); b=rd(); c=rd(); d=rd();
    if(a==-1&&b==-1&&c==-1&&d==-1) break;
    ans=(5544*a+14421*b+1288*c-d+21252)%21252;
    printf("Case %d: the next triple peak occurs in %d days.\n",++cnt,ans==0?21252:ans);
  }
  return 0;
}
