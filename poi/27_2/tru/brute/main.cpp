#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int64_t n;

constexpr int primes[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37,
                          41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83};

using ans_t = std::tuple<int, int64_t, int64_t>;

ans_t solve(const int *pr,
            int64_t    p,
            int64_t    q,
            int        pa,
            int        qa,
            int        ga,
            int        l_max,
            int        l_min)
{
  ans_t ans{pa + qa - ga, p, q};

  int64_t cp = p;
  for (int i = 0; i <= l_max && cp <= n; i++)
  {
    int64_t cq = q;
    for (int j = 0; j <= l_max && cq <= n; j++)
    {
      if (i > 0 || j > 0)
        if (std::min(i, j) <= l_min)
          check_max(ans,
                    solve(pr + 1,
                          cp,
                          cq,
                          pa * (i + 1),
                          qa * (j + 1),
                          ga * std::min(i + 1, j + 1),
                          std::min(std::min(i, j) + 1, std::max(i, j)),
                          std::min(i, j)));
      cq *= *pr;
    }
    cp *= *pr;
  }
  return ans;
}

int main()
{
  n = sc.next_long();

  while (n >= 5000)
  {
    std::cerr << n << std::endl;
    const auto [a, p, q] = solve(primes, 1, 1, 1, 1, 1, 12, 12);
    std::cout << a << " " << p << " " << q << std::endl;
    n = std::max(p, q) - 1;
  }

  return 0;
}
