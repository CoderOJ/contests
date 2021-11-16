#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
#include "/home/jack/cm/util.hpp"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

using int_t = cm::intm<1'000'000'007>;
CONSTRAINT(N, 1000005, 1005)
int_t mu[N], ans[N];

int main()
{
  mu[1] = 1;
  for (int i = 1; i < N; i++)
    for (int j = i + i; j < N; j += i)
      mu[j] -= mu[i];

  int n = sc.next_int();
  int_t k = sc.next_int();
  for (int i = 1; i <= n; i++)
  {
    auto kp = k.pow(i);
    for (int j = i; j <= n; j += i)
      ans[j] += mu[j / i] * kp;
  }

  int_t sum = 0;
  for (int i = 1; i <= n; i++)
    if (n % i == 0)
      sum += ans[i] / i;
  std::cout << sum << std::endl;

  return 0;
}
