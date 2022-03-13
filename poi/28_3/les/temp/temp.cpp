#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int64_t solve(const std::vector<int64_t> &a,
              const std::vector<int64_t> &b,
              int64_t                     d)
{
  auto at = [d](const std::vector<int64_t> &a, int x) -> int64_t {
    if (x < 0)
      return 0;
    else if (x >= static_cast<int>(a.size()))
      return d;
    return a[x];
  };

  int len = static_cast<int>(a.size() + b.size());

  auto calc_diff = [&](int diff) {
    int ans = 0;
    for (int i = -len; i <= len; i++)
    {
      int64_t ai = at(a, i);
      int64_t bi = at(b, i + diff);
      if (ai > bi)
        ans += 1;
      else if (ai < bi)
        ans += -1;
    }
    return ans;
  };

  auto calc = [&](int diff) {
    int64_t ans = 0;
    for (int i = -len; i <= len; i++)
      ans += std::abs(at(a, i) - at(b, i - diff));
    return ans;
  };

  int l = -len, r = len;
  while (r - l >= 5)
  {
    int m = l + (r - l) / 2;
    if (calc(m) < calc(m + 1))
      r = m + 1;
    else
      l = m;
  }

  see(l);

  int64_t ans = calc(r);
  for (int i = l; i < r; i++)
    check_min(ans, calc(i));

  return ans;
}

int main()
{
  int     n = sc.next_int();
  int64_t d = sc.next_long();

  auto next_list = [] {
    int                  n = sc.next_int();
    std::vector<int64_t> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_long();
    return a;
  };

  auto pre = next_list();
  for (int i = 1; i < n; i++)
  {
    auto cur = next_list();
    std::cout << solve(pre, cur, d) << std::endl;
    pre = std::move(cur);
  }

  return 0;
}
