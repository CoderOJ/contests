#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <random>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

int main()
{
  FILE *input  = fopen("elegant.in", "r");
  FILE *output = fopen("elegant.out", "w");

  cm::scanner<cm::optimal_reader> sc(input);

  constexpr int primes0[] = {2, 3, 5, 7, 11};
  constexpr int primes1[] = {13, 17, 19, 23, 29};
  constexpr int primes2[] = {31, 37, 41, 43, 47};

  int n = sc.next_int();

  auto gen_perm = [](int n) {
    static std::mt19937 rand(20050612);
    std::vector<int>    a(n);
    for (int i = 0; i < n; i++)
      a[i] = i;
    std::shuffle(a.begin(), a.end(), rand);
    return a;
  };

  auto gen_square = [&]() {
    std::vector<long long> res;

    auto perm0 = gen_perm(n);
    auto perm1 = gen_perm(n);
    auto perm2 = gen_perm(n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
        long long x = 1;
        for (int k = 0; k < 5; k++)
          if (((i + perm0[j]) % n) & (1 << k))
            x *= primes0[k];
        for (int k = 0; k < 5; k++)
          if (((i + perm1[j]) % n) & (1 << k))
            x *= primes1[k];
        for (int k = 0; k < 5; k++)
          if (((i + perm2[j]) % n) & (1 << k))
            x *= primes2[k];
        res.push_back(x);
      }
    return res;
  };

  while (true)
  {
    auto a = gen_square();
    auto b = a;
    std::sort(b.begin(), b.end());
    see(b);
    if (std::unique(b.begin(), b.end()) == b.end())
    {
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          fprintf(output, "%lld%c", a[i * n + j], " \n"[j == n - 1]);
      break;
    }
  }

  return 0;
}
