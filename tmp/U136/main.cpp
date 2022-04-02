#include <bits/stdc++.h>

int f(int n, int m)
{
  if (n > m) std::swap(n, m);
  int a0 = n == 0 ? n : n + 1;
  int a1 = (m - n) < 4 ? (m - n) : (m - n) - ((m - n) / 2  - 1);
  if (a0 > 0 && (m - n) >= 3 && (m - n) % 2 == 1) a1 -= 1;
  return a0 + a1;
}

int main()
{
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++)
  {
    int n, m;
    scanf("%d%d", &n, &m);
    n--, m--;
    printf("%d\n", f(n, m));
  }
  return 0;
}
