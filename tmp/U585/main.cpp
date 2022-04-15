#include <bits/stdc++.h>

const int MOD = 998244353;

int inv(int x)
{
  return x == 1 ? 1 : 1ll * inv(MOD % x) * (MOD - MOD / x) % MOD;
}

struct matrix_t
{
  std::array<std::array<int, 3>, 3> a = {{{0}}};

  matrix_t operator+(const matrix_t &rhs) const
  {
    matrix_t res;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        res.a[i][j] = (a[i][j] + rhs.a[i][j]) % MOD;
    return res;
  }

  matrix_t operator*(int64_t rhs) const
  {
    rhs %= MOD;
    matrix_t res;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        res.a[i][j] = a[i][j] * rhs % MOD;
    return res;
  }

  matrix_t operator*(const matrix_t &rhs) const
  {
    matrix_t res;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        res.a[i][j] =
            (1ll * a[i][0] * rhs.a[0][j] + 1ll * a[i][1] * rhs.a[1][j] +
             1ll * a[i][2] * rhs.a[2][j]) %
            MOD;
    return res;
  }

  matrix_t pow(int k) const
  {
    matrix_t r, a = *this;
    for (int i = 0; i < 3; i++)
      r.a[i][i] = 1;
    for (; k; k >>= 1)
    {
      if (k & 1)
        r = r * a;
      a = a * a;
    }
    return r;
  }

  void display()
  {
    printf("[[%d %d %d] [%d %d %d] [%d %d %d]]\n",
           a[0][0],
           a[0][1],
           a[0][2],
           a[1][0],
           a[1][1],
           a[1][2],
           a[1][0],
           a[1][1],
           a[1][2]);
  }
};

const int N = 200005;

int n, k, a[N], *ap = a;

int64_t count_subinterval(int l, int r)
{
  return 1ll * (r - l) * (r - l + 1) / 2;
}

int64_t count_intersect(int l, int r)
{
  return count_subinterval(0, n) - count_subinterval(0, l) -
         count_subinterval(r, n);
}

int64_t count_superinterval(int l, int r)
{
  return 1ll * (l - 0 + 1) * (n - r + 1);
}

/**
 * dp values
 * + f: p(tagged)
 * + g: p(any ancestor tagged)
 */

enum dp_type_t
{
  F = 0,
  G = 1,
  I = 2,
};

std::array<int, 3> DF = {{1, 0, 0}};
std::array<int, 3> DG = {{0, 1, 0}};
std::array<int, 3> D0 = {{0, 0, 0}};
std::array<int, 3> D1 = {{0, 0, 1}};

matrix_t trans0 = {{D0, D0, D1}};
matrix_t trans1 = {{D1, D1, D1}};
matrix_t trans2 = {{DG, DG, D1}};
matrix_t trans3 = {{DF, D1, D1}};
matrix_t trans4 = {{DF, DG, D1}};

/**
 * node types:
 * + 0: tag be cleared
 * + 1: be tagged
 * + 2: be pushed
 * + 3: ancestor (not including itself) be pushed
 * + 4: not changed
 */

struct segment_t
{
  int        l, r, m;
  segment_t *f;

  int64_t count0() const
  {
    return count_intersect(l, r) - count_superinterval(l, r);
  }

  int64_t count1() const
  {
    return count_superinterval(l, r) -
           (f ? count_superinterval(f->l, f->r) : 0);
  }

  int64_t count2() const
  {
    if (f == nullptr)
      return 0;
    else
      return count_intersect(f->l, f->r) - count_intersect(l, r);
  }

  int64_t count3() const
  {
    if (f == nullptr)
      return 0;
    else
      return count_superinterval(f->l, f->r);
  }

  int64_t count4() const
  {
    return count_subinterval(0, n) - count0() - count1() - count2() - count3();
  }

  int calc(int k) const
  {
    matrix_t trans =
        (trans0 * count0() + trans1 * count1() + trans2 * count2() +
         trans3 * count3() + trans4 * count4());
    trans = trans * inv(count_subinterval(0, n) % MOD);

    matrix_t init;
    init.a[F][0] = 0;
    init.a[G][0] = 0;
    init.a[I][0] = 1;

    init = trans.pow(k) * init;
    return init.a[F][0];
  }
};

segment_t p[N * 2];

void build(int u, int l, int r, segment_t *f)
{
  if (r - l == 1)
  {
    p[u] = {l, r, -1, f};
  }
  else
  {
    int m = *ap++;
    p[u]  = {l, r, m, f};
    build(u + 1, l, m, &p[u]);
    build(u + (m - l) * 2, m, r, &p[u]);
  }
}

int main()
{
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n - 1; i++)
    scanf("%d", &a[i]);
  build(0, 0, n, nullptr);

  int64_t ans = 0;
  for (int i = 0; i < n * 2 - 1; i++)
    ans += p[i].calc(k);
  ans = ans % MOD;
  printf("%" SCNi64 "\n", ans);

  return 0;
}
