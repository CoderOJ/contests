#include <bits/stdc++.h>

int main()
{
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  std::reverse(a.begin(), a.end());

  printf("%d\n", n * 2 * 20);
  for (int i = 0; i < 20; i++)
  {
    std::vector<int> b, c;
    while (!a.empty())
    {
      if (a.back() & (1 << i))
      {
        b.push_back(a.back());
        puts("1 2");
      }
      else
      {
        c.push_back(a.back());
        puts("1 3");
      }
      a.pop_back();
    }
    while (!b.empty())
    {
      puts("2 1");
      a.push_back(b.back());
      b.pop_back();
    }
    while (!c.empty())
    {
      puts("3 1");
      a.push_back(c.back());
      c.pop_back();
    }
  }
  return 0;
}
