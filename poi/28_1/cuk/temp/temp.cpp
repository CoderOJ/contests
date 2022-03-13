#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int64_t ans[8];
  std::fill(ans, ans + 8, 0x3f3f3f3f3f3f3f3f);
  ans[0] = 0;

  int all_state = 0;

  int n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int64_t a[3];
    a[0]        = sc.next_int();
    a[1]        = sc.next_int();
    a[2]        = sc.next_int();
    int64_t sum = a[0] + a[1] + a[2];

    int64_t cur[8];
    std::fill(cur, cur + 8, 0x3f3f3f3f3f3f3f3f);

    for (int i = 0; i < 3; i++)
      if (a[i] > 0)
        all_state |= (1 << i);

    for (int i = 0; i < 3; i++)
      for (int p = 0; p < 8; p++)
        check_min(cur[p | (1 << i)], ans[p] + sum - a[i]);

    std::copy(cur, cur + 8, ans);
  }

  std::cout << ans[all_state] << std::endl;

  return 0;
}
