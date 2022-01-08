#include <stdio.h>
#include <string.h>

#define N 5005

char s[N * 2], ta[N], tb[N];
int  n, k;

int main()
{
  scanf("%d%d", &n, &k);
  scanf("%s", s);
  for (int i = 0; i < n; i++)
    s[n + n - i - 1] = s[i];

  if (k >= 20)
  {
    char c_min = s[0];
    for (int i = 0; i < n; i++)
      if (s[i] < c_min)
        c_min = s[i];
    for (int i = 0; i < n; i++)
      putchar_unlocked(c_min);
    puts("");
    return 0;
  }

  memcpy(ta, s, sizeof(char) * n);

  for (const char *l = s; l < s + n; l++)
  {
    const char *r = l;
    while (*r == *l)
      r++;

    int len = (int)(r - l) << (k - 1);
    if (len >= n)
    {
      memset(tb, *l, n);
    }
    else
    {
      memset(tb, *l, len);
      memcpy(tb + len, r, n - len);
    }

    if (strcmp(ta, tb) > 0)
      strcpy(ta, tb);
  }

  puts(ta);

  return 0;
}
