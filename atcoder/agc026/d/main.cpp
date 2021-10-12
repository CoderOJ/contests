#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t = cm::intm<MOD>;
using pint_t = std::pair<int_t, int_t>; // 0101, all

pint_t solve(int l, int r, std::vector<int> &v)
{
  int mi = (int)(1e9 + 1e4);
  for (int i = l; i < r; i++)
  {
    mi = std::min(mi, v[i]);
  }
  for (int i = l; i < r; i++)
  {
    v[i] -= mi;
  }
  int other = 0;
  int_t c01 = int_t(1), c01self = int_t(1);
  int p = l;
  while (p < r)
  {
    if (v[p] == 0)
    {
      other++;
      p++;
      continue;
    }
    int q = p;
    while (q < r && v[q])
      q++;
    pint_t ch = solve(p, q, v);
    c01 *= ch.first;
    c01self *= (ch.first + ch.second);
    p = q;
  }
  int_t self01 = int_t(2).pow(mi) * c01;
  int_t selfall = int_t(2).pow(other) * c01self + self01 - int_t(2) * c01;
  return pint_t(self01, selfall);
}

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  pint_t p = solve(0, n, a);
  std::cout << p.second << std::endl;
  return 0;
}
