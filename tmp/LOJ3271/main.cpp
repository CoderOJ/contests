#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 1000005, 105)

using inter_t = std::pair<int, int>;

int     a[N][2], n;
inter_t dp[N][2];

constexpr inter_t emp{-1, -1};

inter_t join(inter_t a, inter_t b)
{
  if (a == emp)
    return b;
  else if (b == emp)
    return a;
  else
    return {std::min(a.first, b.first), std::max(a.second, b.second)};
}

inter_t shift(inter_t x, int d)
{
  if (x == emp)
    return x;
  else
    return {x.first + d, x.second + d};
}

bool contains(inter_t x, int v)
{
  return x.first <= v && v < x.second;
}

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n * 2; i++)
    a[i][0] = sc.next_int();
  for (int i = 0; i < n * 2; i++)
    a[i][1] = sc.next_int();

  dp[0][0] = inter_t(1, 2);
  dp[0][1] = inter_t(0, 1);
  for (int i = 1; i < n * 2; i++)
  {
    dp[i][0] = shift(join(a[i][0] >= a[i - 1][0] ? dp[i - 1][0] : emp,
                          a[i][0] >= a[i - 1][1] ? dp[i - 1][1] : emp),
                     1);
    dp[i][1] = shift(join(a[i][1] >= a[i - 1][0] ? dp[i - 1][0] : emp,
                          a[i][1] >= a[i - 1][1] ? dp[i - 1][1] : emp),
                     0);
  }

  if (contains(dp[n * 2 - 1][0], n) || contains(dp[n * 2 - 1][1], n))
  {
    static char ans[N];
    int c = n, last = 0x3f3f3f3f;
    for (int i = n * 2 - 1; i >= 0; i--)
    {
      if (contains(dp[i][0], c) && a[i][0] <= last)
      {
        last = a[i][0];
        ans[i] = 'A';
        c -= 1;
      }
      else
      {
        last = a[i][1];
        ans[i] = 'B';
      }
    }
    puts(ans);
  }
  else
  {
    puts("-1");
  }

  return 0;
}
