#include <ctype.h>
#include <stdio.h>
#include <string.h>

int read()
{
  int c = getchar_unlocked();
  while (!isdigit(c))
    c = getchar_unlocked();

  int r = 0;
  while (isdigit(c))
  {
    r = r * 10 + (c - '0');
    c = getchar_unlocked();
  }

  return r;
}

#define MOD 1000000007

struct matrix_t
{
  int a[3][3];
};

struct matrix_t matrix_mul(
    const struct matrix_t *lhs, const struct matrix_t *rhs)
{
  struct matrix_t r;
  memset(&r, 0, sizeof(r));

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
    {
      long long cur = 1ll * lhs->a[i][0] * rhs->a[0][j]
                    + 1ll * lhs->a[i][1] * rhs->a[1][j]
                    + 1ll * lhs->a[i][2] * rhs->a[2][j];
      r.a[i][j] = (int)(cur % MOD);
    }

  return r;
}

int main()
{
  struct matrix_t mul_norm = {
      {
          {2, 1, 1},
          {2, 1, 0},
          {1, 1, 1},
      },
  };

  struct matrix_t mul_spec = {
      {
          {1, 0, 0},
          {2, 1, 0},
          {1, 1, 1},
      },
  };

  struct matrix_t mul_final = {
      {
          {1, 1, 1},
          {0, 0, 0},
          {0, 0, 0},
      },
  };

  static struct matrix_t mn_pow[30];
  mn_pow[0] = mul_norm;
  for (int i = 0; i + 1 < 30; i++)
    mn_pow[i + 1] = matrix_mul(&mn_pow[i], &mn_pow[i]);

  int n = read();
  int m = read();

  struct matrix_t cur = {
      {
          {1, 0, 0},
          {0, 0, 0},
          {0, 0, 0},
      },
  };
  int cur_p = 0;

  for (int i = 0; i < m; i++)
  {
    int p = read();

    int d = (p - 1) - cur_p;
    for (int i = 0; i < 30; i++)
      if (d & (1 << i))
        cur = matrix_mul(&mn_pow[i], &cur);
    cur   = matrix_mul(&mul_spec, &cur);
    cur_p = p;
  }

  int d = (n - 1) - cur_p;
  for (int i = 0; i < 30; i++)
    if (d & (1 << i))
      cur = matrix_mul(&mn_pow[i], &cur);
  cur = matrix_mul(&mul_final, &cur);

  printf("%d\n", cur.a[0][0]);

  return 0;
}
