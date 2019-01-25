#include<cmath>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 2010
#define R register
#define gc getchar
using namespace std;

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

int n,m,fl,a[N];

int main(){
  n=rd();
  for(R int i=1;i<=n;++i){
    a[i]=rd();
    if(a[i]<=a[i-1]) fl=1;
  }
  if(!fl){puts("0");return 0;}
  printf("%d\n",n+1);
  for(R int i=n,s=0,tmp;i;--i){
    a[i]=(a[i]+s)%(n+1);
    tmp=(n+1+i-a[i])%(n+1);
    printf("1 %d %d\n",i,tmp); s+=tmp;
  }
  printf("2 %d %d\n",n,n+1);
  return 0;
}
