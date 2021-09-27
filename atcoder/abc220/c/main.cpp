#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <numeric>
#define int long long
cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100005;
int a[N], n;

signed main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_long();
  int x = sc.next_long();

  std::partial_sum(a, a + n, a);
  int tot = a[n - 1];
  int ans = x / tot * n; x %= tot;

  for (int i = 0; i < n; i++)
    if (x < a[i])
    {
      ans += i + 1;
      break;
    }

  printf("%lld\n", ans);
  return 0;
}

