#include <bits/stdc++.h>

int main()
{
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++)
  {
    int n;
    scanf("%d", &n);
    int cnt = 0;
    int64_t sum = 0;
    std::vector<int> others;
    for (int c = 1; c <= 1e9 && cnt < n; c *= 2, cnt++)
    {
      printf("%d ", c);
      sum += c;
    }
    for (int c = 1e9; cnt < n; cnt++, c--)
    {
      printf("%d ", c);
      sum += c;
      others.push_back(c);
    }
    puts("");
    fflush(stdout);

    for (int i = 0; i < n; i++)
    {
      int x;
      scanf("%d", &x);
      others.push_back(x);
      sum += x;
    }

    int64_t k = sum / 2;
    while (k >= others.back())
    {
      k -= others.back();
      printf("%d ", others.back());
      others.pop_back();
    }
    for (int i = 0; i < 30; i++)
      if (k & (1 << i))
        printf("%d ", (1 << i));
    puts("");
    fflush(stdout);
  }
  return 0;
}
