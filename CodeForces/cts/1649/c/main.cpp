#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();

  std::vector<std::vector<int>> a;
  if (n > m)
  {
    a.resize(n, std::vector<int>(m, 0));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        a[i][j] = sc.next_int();
  }
  else
  {
    std::swap(n, m);
    a.resize(n, std::vector<int>(m, 0));
    for (int j = 0; j < m; j++)
      for (int i = 0; i < n; i++)
        a[i][j] = sc.next_int();
  }

  std::vector<std::pair<int, std::pair<int, int>>> vals;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      vals.push_back({a[i][j], {i, j}});

  std::sort(vals.begin(), vals.end());

  int64_t              ans = 0;
  std::vector<int64_t> sum(m), cnt(m);
  for (auto il = vals.begin(), ir = vals.begin(); il != vals.end(); il = ir)
  {
    while (ir != vals.end() && il->first == ir->first)
      ir++;
    for (auto i = il; i != ir; i++)
    {
      int x = i->second.first;
      int y = i->second.second;
      for (int j = 0; j < m; j++)
        ans += cnt[j] * x - sum[j] + cnt[j] * std::abs(y - j);
      cnt[y] += 1;
      sum[y] += x;
    }
    for (auto i = il; i != ir; i++)
    {
      int x = i->second.first;
      int y = i->second.second;
      cnt[y] -= 1;
      sum[y] -= x;
    }
    // see(std::vector(il, ir));
    // see(ans);
  }

  std::cout << ans << std::endl;

  return 0;
}
