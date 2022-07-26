#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <string>
#include <utility>

int main()
{
  constexpr int MOD = 998'244'353;
  using int_t       = cm::intm<MOD>;

  std::string s;
  std::cin >> s;

  int n = (int)s.size();

  int_t sv = 0;
  for (int i = 0; i < n; i++)
    sv = sv + sv + (s[i] - '0');

  int_t ans = (sv + 1) * sv * (sv - 1);

  cm::array<int_t, 8, 8> dp;
  dp[0][0] = 1;
  for (int i = 0; i < n; i++)
  {
    int c = (s[i] - '0');

    cm::array<int_t, 8, 8> cur;
    for (int pa = 0; pa < 8; pa++)
      for (int pb = 0; pb < 8; pb++)
        if (dp[pa][pb])
          for (int c0 = 0; c0 < 2; c0++)
            for (int c1 = 0; c1 < 2; c1++)
              for (int c2 = 0; c2 < 2; c2++)
              {
                if ((pa & (1 << 0)) || (c0 <= c))
                  if ((pa & (1 << 1)) || (c1 <= c))
                    if ((pa & (1 << 2)) || (c2 <= c))
                    {
                      int d0 = c1 ^ c2;
                      int d1 = c0 ^ c2;
                      int d2 = c0 ^ c1;

                      int va = pa;
                      va |= (c0 < c) << 0;
                      va |= (c1 < c) << 1;
                      va |= (c2 < c) << 2;

                      int vb = pb;
                      if (d0 || d1 || d2)
                      {
                        vb |= (d0 == 0) << 0;
                        vb |= (d1 == 0) << 1;
                        vb |= (d2 == 0) << 2;
                      }

                      cur[va][vb] += dp[pa][pb];
                    }
              }

    dp = cur;
  }

  // see(dp);

  int_t sub = 0;
  for (int pa = 0; pa < 8; pa++)
  {
    sub += dp[pa][0b011];
    sub += dp[pa][0b101];
    sub += dp[pa][0b110];
  }

  std::cout << ans - sub << std::endl;

  return 0;
}
