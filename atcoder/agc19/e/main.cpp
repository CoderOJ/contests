#include "/home/jack/cm/0pch.hpp"

#include "/home/jack/code/Math/Poly/main.h"
#include <string>
#include <vector>

int main()
{
  std::string s, t;
  std::cin >> s;
  std::cin >> t;

  int n  = 0;
  int n1 = 0;
  int n2 = 0;
  for (size_t i = 0; i < s.size(); i++)
    if (s[i] == '1')
    {
      n += 1;
      (t[i] == '1' ? n2 : n1) += 1;
    }

  using namespace Polys;

  std::vector<Int> fac(n + 5);
  fac[0] = 1;
  for (int i = 1; i < n + 5; i++)
    fac[i] = fac[i - 1] * Int(i);

  Poly f(n2 + 1);
  for (int i = 0; i <= n2; i++)
    f[i] = fac[i + 1].inv();

  f = f.pow(n1, n1);

  Int ans = 0;
  for (int i = 0; i <= n2; i++)
    ans += f[i];
  ans = ans * fac[n] * fac[n2] * fac[n1];

  std::cout << ans << std::endl;

  return 0;
}
