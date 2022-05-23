#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <numeric>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int highbit(int x)
{
  return 1 << (31 - __builtin_clz(x));
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();

    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();

    int sum = std::accumulate(a.begin(), a.end(), 0);
    if (sum & (sum - 1))
    {
      puts("no");
    }
    else
    {
      constexpr int V = (1 << 13) + 1;

      std::vector<std::vector<int>> dp;
      dp.reserve(n + 1);
      dp.emplace_back(std::vector<int>(1, 0));

      int sum = 0;
      for (int x : a)
      {
        dp.emplace_back(std::vector<int>(sum + x + 1, -1));
        auto &pre = dp[dp.size() - 2];
        auto &cur = dp[dp.size() - 1];

        for (int i = 0; i <= sum; i++)
          if (pre[i] != -1)
          {
            if (!(i & (x - 1)))
            {
              cur[i + x] = i;
            }
            if (!((sum - i) & (x - 1)))
            {
              int h = highbit(sum + x - i);
              if (h * 2 > i)
                cur[i + h] = V + i;
              else
                cur[i] = V + i;
            }
          }

        sum += x;
      }

      int p = sum;
      if (dp.back()[p] == -1)
      {
        puts("no");
      }
      else
      {
        std::string ans(n, 'l');
        for (int i = n - 1; i >= 0; i--)
        {
          see(p, dp[i + 1][p]);
          if (dp[i + 1][p] < V)
          {
            ans[i] = 'l';
            p = dp[i + 1][p];
          }
          else
          {
            ans[i] = 'r';
            p = dp[i + 1][p] - V;
          }
        }
        puts(ans.c_str());
      }
    }
  }
  return 0;
}
