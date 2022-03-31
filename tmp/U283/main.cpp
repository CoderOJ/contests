#include <bits/stdc++.h>

int n;

int main()
{
  scanf("%d", &n);
  if (n <= 10)
  {
    for (int i = 2; i <= n; i++)
      printf("%d %d\n", 1, i);
  }
  else
  {
    int best_ans = 0;
    int best_m   = 0;
    for (int i = 2, c = 4, s = 5; c <= n; i++, c += (2 * i - 1), s += c)
    {
      int cs = s + (n - c) * i;
      if (cs > best_ans)
      {
        best_ans = cs;
        best_m   = i;
      }
    }
    fprintf(stderr, "best_ans = %d\n", best_ans);

    int cur_u = 1;
    int last = -1;
    for (int l = best_m; l >= 1; l--)
    {
      int u = cur_u++;
      if (last != -1)
        printf("%d %d\n", last, u);
      last = u;
      for (int i = 0; i < 2; i++)
      {
        int cu = last;
        for (int i = 1; i < l; i++)
        {
          int u = cur_u++;
          printf("%d %d\n", cu, u);
          cu = u;
        }
      }
    }
    int key = cur_u - 4;
    while (cur_u <= n)
    {
      int u = cur_u++;
      printf("%d %d\n", key, u);
    }
  }
  return 0;
}
