#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <set>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();

    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();

    std::vector<std::pair<int, int>> ops;
    std::vector<int>                 lens;

    while (!a.empty())
    {
      int x = a.back();
      a.pop_back();
      auto x_pre = std::find(a.begin(), a.end(), x);

      if (x_pre == a.end())
      {
        puts("-1");
        goto fail;
      }

      int a_len   = static_cast<int>(a.end() - x_pre);
      int pre_len = static_cast<int>(x_pre - a.begin());
      lens.emplace_back(a_len * 2);
      std::reverse(std::next(x_pre), a.end());
      for (auto it = std::next(x_pre); it != a.end(); it++)
      {
        ops.emplace_back(pre_len, *it);
        pre_len += 1;
      }
      a.erase(x_pre);
    }

    std::cout << ops.size() << '\n';
    for (const auto &[x, y] : ops)
      std::cout << x << ' ' << y << '\n';
    std::reverse(lens.begin(), lens.end());
    std::cout << lens.size() << '\n';
    for (int x : lens)
      std::cout << x << ' ';
    std::cout << '\n';

  fail:;
  }
  return 0;
}
