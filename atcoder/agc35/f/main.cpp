#include "/home/jack/code/Math/Poly/main.h"
#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  using namespace Polys;

  int  n = sc.next_int();
  int  m = sc.next_int();
  Poly f(n + 1);

  Int fac = 1;
  for (int i = 0; i <= n; i++)
  {
    if (i != 0)
      fac *= Int(i);
    f[i] = Int(n - i + 1) / fac;
  }

  f = f.pow(m, m);

  Int ans = 0;
  fac     = 1;
  for (int i = 0; i <= n; i++)
  {
    std::cout << i << " " << f[i] << std::endl;
    ans += f[i] * fac;
    fac *= Int(n - i);
  }
  std::cout << ans << std::endl;

  return 0;
}
