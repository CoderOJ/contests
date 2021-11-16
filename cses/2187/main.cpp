#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t = cm::intm<MOD>;
CONSTRAINT(N, 1000005, 1005)
int_t fac[N], inv[N], ifac[N];

int main()
{
  fac[0] = fac[1] = 1;
  inv[0] = inv[1] = 1;
  ifac[0] = ifac[1] = 1;
  for (int i = 2; i < N; i++)
  {
    fac[i] = fac[i - 1] * i;
    inv[i] = inv[MOD % i] * (MOD - MOD / i);
    ifac[i] = ifac[i - 1] * inv[i];
  }

  auto binom = [](int n, int m) -> int_t {
    if (m < 0 || m > n)
      return 0;
    else
      return fac[n] * ifac[m] * ifac[n - m];
  };

  int n = sc.next_int();
  std::vector<char> s(n + 1);
  int k = static_cast<int>(sc.next_token(s.data()) - s.data());

  if (n % 2 == 1)
  {
    puts("0");
  }
  else
  {
    int cur_level = 0;
    for (char *i = s.data(); *i; i++)
    {
      if (*i == '(')
        cur_level++;
      else
      {
        cur_level--;
        if (cur_level < 0)
        {
          puts("0");
          return 0;
        }
      }
    }
    int up_cnt = (n - k - cur_level) / 2;
    std::cout << binom(n - k, up_cnt) - binom(n - k, up_cnt - 1) << std::endl;
  }

  return 0;
}
