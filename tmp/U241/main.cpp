#include <bits/stdc++.h>

const int MOD = 998244353;

template <int N>
struct matrix_t
{
  int data[N][N] = {};

  matrix_t operator* (const matrix_t &rhs) const
  {
    static uint64_t a[N][N]; 
    memset(a, 0, sizeof(a));
    for (int i = 0; i < N; i++)
      for (int k = 0; k < N; k++)
        for (int j = 0; j < N; j++)
          a[i][j] += 1ll * data[i][k] * rhs.data[k][j];
    matrix_t r;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        r.data[i][j] = a[i][j] % MOD;
    return r;
  }

  matrix_t pow(int k) const
  {
    matrix_t r, a = *this;
    for (int i = 0; i < N; i++)
      r.data[i][i] = 1;
    for (; k; k >>= 1)
    {
      if (k & 1) r = r * a;
      a = a * a;
    }
    return r;
  }
};

int solve_odd(int n, int m)
{
  using matrix_t = ::matrix_t<2>;

  matrix_t trans;
  trans.data[0][0] = 0;
  trans.data[0][1] = 1;
  trans.data[1][0] = m - 1;
  trans.data[1][1] = m - 2;

  matrix_t dp;
  dp.data[0][0] = 1;
  dp = trans.pow(n - 1) * dp; 

  int ans = 1ll * dp.data[1][0] * m % MOD;
  return ans;
}

int solve_even(int n, int m)
{
  using matrix_t = ::matrix_t<9>;
  n = n / 2;

  auto code = [](int x, int y) {
    return x * 3 + y;
  };

  matrix_t trans;
  for (int ta = 0; ta < 3; ta++)
    for (int tb = 0; tb < 3; tb++)
      if (ta == 2 || ta != tb)
        for (int sa = 0; sa < 3; sa++)
          if (ta == 2 || ta != sa)
            for (int sb = 0; sb < 3; sb++)
              if (tb == 2 || tb != sb)
                if (sa == 2 || sa != sb)
                {
                  int xa = ta == 2 ? m - 2 - (ta == sa) : 1;
                  int xb = tb == 2 ? m - 2 - (tb == sb) : 1;
                  int64_t x = 1ll * xa * xb;
                  if (ta == 2 && tb == 2)
                  {
                    if (sa == 2 && sb == 2)
                      x -= xa - 1;
                    else
                      x -= std::min(xa, xb);
                  }
                  if (x > 0)
                  {
                    trans.data[code(ta, tb)][code(sa, sb)] = x % MOD;
                    // printf("trans: (%d, %d) -> (%d, %d) = %ld\n", sa, sb, ta, tb, x);
                  }
                }

  matrix_t dp;
  dp.data[code(0, 1)][0] = 1;
  dp = trans.pow(n - 1) * dp;
  
  int ans = 0;
  for (int ta = 0; ta < 3; ta++)
    if (ta != 1)
      for (int tb = 0; tb < 3; tb++)
        if (tb != 0)
          ans = (ans + dp.data[code(ta, tb)][0]) % MOD;
  ans = 1ll * ans * (1ll * m * (m - 1) % MOD) % MOD;

  return ans;
}

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  if (n % 2 == 1)
    printf("%d\n", solve_odd(n, m));
  else
    printf("%d\n", solve_even(n, m));
  return 0;
}
