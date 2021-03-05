#include <vector>
#include <set>
#include <algorithm>

class PenguinSledding {
  static constexpr int N = 55;
  int cnt[N];

public:
  PenguinSledding() { std::fill(cnt, cnt+N, 0); } 

  long long countDesigns(int n, std::vector<int> e1, std::vector<int> e2) {
    int m = e1.size();
    for (int i=0; i<m; ++i) {
      cnt[e1[i]]++; cnt[e2[i]]++; }
    long long ans = 1 + m;
    for (int u=1;u<=n;++u) if (cnt[u] >= 2) {
      ans += (1ll << cnt[u]) - cnt[u] - 1; }
    for (int i=0;i<m;++i) for (int j=0;j<i;++j) for (int k=0;k<j;++k) {
      if (std::set<int>({e1[i],e1[j],e1[k],e2[i],e2[j],e2[k]}).size() == 3) {
        ans++; } }
    return ans;
  }
};
