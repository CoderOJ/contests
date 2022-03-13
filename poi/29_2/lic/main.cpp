#include "/home/jack/cm/debug"
#include "/home/jack/cm/math_util"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

std::vector<std::pair<int64_t, int>> fac_phi(int64_t x)
{
  std::vector<std::pair<int64_t, int>> res{{1, 1}};
  for (int64_t i = 2; i * i <= x; i++)
    if (x % i == 0) [[unlikely]]
    {
      size_t ori_size = res.size();
      for (size_t j = 0; j < ori_size; j++)
        res.emplace_back(i * res[j].first, -res[j].second);
      while (x % i == 0)
        x /= i;
    }
  if (x != 1)
  {
    size_t ori_size = res.size();
    for (size_t i = 0; i < ori_size; i++)
      res.emplace_back(x * res[i].first, -res[i].second);
  }
  return res;
}

int64_t count_coprime(const std::vector<std::pair<int64_t, int>> &n_phi,
                      int64_t                                     k)
{
  int64_t res = 0;
  for (const auto &[x, t] : n_phi)
    res += t * (k / x);
  return res;
}

int main()
{
  int64_t n = sc.next_long();
  int64_t k = sc.next_long();
  int     c = sc.next_int();

  auto n_phi = fac_phi(n);

  int64_t sl = 1, sr = 1e18;
  while (sl < sr)
  {
    int64_t sm = sl + (sr - sl) / 2;
    if (count_coprime(n_phi, sm) >= k)
      sr = sm;
    else
      sl = sm + 1;
  }

  int cnt = 0;
  while (cnt < c)
  {
    if (cm::gcd(sl, n) == 1)
    {
      std::cout << sl << " ";
      cnt += 1;
    }
    sl += 1;
  }

  std::cout << std::endl;

  return 0;
}
