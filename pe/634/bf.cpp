#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cmath>
#include <cstring>

cm::scanner<cm::optimal_reader> sc(stdin);

#define int unsigned long long

constexpr int N = 3000005;
bool ok[N];

signed main()
{
  int n = sc.next_int();
  for (int a = 2; a * a <= n; a++)
    for (int b = 2; a * a * b * b * b <= n; b++)
      ok[a * a * b * b * b] = true;

  int last = 0;
  for (int i = 1; i <= n; i++)
    printf("%llu %llu\n", i, (last += ok[i]));
  return 0;
}

