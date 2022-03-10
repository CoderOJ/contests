#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <map>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  std::vector<int> low(n), high(n);
  for (int i = 0; i < n; i++)
  {
    low[i]  = sc.next_int();
    high[i] = sc.next_int();
  }

  int concave_cnt = 0;
  for (int i = 0; i + 1 < n; i++)
  {
    if (low[i] != low[i + 1])
      concave_cnt += 1;
    if (high[i] != high[i + 1])
      concave_cnt += 1;
  }

  std::set<int> vertical;
  for (int i = 0; i + 1 < n; i++)
  {
    if (low[i] != low[i + 1] && high[i] != high[i + 1])
      vertical.insert(i);
  }

  see(concave_cnt);

  std::vector<std::pair<int, int>> horizontal;
  std::map<int, int>               lower, higher;
  for (int i = 0; i + 1 < n; i++)
  {
    if (low[i] < low[i + 1])
    {
      lower[low[i]] = i;
    }
    else if (low[i] > low[i + 1])
    {
      while (lower.begin() != lower.end())
      {
        const auto [ph, pid] = *std::prev(lower.end());
        if (ph < low[i + 1])
          break;
        if (ph == low[i + 1])
          horizontal.emplace_back(pid, i + 1);
        lower.erase(std::prev(lower.end()));
      }
    }
    if (high[i] < high[i + 1])
    {
      higher[high[i]] = i;
    }
    else if (high[i] > high[i + 1])
    {
      while (higher.begin() != higher.end())
      {
        const auto [ph, pid] = *std::prev(higher.end());
        if (ph < high[i + 1])
          break;
        if (ph == high[i + 1])
          horizontal.emplace_back(pid, i + 1);
        higher.erase(std::prev(higher.end()));
      }
    }
  }

  int ans = concave_cnt;
  ans -= (int)(vertical.size());
  ans -= (int)(horizontal.size());

  see(vertical);
  see(horizontal);

  for (const auto &[l, r] : horizontal)
  {
    auto it = vertical.lower_bound(l);
    if (it != vertical.end() && *it < r)
    {
      ans += 1;
      vertical.erase(it);
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
