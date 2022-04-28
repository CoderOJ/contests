#include <bits/stdc++.h>

int main()
{
  int n, m, t;
  std::cin >> n >> m >> t;
  if (m > n) m = n;

  const int cx = 1000000;

  {
    printf("%d\n", n);
    int use_n = 0;
    int u0 = 0, u1 = 0;
    for (int i = 1; use_n < n; i++)
    {
      for (int j = 0; j < i && use_n < n; j++)
      {
        if (use_n >= n - m)
          printf("%d %d\n", cx + i - 1, cx - u0 - 1);
        else
          printf("%d %d\n", cx + i - 1, cx + j);
        u0 += 1;
        use_n += 1;
      }
      for (int j = 0; j < i && use_n < n; j++)
      {
        if (use_n >= n - m)
          printf("%d %d\n", cx - u1 - 1, cx + i);
        else
          printf("%d %d\n", cx + j, cx + i);
        u1 += 1;
        use_n += 1;
      }
    }
  }

  {
    printf("%d\n", m);
    int use_m = 0;
    int u0 = 0, u1 = 0;
    for (int i = 1; use_m < n; i++)
    {
      for (int j = 0; j < i && use_m < n; j++)
      {
        if (use_m >= n - m)
          printf("1 %d %d\n", cx - u0 - 1, cx + j);
        u0 += 1;
        use_m += 1;
      }
      for (int j = 0; j < i && use_m < n; j++)
      {
        if (use_m >= n - m)
          printf("0 %d %d\n", cx - u1 - 1, cx + j);
        u1 += 1;
        use_m += 1;
      }
    }
  }

  return 0;
}
