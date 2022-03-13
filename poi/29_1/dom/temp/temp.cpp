#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int64_t M = 1e18;

auto fibs = [] {
  std::vector<std::pair<int64_t, int>> res{{2, 3}, {3, 4}};
  while (res.back().first < M)
    res.emplace_back(res[res.size() - 2].first + res[res.size() - 1].first,
                     res.back().second + 1);
  return res;
}();

int solve(int64_t m, auto it)
{
  if (m == 1)
    return -1;
  else if (it == fibs.end())
    return 0x3f3f3f3f;
  else if (m % it->first != 0)
    return solve(m, std::next(it));
  else
    return std::min(solve(m, std::next(it)),
                    solve(m / it->first, it) + it->second);
}

int main()
{
  int64_t m   = sc.next_long();

  if (m == 1)
  {
    puts("1");
    return 0;
  }

  int     ans = solve(m, fibs.begin());

  if (ans >= 0x3f3f3f3f)
    puts("NIE");
  else
    std::cout << ans << std::endl;
  return 0;
}
