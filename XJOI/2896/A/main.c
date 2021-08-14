#include <stdio.h>

__attribute__ ((always_inline)) inline
long long iminq(long long a, long long b)
{
  return a < b ? a : b;
}

__attribute__ ((always_inline)) inline
long long imulmodq(long long ax, long long ay, long long mod)
{
  long long a_lb, a_hb;
  __asm__ ("imulq   %3" : "=a"(a_lb), "=d"(a_hb) : "a"(ax), "r"(ay));
  long long remain;
  __asm__ ("idivq   %3" : "=d"(remain) : "a"(a_lb), "d"(a_hb), "r"(mod));
  return remain;
}

long long phi(long long x)
{
  /* printf("calc phi(%lld)\n", x); */
  long long res = x;
  for (long long i = 2; i * i <= x; i++)
    if (x % i == 0)
    {
      res = res / i * (i - 1);
      while (x % i == 0)
        x /= i;
    }
  if (x != 1)
    res = res / x * (x - 1);
  return res;
}

#define LOG_M 50
long long m, k;
long long k_pow2[LOG_M];
long long k_pow(long long exp)
{
  long long res = 1;
  for (int i = 0; i < LOG_M; i++)
    if (exp & (1ll << i))
      res = imulmodq(res, k_pow2[i], m);
  return res;
}

long long gcd(long long a, long long b)
{
  return b == 0 ? a : gcd(b, a % b);
}

long long calc_rounds(long long m)
{
  long long loop = phi(m), min_loop = __INT64_MAX__;
  /* printf("phi = %lld\n", m); */
  for (long long i = 1; i * i <= loop; i++)
    if (loop % i == 0)
    {
      if (k_pow(i) % m == 1 % m)
        min_loop = iminq(min_loop, i);
      if (k_pow(loop / i) % m == 1 % m)
        min_loop = iminq(min_loop, loop / i);
    }
  /* printf("loop = %lld, min_loop = %lld\n", loop, min_loop); */
  /* printf("m = %lld, ans = %lld\n", m, loop / min_loop); */
  return loop / min_loop;
}

int main() 
{
  scanf("%lld%lld", &m, &k);
  
  k_pow2[0] = k;
  for (int i = 0; i + 1 < LOG_M; i++)
    k_pow2[i + 1] = imulmodq(k_pow2[i], k_pow2[i], m);

  // if all initial numbers become 0
  if (k_pow(64) == 0)
  {
    puts("1");
    return 0;
  }

  long long g = gcd(m, k);
  m /= g;
  k %= m;

  long long ans = 0;
  for (long long i = 1; i * i <= m; i++)
  {
    if (m % i == 0)
    {
      ans += calc_rounds(i);
      if (i * i != m)
        ans += calc_rounds(m / i);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
