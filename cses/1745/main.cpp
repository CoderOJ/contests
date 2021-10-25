#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <bitset>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int N = 100005;
  using dp_t = std::bitset<N>;

  dp_t dp;
  dp.set(0);
  int n = sc.next_int();
  for (int i = 0; i < n; i++)
    dp |= (dp << sc.next_int());

  printf("%zu\n", dp.count() - 1);
  for (int i = 1; i < N; i++)
    if (dp[i])
      printf("%d ", i);
  return 0;
}

