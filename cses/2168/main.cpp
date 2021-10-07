#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  struct inter_t
  {
    int l, r, id;
  };

  int n = sc.next_int();
  std::vector<inter_t> a;
  for (int i = 0; i < n; i++)
  {
    int l = sc.next_int(), r = sc.next_int();
    a.push_back({l, r, i});
  }

  {
    std::sort(a.begin(), a.end(), [](inter_t x, inter_t y) {
      return x.r != y.r ? x.r < y.r : x.l > y.l; });
    std::vector<int> ok(n, 0);
    int max_l = -1;
    for (const auto [l,r,id] : a)
    {
      if (max_l >= l) ok[id] = 1;
      check_max(max_l, l);
    }
    for (int i : ok)
      std::cout << i << " ";
    std::cout << std::endl;
  }
  {
    std::sort(a.begin(), a.end(), [](inter_t x, inter_t y) {
      return x.l != y.l ? x.l < y.l : x.r > y.r; });
    std::vector<int> ok(n, 0);
    int max_r = -1;
    for (const auto [l,r,id] : a)
    {
      if (max_r >= r) ok[id] = 1;
      check_max(max_r, r);
    }
    for (int i : ok)
      std::cout << i << " ";
    std::cout << std::endl;
  }
  return 0;
}

