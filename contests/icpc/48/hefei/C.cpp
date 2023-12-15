#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)

const int A = 10;
const int N = 6000007;
const int mod = 998244353;

int n;

char S[N];

struct PAM {

	int tot, now, last, s[N];

	int l[N], fail[N], nxt[N][A], num[N];

	void clear() {
		s[0] = l[1] = -1;
	    fail[0] = tot = now = 1;
	    last = l[0] = 0;
	    memset(nxt[0],0,sizeof nxt[0]);
        memset(nxt[1],0,sizeof nxt[1]);
	}

	int newn(int len){
	    tot++;
	    memset(nxt[tot], 0, sizeof(nxt[tot]));
	    fail[tot] = num[tot] = 0;
	    l[tot] = len;
	    return tot;
	}

	int get_fail(int x){
	    while (s[now - l[x] - 2] != s[now - 1]) x = fail[x];
	    return x;
	}

	void add(int ch, int w){
		s[now++] = ch;
	    int cur = get_fail(last);
	    if(!nxt[cur][ch]) 
	    	fail[nxt[cur][ch] = newn(l[cur] + 2)] = nxt[get_fail(fail[cur])][ch];
	    last = nxt[cur][ch];
	    num[last] += w;
	}

	int calc(){
		int ret = 0;
	    for (int i = tot; i >= 2; --i) {
	    	num[fail[i]] += num[i];
	    	if (l[i] <= n) ret = (ret + 1ll * num[i] * num[i] % mod * l[i]) % mod;
	    }
	    return ret;
	}

} pam;

int main() {
	scanf("%d", &n);
	scanf("%s", S + 1);
	pam.clear();
	rep(i, 1, n) pam.add(S[i] - '0', 0);
	rep(i, 1, n) pam.add(S[i] - '0', 1);
	printf("%d\n", pam.calc());
    return 0;
}