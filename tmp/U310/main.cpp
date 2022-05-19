#include <bits/stdc++.h>

const int MOD = 998244353;
const int inv2 = (MOD + 1) / 2;
const int N = 20;
const int L = 1 << N;

int a[L], n;

int test_sub(int x)
{
  return x >= MOD ? x - MOD : x;
}

int test_add(int x)
{
  return x < 0 ? x + MOD : x;
}

void fwt(int a[])
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < L; j++)
      if (j & (1 << i))
      {
        int x = a[j ^ (1 << i)], y = a[j];
        a[j ^ (1 << i)] = x + y;
        a[j] = x - y;
      }
}

auto p3 = []{
  std::array<int, L> res;
  res[0] = 1;
  for (int i = 1; i < L; i++)
    res[i] = 3ll * res[i - 1] % MOD;
  return res;
}();

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    int x;
    scanf("%d", &x);
    a[x] += 1;
  }

  fwt(a);
  int ans = 0;
  for (int i = 0; i < L; i++)
  {
    int n3 = (n + a[i]) / 2;
    int n1 = n - n3;
    int cur = (n1 % 2 == 1) ? MOD - p3[n3] : p3[n3];
    ans = test_sub(ans + cur);
  }

  for (int i = 0; i < N; i++)
    ans = (int64_t)ans * inv2 % MOD;
  ans = test_add(ans - 1);

  std::cout << ans << std::endl;

  return 0;
}
