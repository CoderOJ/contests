#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 2001

char s[N], t[N];
int n;

struct option_t
{
  int c_pre1;
  int c_suf1;
};

int
option_cmp (const void *a, const void *b)
{
  return ((const struct option_t *)a)->c_pre1
         - ((const struct option_t *)b)->c_pre1;
}

int
main ()
{
  scanf ("%s%s", s, t);
  n = (int)strlen (s);

  bool s_any = false;
  bool t_any = false;
  for (int i = 0; i < n; i++)
    {
      if (s[i] == '1')
        s_any = true;
      if (t[i] == '1')
        t_any = true;
    }

  if (!t_any)
    {
      if (s_any)
        puts ("-1");
      else
        puts ("0");
    }
  else
    {
      static int pre1[N];
      if (t[0] == '1')
        pre1[0] = 0;
      else
        for (int i = n - 1; i >= 0; i--)
          if (t[i] == '1')
            {
              pre1[0] = i - n;
              break;
            }
      for (int i = 1; i < n; i++)
        {
          if (t[i] == '1')
            pre1[i] = 0;
          else
            pre1[i] = -1 + pre1[i - 1];
        }

      static int suf1[N];
      if (t[n - 1] == '1')
        suf1[n - 1] = 0;
      else
        for (int i = 0; i < n; i++)
          if (t[i] == '1')
            {
              suf1[n - 1] = i + 1;
              break;
            }
      for (int i = n - 2; i >= 0; i--)
        {
          if (t[i] == '1')
            suf1[i] = 0;
          else
            suf1[i] = 1 + suf1[i + 1];
        }

      int ans = INT32_MAX;
      for (int bs = -n + 1; bs <= n - 1; bs++)
        {
          int cur_ans = abs (bs);

          int lb = bs < 0 ? bs : 0;
          int rb = bs > 0 ? bs : 0;

          static struct option_t options[N];
          for (int i = 0; i < n; i++)
            {
              char sc = s[i];
              char tc = t[(i + n + bs) % n];

              if (sc != tc)
                {
                  cur_ans += 1;
                  options[i] = (struct option_t){
                    pre1[i] < lb ? lb - pre1[i] : 0,
                    suf1[i] > rb ? suf1[i] - rb : 0,
                  };
                }
              else
                {
                  options[i] = (struct option_t){ 0, 0 };
                }
            }

          qsort (options, n, sizeof (struct option_t), option_cmp);

          int min_det = INT32_MAX;
          int max_suf1 = 0;
          for (int i = n - 1; i >= 0; i--)
            {
              int cur_det = options[i].c_pre1 + max_suf1;
              if (cur_det < min_det)
                min_det = cur_det;
              if (options[i].c_suf1 > max_suf1)
                max_suf1 = options[i].c_suf1;
            }
          cur_ans += min_det * 2;

          /* printf("offset = %d, ans = %d\n", bs, cur_ans); */

          if (cur_ans < ans)
            ans = cur_ans;
        }

      printf ("%d\n", ans);
    }

  return 0;
}
