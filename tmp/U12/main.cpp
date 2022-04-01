#include <bits/stdc++.h>

int64_t int64_sqrt(int64_t x)
{
  int64_t t = static_cast<int64_t>(std::sqrt(x));
  for (int64_t i = std::max<int64_t>(0, t - 10); ; i++)
    if (i * i == x)
      return i;
}

int main()
{
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++)
  {
    int64_t g, l;
    scanf("%" SCNi64 "%" SCNi64, &g, &l);
    l = l / g;
    printf("%" SCNi64 " %" SCNi64 "\n", int64_sqrt(l) * 2 * g, (1 + l) * g);
  }
  return 0;
}
