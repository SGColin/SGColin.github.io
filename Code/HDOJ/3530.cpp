#include<bits/stdc++.h>
using namespace std;

int a[100007];

deque<int> mx, mn;

int main() {
    cin.tie(nullptr) -> sync_with_stdio(false);
    int n, L, R;
    while (cin >> n >> L >> R) {
        int ans = 0, l = 1;
        mx.clear(); mn.clear();
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int r = 1; r <= n; ++r) {
            while (!mx.empty() && a[r] > a[mx.back()]) mx.pop_back(); 
            while (!mn.empty() && a[r] < a[mn.back()]) mn.pop_back(); 
            mx.push_back(r); mn.push_back(r);
            while (a[mx.front()] - a[mn.front()] > R) {
                if (mx.front() < mn.front()){
                    l = mx.front() + 1; mx.pop_front(); 
                } else {
                    l = mn.front() + 1; mn.pop_front();
                }
            }
            if (a[mx.front()] - a[mn.front()] >= L) ans = max(ans, r - l + 1);
        }
        cout << ans << endl;
    }
    return 0;
}