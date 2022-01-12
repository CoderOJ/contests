#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstdint>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 135;

int      n, p, q, cnt[N];
uint32_t ans, rem, c[N];

void insert(int x, int sign)
{
  for (int d = 2; d <= p; d++)
    for (; x % d == 0; x /= d)
      cnt[d] += sign;
  rem *= x;
}

int main()
{
  n = sc.next_int();
  p = std::min(sc.next_int(), n - 1);
  q = sc.next_int();

  rem = 1;
  for (int i = 0; i <= p; i++)
  {
    c[i] = rem;
    for (int d = 2; d <= p; d++)
      for (int j = 0; j < cnt[d]; j++)
        c[i] *= d;
    if (i == p)
      continue;
    insert(n - i, 1);
    insert(i + 1, -1);
  }

  for (int m = 1; m <= q; m++)
  {
    unsigned res = 0, pwr = 1;
    for (int i = 0; i <= p; i++)
    {
      res += c[i] * pwr;
      pwr *= m;
    }
    ans ^= res * m;
  }

  printf("%u\n", ans);

  return 0;
}
