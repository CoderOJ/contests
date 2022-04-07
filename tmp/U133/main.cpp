#include <bits/stdc++.h>

int64_t n, m, r;

bool check(int64_t x)
{
  int64_t p = std::min(n, static_cast<int64_t>(std::sqrt(static_cast<double>(x) + 0.5)));
  int64_t q = (x - 1) / p + 1;
  return (x * (x - 1) / 2 - x * 2 + (p + q)) <= r;
}

int main()
{
  scanf("%" SCNi64 "%" SCNi64 "%" SCNi64, &n, &m, &r);
  if (n > m) std::swap(n, m);

  int64_t l = 1, r = std::min<int64_t>(2e9, n * m);
  while (l < r)
  {
    int64_t m = l + (r - l + 1) / 2;
    if (check(m)) l = m;
    else r = m - 1;
  }
  printf("%" SCNi64 "\n", l);
  return 0;
}
