#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);
using Int = cm::intm<998244353>;

constexpr int N = 5005;
Int fac[N], ifac[N], ans[N];
int n, m;

AT_INIT({
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < N; i++)
    fac[i] = fac[i - 1] * i;
  for (int i = 1; i < N; i++)
    ifac[i] = fac[i].inv();
});

Int binom(int n, int r)
{
  if (r < 0 || r > n) return 0;
  return fac[n] * ifac[n - r] * ifac[r];
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();

  std::fill(ans, ans + N, 1);
  for (int i = 0; i < m; i++)
  {
    int cnt = (n + m - i - 1) / m;
    for (int j = 1; j <= n; j++)
      ans[j] *= binom(j, cnt) * fac[cnt];
  }
  for (int i = n; i >= 1; i--)
  {
    see(i, ans[i]);
    for (int j = 1; j < i; j++) 
      if ((i - j) % 2 == 1)
        ans[i] -= binom(i,j) * ans[j];
      else
        ans[i] += binom(i,j) * ans[j];
    see(i, ans[i]);
  }
  see(ans[1], ans[2], ans[3], ans[4]);
  for (int i = 1; i <= n; i++)
    std::cout << ans[i] * ifac[i] << std::endl;
  return 0;
}

