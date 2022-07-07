#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <string>

int main()
{
  std::string s;
  std::cin >> s;
  int n = static_cast<int>(s.size());

  uint64_t mod = 0;
  int      ctz = 0;
  for (int i = 0; i < n; ++i)
    if (s[i] == '1')
    {
      ctz = i;
      for (int j = i; j < n; ++j)
        mod |= 1LL * (s[j] - '0') << (j - i);
      break;
    }

  for (int i = n - 1; i >= 0 && s[i] == '0'; i--)
    n -= 1;

  n -= ctz;

  if (mod == 0)
  {
    puts("-1");
  }
  else if (mod == 1)
  {
    printf("%d %d\n", ctz + 1, ctz + 2);
  }
  else
  {
    auto mul = [&](uint64_t x, uint64_t y) {
      uint64_t res = 0;
      for (; y; y >>= 1)
      {
        if (y & 1)
          res ^= x;
        x <<= 1;
        if (x >> (n - 1) & 1)
          x ^= mod;
      }
      return res;
    };

    std::unordered_map<uint64_t, int> logs;
    logs[1] = 0;

    int m = n / 2;

    uint64_t xp = 1;
    for (int i = 0; i < 1 << m; ++i)
    {
      logs[xp] = i;
      xp       = mul(xp, 2);
    }

    int64_t  ans = 1LL << n;
    uint64_t xpp = xp;
    for (int i = 1; i < 1 << (n - m); ++i)
    {
      auto it = logs.find(xpp);
      if (it != logs.end())
        ans = std::min(ans, (static_cast<int64_t>(i) << m) - it->second);
      xpp = mul(xpp, xp);
    }

    printf("%d %" SCNi64 "\n", ctz + 1, ans + ctz + 1);

    return 0;
  }
}
