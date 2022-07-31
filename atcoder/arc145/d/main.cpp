#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <numeric>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int     n = sc.next_int();
  int64_t m = sc.next_long();

  std::vector<int> p{0, 1, 3, 4};
  int              p_len = 5;
  while ((int)p.size() < n)
  {
    int k = (int)p.size();
    for (int i = 0; i < k; i++)
      p.push_back(p[i] + p_len * 2);
    p_len = p_len * 3;
  }

  p.resize(n - 1);
  p.push_back(p_len * 2);

  int64_t p_sum = std::accumulate(p.begin(), p.end(), (int64_t)0);
  int     det   = (int)((m - p_sum) % n) + n;
  p.back() += det;
  p_sum += det;

  int all_det = (int)((m - p_sum) / n);
  for (int x: p)
    printf("%d ", x + all_det);
  puts("");

  return 0;
}
