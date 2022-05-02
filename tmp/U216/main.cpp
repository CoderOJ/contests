#include <bits/stdc++.h>

std::vector<std::pair<int64_t, int64_t>> ops;

void get_gcd(int64_t x, int64_t y)
{
  if (x < y) std::swap(x, y);
  if (y == 0 || x % y == 0) return;

  if (y + y > x)
  {
    ops.emplace_back(x, y);
    get_gcd(y, x - y);
  }
  else
  {
    {
      ops.emplace_back(x, y);
      int64_t px = x - y;
      for (int64_t dy = y * 2; dy <= x; dy *= 2)
      {
        ops.emplace_back(px, dy / 2);
        ops.emplace_back(x, px - dy / 2);
        px -= dy / 2;
      }
    }

    int64_t d = x / y;
    {
      int64_t px = x;
      for (int i = 0; i < 60; i++)
        if (d & (1ll << i))
        {
          ops.emplace_back(px, y << i);
          px -= y << i;
        }
    }

    get_gcd(y, x % y);
  }
}

void get_multiple(int64_t x, int64_t y, int64_t z)
{
  if (x == z) return;

  int64_t s = x - z;
  {
    int64_t px = x - y;
    ops.emplace_back(x, y);
    for (int64_t dy = y * 2; dy <= s; dy *= 2)
    {
      ops.emplace_back(px, dy / 2);
      ops.emplace_back(x, px - dy / 2);
      px -= dy / 2;
    }
  }
  {
    int64_t d = s / y;
    int64_t px = x;
    for (int i = 0; i < 60; i++)
      if (d & (1ll << i))
      {
        ops.emplace_back(px, y << i);
        px -= y << i;
      }
  }
}

int main()
{
  int64_t a, b, c;
  std::cin >> a >> b >> c;
  if (a < b) std::swap(a, b);
  if (c > a) { puts("-1"); return 0; }
  if (c % std::gcd(a, b) != 0) { puts("-1"); return 0; }

  get_gcd(a, b);
  get_multiple(a, std::gcd(a, b), c);

  printf("%zu\n", ops.size());
  for (const auto &[x, y] : ops)
    printf("%" SCNi64 " %" SCNi64 "\n", x, y);

  return 0;
}
