#include<bits/stdc++.h>
using namespace std;

int f[1000007];

deque<int> q;

inline void work() {
    int n, k, t;
    cin >> n >> k >> t;
    f[n] = 0; q.push_back(n);
    for (int i = n - 1; i; --i) {
        f[i] = 1e9;
        while (!q.empty() && q.front() > i + t) q.pop_front();
        if (!q.empty()) f[i] = min(f[i], f[q.front()] + 1);
        if (1ll * i * k <= 1ll * n) f[i] = min(f[i], f[i * k] + 1);
        while (!q.empty() && f[q.back()] > f[i]) q.pop_back();
        q.push_back(i);
    }
    cout << f[1] << endl;
    q.clear();
}

int main() {
    cin.tie(nullptr) -> sync_with_stdio(false);
    int t;
    for (cin >> t; t; --t) work();
    return 0;
}