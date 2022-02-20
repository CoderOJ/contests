#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cmath>
#include <map>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#ifdef CM_DEBUG
cm::scanner<cm::optimal_reader> sc(stdin);
FILE                           *output = stdout;
#else
cm::scanner<cm::optimal_reader> sc(fopen("astronomy.in", "r"));
FILE                           *output = fopen("astronomy.out", "w");
#endif

int main()
{
  int n = sc.next_int();

  std::vector<std::pair<long long, long long>> ps;

  for (int i = 0; i < n; i++)
  {
    long long x = sc.next_int();
    long long y = sc.next_int();
    ps.emplace_back(x, y);
  }

  std::map<std::tuple<long long, long long, long long>, int> cnt;

  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
    {
      const auto &[ax, ay] = ps[i];
      const auto &[bx, by] = ps[j];
      long long a          = ax * ax + ay * ay;
      long long b          = bx * bx + by * by;
      long long c          = (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
      if (a > b)
        std::swap(a, b);
      cnt[{a, b, c}] += 1;
    }

  int m = sc.next_int();

  for (int i = 0; i < m; i++)
  {
    long long a = sc.next_long();
    long long b = sc.next_long();
    long long c = sc.next_long();
    if (a > b)
      std::swap(a, b);
    fprintf(output, "%d\n", cnt[{a, b, c}]);
  }

  return 0;
}
