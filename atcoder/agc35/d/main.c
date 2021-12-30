#include <stdio.h>

#define N 18

int a[N];
int n;

long long solve(int l, int r, int fl, int fr)
{
  if (r - l <= 1)
    return 0;
  else
  {
    long long ans = 1e18;
    for (int s = l + 1; s <= r - 1; s++)
    {
      long long cur = solve(l, s, fl, fl + fr) + solve(s, r, fl + fr, fr) +
                      (long long)a[s] * (fl + fr);
      if (cur < ans)
        ans = cur;
    }
    return ans;
  }
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  printf("%lld\n", a[0] + a[n - 1] + solve(0, n - 1, 1, 1));
  return 0;
}
