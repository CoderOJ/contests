#include <bits/stdc++.h>

uint64_t tab[][2] = {
  {1, 7},
  {1, 5},
  {3, 5},
  {3, 7},
  {5, 7},
  {2, 4},
  {2, 6},
  {4, 6},
};

int main()
{
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++)
  {
    uint64_t n;
    scanf("%" SCNu64, &n);
    if (n == 1'000'000'000'000'000'000ul)
      printf("%" SCNu64 " %" SCNu64 "\n", n - 4, n);
    else
    {
      uint64_t tail = n & 7;
      uint64_t base = n - tail;
      printf("%" SCNu64 " %" SCNu64 "\n", base | tab[tail][0], base | tab[tail][1]);
    }
  }
  return 0;
}
