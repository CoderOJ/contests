#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <numeric>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 998244353;
using int_t       = cm::intm<MOD>;

struct limit_t
{
  int l, r;
  int w;
};

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int m = sc.next_int();
    int k = sc.next_int();

    std::vector<limit_t> limits;

    for (int i = 0; i < m; i++)
    {
      int l = sc.next_int() - 1;
      int r = sc.next_int();
      int w = sc.next_int();
      limits.push_back({l, r, w});
    }

    std::vector<int> vals = {0, n};
    for (auto p : limits)
    {
      vals.push_back(p.l);
      vals.push_back(p.r);
    }
    std::sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
    n = static_cast<int>(vals.size()) - 1;
    for (auto &p : limits)
    {
      p.l = static_cast<int>(std::lower_bound(vals.begin(), vals.end(), p.l) -
                             vals.begin());
      p.r = static_cast<int>(std::lower_bound(vals.begin(), vals.end(), p.r) -
                             vals.begin());
    }

    std::vector<int> p_limit(n, k);
    for (auto p : limits)
      for (int i = p.l; i < p.r; i++)
        check_min(p_limit[i], p.w);

    see(p_limit);

    std::vector<int> ws;
    for (int x : p_limit)
      ws.push_back(x);
    std::sort(ws.begin(), ws.end());
    ws.erase(std::unique(ws.begin(), ws.end()), ws.end());

    int_t ans = 1;

    for (auto p : limits)
    {
      bool reached = false;
      for (int i = p.l; i < p.r && !reached; i++)
        if (p_limit[i] == p.w)
          reached = true;
      if (!reached)
        ans = 0;
    }

    for (int ww : ws)
    {
      std::vector<int> min_left(n + 1, 0);
      for (auto p : limits)
        if (p.w == ww)
          check_max(min_left[p.r], p.l + 1);

      asee(ww);
      std::vector<int_t> dp{1};
      for (int i = 1; i <= n; i++)
      {
        if (p_limit[i - 1] == ww)
        {
          int   t     = vals[i] - vals[i - 1];
          int_t n_all = int_t(p_limit[i - 1]).pow(t);
          int_t n_nie = int_t(p_limit[i - 1] - 1).pow(t);
          int_t n_tak = n_all - n_nie;

          std::vector<int_t> cur(i + 1, 0);
          for (int j = 0; j < (int)(dp.size()); j++)
          {
            cur[i] += dp[j] * n_tak;
            cur[j] += dp[j] * n_nie;
          }
          dp = std::move(cur);
        }
        for (int j = 0; j < min_left[i]; j++)
          dp[j] = 0;
      }

      int_t cur_ans = std::accumulate(dp.begin(), dp.end(), int_t(0));
      see(cur_ans);
      ans *= cur_ans;
    }

    std::cout << ans << std::endl;
  }
  return 0;
}
