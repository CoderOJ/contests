#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1'000'005;

int a[N], b[N];
int n, m;

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < m; i++)
    b[i] = sc.next_int();
  a[n] = m;

  int64_t r = 1;
  for (int p = 0; p <= n && r <= m; p++)
    if (a[p] > 1)
    {
      int64_t rr = r * a[p];
      for (int i = 0; i * rr <= m; i++)
        for (int j = std::min((int)(m - i * rr) / (int)r, a[p] - 2); j >= 0;
             j--)
          for (int k = 0; k < r; k++)
          {
            int64_t x = i * rr + (j + 1) * r + k;
            int64_t y = i * rr + (j + 0) * r + k;
            if (x < m)
              b[x] -= b[y];
          }
      r = rr;
    }

  std::cout << n << std::endl;
  for (int i = 0; i < n; i++)
    std::cout << a[i] << " ";
  std::cout << std::endl;
  std::cout << m << std::endl;
  for (int i = 0; i < m; i++)
    std::cout << b[i] << " ";
  std::cout << std::endl;

  return 0;
}
