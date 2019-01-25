#include <cmath>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100010
#define gc getchar
#define Rg register
#define mod 9973ll
using namespace std;
typedef long long ll;

inline int rd() {
  int x = 0; bool f = 0; char c = gc();
  while (!isdigit(c)) { if (c=='-') f = 1; c = gc(); }
  while (isdigit(c)) { x = x * 10 + (c ^ 48); c = gc(); }
  return f ? -x : x;
}

int n, m, k;

struct Matrix {

  int a[10][10];

  inline void reset() { memset(a, 0, sizeof a); }

  inline void unit() {
    memset(a, 0, sizeof a);
    for (Rg int i = 0; i < m; ++i) a[i][i] = 1;
  }

  inline void trsf() {
    for (Rg int i = 0; i < m; ++i)
      for (Rg int j = 0; j < m; ++j) a[i][j] = 1;
  }

  inline Matrix operator * (const Matrix &x) {
    Matrix res;
    res.reset();
    for (Rg int i = 0; i < m; ++i)
      for(Rg int j = 0; j < m; ++j)
        for (Rg int k = 0; k < m; ++k)
          (res.a[i][j] += a[i][k] * x.a[k][j]) %= mod;
    return res;
  }

} unit,tr;

inline ll qpow(ll x, ll t) {
  ll res = 1;
  while (t) {
    if (t & 1) (res *= x) %= mod;
    (x *= x) %= mod; t >>= 1;
  }
  return res;
}

inline Matrix qpow(ll t) {
  Matrix res,x;
  res.unit(); x=tr;
  while (t) {
    if (t & 1) res = res * x;
    x = x * x; t >>= 1;
  }
  return res;
}

inline ll f(ll x) {
  Matrix res = qpow(x);
  ll sum = 0;
  for (Rg int i = 0; i < m; ++i) sum = (sum + res.a[i][i]) % mod;
  return sum;
}

inline vector<int> fac(const int &x) {
  vector<int> res;
  int lim = sqrt(x);
  for (Rg int i = 1; i <= lim; ++i)
    if (x % i == 0){
      res.push_back(i);
      if (x / i != i) res.push_back(x / i);
    }
  return res;
}

inline vector<int> prmfac(int x) {
  vector<int> res;
  int lim = sqrt(x);
  for (Rg int i = 2; i <= lim; ++i)
    if (x % i == 0) {
      res.push_back(i);
      while (x % i == 0) x /= i;
      if (x == 1) break;
    }
  if (x > 1) res.push_back(x);
  return res;
}

inline int phi(int x, const vector<int> &Prmfac) {
  int m = Prmfac.size(), res = x;
  for (Rg int i = 0; i < m; ++i)
    if (x % Prmfac[i] == 0){
      res -= res / Prmfac[i];
      while (x % Prmfac[i] == 0) x /= Prmfac[i];
      if (x ==  1) return res % mod;
    }
  return res % mod;
}

inline ll polya(ll n) {
  ll ans = 0;
  vector<int> Fac = fac(n);
  vector<int> Prmfac = prmfac(n);
  int m = Fac.size();
  for (Rg int i = 0; i < m; ++i) {
    ans = (ans + f(Fac[i]) * phi(n / Fac[i], Prmfac)) % mod;
  }
  return ans * qpow(n, mod - 2) % mod;
}

int main() {
  ll t=rd();
  while (t--) {
    n = rd(); m = rd();
    k = rd(); tr.trsf();
    for (Rg int i = 1, a, b; i <= k; ++i){
      a = rd() - 1; b = rd() - 1;
      tr.a[a][b] = tr.a[b][a] = 0;
    }
    printf("%lld\n", polya(n));
  }
  return 0;
}
