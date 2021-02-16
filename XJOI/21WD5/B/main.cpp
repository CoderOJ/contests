#include <vector>
#include <limits>
#include <algorithm>

class FoxAndPhotography {
private:
  inline int pop_cnt(int x) {
    int res = 0;
    for (;x;x &= (x-1)) { res++; }
    return res; }

  static constexpr int N = 16;
  int dp[1 << N];

public:
  int getMinimumSwaps(const std::vector<int>& front, const std::vector<int>& back) {
    int n = front.size();
    for (int i=(1<<n)-2; i>=0; i--) {
      dp[i] = std::numeric_limits<int>::max();
      int cnt = pop_cnt(i);
      int cross = 0;
      for (int j=0; j<n; ++j) {
        int vmask = i | (1 << j);
        if ((i & (1<<j)) == 0) {
          if (front[j] < back[cnt] && dp[vmask] != std::numeric_limits<int>::max()) {
            dp[i] = std::min(dp[i], dp[vmask] + cross); }
          cross++; } } }
    return dp[0] == std::numeric_limits<int>::max() ? -1 : dp[0];
  }
};
