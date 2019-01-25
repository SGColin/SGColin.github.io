#include<cmath>
#include<vector>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 510
#define R register
#define gc getchar
using namespace std;

inline int rd(){
  int x=0; bool f=0; char c=gc();
  while(!isdigit(c)){if(c=='-')f=1;c=gc();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc();}
  return f?-x:x;
}

int n,m,cnt1,sum,sum2;

vector<int> s[N];

int main(){
  n=rd();
  for(R int i=1,x;i<=n;++i){
    x=rd(); s[x].push_back(i);
    sum+=x;
    if(x>1) sum2+=x-2;
    else ++cnt1;
  }
  if(sum2<cnt1-2){puts("NO");return 0;}
  printf("YES %d\n",n-cnt1-1+min(2,cnt1));
  printf("%d\n",n-1);
  if(!s[1].size()){
    for(R int i=2,lst=0;i<=n-1;++i)
      for(R int j=0;j<(int)s[i].size();++j)
        if(!lst) lst=s[i][j];
        else{printf("%d %d\n",lst,s[i][j]);lst=s[i][j];}
  }
  else{
    int ptr=2,lst=s[1][0];
    for(R int i=2;i<=n-1;++i)
      for(R int j=0;j<(int)s[i].size();++j){
        printf("%d %d\n",lst,s[i][j]); lst=s[i][j];
      }
    if(s[1].size()==1) return 0;
    printf("%d %d\n",lst,s[1][1]);
    for(R int i=3;i<=n-1;++i)
      for(R int j=0;j<(int)s[i].size();++j){
        for(R int k=1;k<=i-2&&ptr<(int)s[1].size();++k){
          printf("%d %d\n",s[i][j],s[1][ptr]); ++ptr;
        }
        if(ptr==(int)s[1].size()) return 0;
      }
  }
  return 0;
}
