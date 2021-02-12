#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < n; ++i)
#define repa(i, n) for (int i = 1; i <= n; ++i)
template <class T> bool checkMin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template <class T> bool checkMax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }
#define int long long

constexpr int N = 200005;

std::priority_queue<int> que;
int t[N], n, k, b, c;

int32_t main() {
  scanf("%lld%lld%lld%lld", &n, &k, &b, &c);
  b = std::min(b, c * 5);
  rep (i,n) scanf("%lld", &t[i]);
  std::sort(t, t + n);

  int sum=0, ans=std::numeric_limits<int>::max();
  rep (i,5) {
    int T = (int)(2e9) + i;
    while (!que.empty()) que.pop();
    sum = 0;
    rep (j,n) {
      int nd = (T - t[j]) / 5 * b + (T - t[j]) % 5 * c;
      sum += nd; que.push(nd);
      if (que.size() > k) { sum -= que.top(); que.pop(); }
      if (que.size() == k) checkMin(ans, sum - (T - t[j]) / 5 * b * k);
    }
  }

  printf("%lld", ans);
}
