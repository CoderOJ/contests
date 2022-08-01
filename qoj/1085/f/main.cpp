#include <bits/stdc++.h>

const int N = 2005;

int64_t ans;

int a[N][N], ta[N][N];

bool eq(std::initializer_list<int> s)
{
  if (s.size() == 0)
    return true;
  for (auto &v: s)
  {
    if (v != *s.begin())
      return false;
  }
  return true;
}

void solve(int xl, int xr, int yl, int yr, int a[][N])
{
  static int L[N], R[N], D[N][N], U[N][N];
  static int lU[N][N], lD[N][N], rU[N][N], rD[N][N];
  for (int i = xl; i <= xr; ++i)
    for (int j = xl; j <= xr; ++j)
      U[i][j] = D[i][j] = lU[i][j] = lD[i][j] = rU[i][j] = rD[i][j] = 0;

  int mid = (yl + yr) / 2;
  for (int i = xl; i <= xr; ++i)
  {
    L[i] = R[i] = 0;
    while (mid - L[i] >= yl && a[i][mid] == a[i][mid - L[i]])
      ++L[i];
    while (mid + 1 + R[i] <= yr && a[i][mid + 1] == a[i][mid + 1 + R[i]])
      ++R[i];
  }
  for (int i = xr; i >= xl; --i)
    for (int j = yl; j <= yr; ++j)
    {
      if (i < xr && a[i][j] == a[i + 1][j])
        D[i][j] = D[i + 1][j];
      else
        D[i][j] = i;
    }
  for (int i = xl; i <= xr; ++i)
    for (int j = yl; j <= yr; ++j)
    {
      if (i > xl && a[i][j] == a[i - 1][j])
        U[i][j] = U[i - 1][j];
      else
        U[i][j] = i;
    }

  for (int i = xl; i <= xr; ++i)
  {
    for (int j = mid; j >= mid - L[i] + 1; --j)
      ++lU[i][U[i][j]], ++lD[i][D[i][j]];
    for (int j = mid + 1; j <= mid + R[i]; ++j)
      ++rU[i][U[i][j]], ++rD[i][D[i][j]];

    for (int j = xl + 1; j <= i; ++j)
    {
      lU[i][j] += lU[i][j - 1];
      rU[i][j] += rU[i][j - 1];
    }
    for (int j = xr - 1; j >= i; --j)
    {
      lD[i][j] += lD[i][j + 1];
      rD[i][j] += rD[i][j + 1];
    }
  }

  for (int i = xl; i <= xr; ++i)
  {
    for (int j = i + 1; j <= xr; ++j)
    {
      if (eq({a[i][mid], a[j][mid], a[i][mid + 1], a[j][mid + 1]}))
      {
        int l, r;
        if (L[i] < L[j])
          l = lD[i][j];
        else
          l = lU[j][i];
        if (R[i] < R[j])
          r = rD[i][j];
        else
          r = rU[j][i];
        ans += 1ll * l * r;
      }
    }
  }
}

void divide(int xl, int xr, int yl, int yr)
{
  if (xl >= xr || yl >= yr)
    return;
  if (xr - xl < yr - yl)
  {
    int mid = (yl + yr) >> 1;
    solve(xl, xr, yl, yr, a);
    divide(xl, xr, yl, mid);
    divide(xl, xr, mid + 1, yr);
  }
  else
  {
    int mid = (xl + xr) >> 1;
    solve(yl, yr, xl, xr, ta);
    divide(xl, mid, yl, yr);
    divide(mid + 1, xr, yl, yr);
  }
}

int main()
{
  int  n, m;
  char s[N];
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%s", s + 1);
    for (int j = 1; j <= m; ++j)
    {
      a[i][j] = ta[j][i] = s[j] - 'a';
    }
  }
  divide(1, n, 1, m);
  printf("%" SCNi64 "\n", ans);
  return 0;
}
