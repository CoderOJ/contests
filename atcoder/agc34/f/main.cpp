#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 998244353;
using int_t       = cm::intm<MOD>;

constexpr int N = 1 << 18;

void dft(int_t a[], int l)
{
  for (int i = 1; i < l; i <<= 1)
    for (int j = 0; j < l; j++)
      if (j & i)
      {
        const int_t x = a[j ^ i];
        const int_t y = a[j];
        a[j ^ i]      = x + y;
        a[j]          = x - y;
      }
}

void idft(int_t a[], int l)
{
  dft(a, l);
  int_t inv = int_t(l).inv();
  for (int i = 0; i < l; i++)
    a[i] *= inv;
}

int n, l;

int_t p[N], p_sum;
int_t s[N];
int_t a[N];

int main()
{
  n = sc.next_int();
  l = 1 << n;

  for (int i = 0; i < l; i++)
  {
    p[i] = sc.next_int();
    p_sum += p[i];
  }
  auto p_sum_inv = p_sum.inv();
  for (int i = 0; i < l; i++)
    p[i] *= p_sum_inv;
  p[0] = p[0] - 1;

  std::fill(s, s + l, -1);
  s[0] += l;

  dft(p, l);
  dft(s, l);
  for (int i = 0; i < l; i++)
  {
    a[i] = s[i] * p[i].pow(MOD - 2);
  }
  idft(a, l);

  for (int i = 0; i < l; i++)
    std::cout << a[i] - a[0] << std::endl;

  return 0;
}
