#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define R register
using namespace std;

int n;

inline bool valid(int x){
  for(R int i=1;i<=n;++i)
    if(x%i==0&&x*i>n&&x/i<n){printf("%d %d\n",x,i);return 1;}
  return 0;
}

int main(){
  scanf("%d",&n);
  for(R int i=1;i<=n;++i) if(valid(i)) return 0;
  puts("-1");
  return 0;
}
