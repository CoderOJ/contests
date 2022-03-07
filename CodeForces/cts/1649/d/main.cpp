#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <numeric>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1'000'005;

int exist[N];
int a[N], n, c;

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    n = sc.next_int();
    c = sc.next_int();
    std::fill(exist, exist + c + 1, 0);
    for (int i = 0; i < n; i++)
    {
      a[i]        = sc.next_int();
      exist[a[i]] = 1;
    }
    std::partial_sum(exist, exist + c + 1, exist);

    for (int i = 1; i <= c; i++)
      for (int j = 1; i * j <= c; j++)
      {
        int jl = i * j;
        int jr = std::min(c, i * (j + 1) - 1);
        // see(i, j, jl, jr, exist[j] - exist[j - 1], exist[jr] - exist[jl - 1]);
        if (exist[j] - exist[j - 1] == 0 && exist[jr] - exist[jl - 1] > 0 &&
            exist[i] - exist[i - 1] > 0)
        {
          puts("No");
          goto fail;
        }
      }

    puts("Yes");
  fail:;
  }
  return 0;
}
