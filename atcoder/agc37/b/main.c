#include <ctype.h>
#include <stdio.h>

#define MOD 998244353;

int main()
{
  int n;
  scanf("%d", &n);

  int ans = 1;
  for (int i = 1; i <= n; i++)
    ans = 1ll * ans * i % MOD;

  int r   = 0;
  int g   = 0;
  int b   = 0;
  int rg  = 0;
  int rb  = 0;
  int gb  = 0;
  int rgb = 0;

  for (int i = 0; i < 3 * n; i++)
  {
    int c = getchar_unlocked();
    while (!isalpha(c))
      c = getchar_unlocked();

#define TRANS(from, to)                                                        \
  do                                                                           \
  {                                                                            \
    ans = 1ll * ans * from % MOD;                                              \
    to++;                                                                      \
    from--;                                                                    \
  } while (0)

    if (c == 'R')
    {
      if (gb > 0)
        TRANS(gb, rgb);
      else if (g > 0)
        TRANS(g, rg);
      else if (b > 0)
        TRANS(b, rb);
      else
        r++;
    }
    else if (c == 'G')
    {
      if (rb > 0)
        TRANS(rb, rgb);
      else if (r > 0)
        TRANS(r, rg);
      else if (b > 0)
        TRANS(b, gb);
      else
        g++;
    }
    else
    {
      if (rg > 0)
        TRANS(rg, rgb);
      else if (r > 0)
        TRANS(r, rb);
      else if (g > 0)
        TRANS(g, gb);
      else
        b++;
    }

#undef TRANS
  }

  printf("%d\n", ans);

  return 0;
}
