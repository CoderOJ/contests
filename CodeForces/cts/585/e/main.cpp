#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstring>
#include <vector>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int W = 10'000'005;
bool is_prime[W];
std::vector<int> primes;
int mu[W], fac[W];

void sieve()
{
  memset(is_prime, 1, sizeof(is_prime));
  mu[1] = 1;
  is_prime[1] = false;
  for (int i = 2; i < W; i++)
  {
    if (is_prime[i])
    {
      primes.push_back(i);
      mu[i] = -1;
      fac[i] = i;
    }
    for (int j : primes)
    {
      int k = i * j;
      if (k >= W)
        break;
      is_prime[k] = false;
      fac[k] = j;
      if (i % j == 0)
      {
        mu[k] = 0;
        break;
      }
      mu[k] = mu[i] * mu[j];
    }
  }
}

std::vector<int> factors(int n)
{
  std::vector<int> res{1};
  while (n > 1)
  {
    std::vector<int> cur;
    int p = fac[n], pi = 0;
    while (n % p == 0)
      n /= p, pi++;
    for (int x : res)
      for (int i = 0, pc = 1; i <= pi; i++, pc *= p)
        cur.push_back(x * pc);
    res = std::move(cur);
  }
  return res;
}

constexpr int MOD = 1'000'000'007;
constexpr int N = 500005;
using int_t = cm::intm<MOD>;

int_t g_cnt[W];
int a[N];
int n;

int main()
{
  sieve();

  n = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  for (int i = 0; i < W; i++)
    g_cnt[i] = 1;
  for (int i = 0; i < n; i++)
    for (int p : factors(a[i]))
      g_cnt[p] *= 2;
  for (int i = 0; i < W; i++)
    g_cnt[i] -= 1;
  for (int p = 2; p < W; p++)
    if (is_prime[p])
      for (int j = 1; j * p < W; j++)
        g_cnt[j] -= g_cnt[j * p];
  g_cnt[1] = 0;

  // see(std::vector<int_t>(g_cnt, g_cnt + 10));

  for (int p = 2; p < W; p++)
    if (is_prime[p])
      for (int j = (W - 1) / p; j >= 1; j--)
        g_cnt[j] += g_cnt[j * p];

  // see(std::vector<int_t>(g_cnt, g_cnt + 10));

  int_t ans = 0;
  for (int i = 0; i < n; i++)
  {
    for (int p : factors(a[i]))
      ans += mu[p] * g_cnt[p];
  }

  std::cout << ans << std::endl;

  return 0;
}
