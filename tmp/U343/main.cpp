#include <bits/stdc++.h>

std::map<int, std::vector<int>> tab = {
#include "./tab.hpp"
};

std::vector<int> primes = {
#include "./primes.hpp"
};

bool check(int p1, int p2, int n)
{
  return 
    p1 * p1 >= n &&
    p2 * p2 * p2 < n &&
    p1 * p2 < p2 * p2 * p2;
}

int main()
{
  int t; scanf("%d", &t);
  for (int i = 0; i < t; i++)
  {
    int n; scanf("%d", &n);
    if (n <= 200)
    {
      for (int x : tab[n])
        printf("%d ", x);
      puts("");
    }
    else
    {
      [n]{
        for (int p1 : primes)
          for (int p2 : primes)
            if (check(p1, p2, n))
            {
              printf("3 %d %d %d\n", p1 * p2, p1 * p2, p1 * p2);
              return;
            }
      }();
    }
  }
  return 0;
}
