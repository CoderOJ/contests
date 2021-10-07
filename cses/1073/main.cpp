#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

struct ftree_t
{
  std::vector<int> a;
  ftree_t(size_t n) : a(n + 5) {}
  static size_t low(size_t x) { return x & (-x); }
  void modify(size_t pos, int val) { pos += 5;
    for (; pos < a.size(); pos += low(pos)) check_max(a[pos], val); }
  int query(size_t pos) { pos += 5; int res = 0;
    for (; pos; pos -= low(pos)) check_max(res, a[pos]); return res; }
};

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  std::vector<int> b(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  for (int i = 0; i < n; i++)
    a[i] = static_cast<int>(std::lower_bound(b.begin(), b.end(), a[i]) - b.begin());
  see(a);

  ftree_t dp(n + 1);
  for (int x: a)
    dp.modify(x, dp.query(x) + 1);
  std::cout << dp.query(n - 1) << std::endl;

  return 0;
}

