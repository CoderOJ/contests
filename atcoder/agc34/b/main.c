#include <stdio.h>

#define N 200005

char s[N];

int main()
{
  fgets(s, N, stdin);

  enum state_t
  {
    init,
    last_b,
  };

  enum state_t state = init;

  long long ans   = 0;
  int       cur_a = 0;

  for (char *i = s; *i > 32; i++)
  {
    char c = *i;

    if (state == init)
    {
      if (c == 'A')
      {
        cur_a++;
        state = init;
      }
      else if (c == 'B')
      {
        state = last_b;
      }
      else
      {
        cur_a = 0;
        state = init;
      }
    }
    else
    {
      if (c == 'A')
      {
        cur_a = 1;
        state = init;
      }
      else if (c == 'B')
      {
        cur_a = 0;
        state = last_b;
      }
      else
      {
        ans += cur_a;
        state = init;
      }
    }
  }

  printf("%lld\n", ans);

  return 0;
}
