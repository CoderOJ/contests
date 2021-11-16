#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 1000005, 1005)
bool is_prime[N];
long long a[N], b[N];

int main()
{
  std::fill(is_prime + 2, is_prime + N, true);
  for (int i = 2; i * i < N; i++)
    if (is_prime[i])
      for (int j = i * i; j < N; j += i)
        is_prime[j] = false;

  int n = sc.next_int();
  for (int i = 0; i < n; i++)
    a[sc.next_int()]++;
  long long cnt_1 = a[1];

  for (int i = 2; i < N; i++)
    if (is_prime[i])
      for (int j = (N - 1) / i; j >= 1; j--)
        a[j] += a[j * i];
  for (int i = 1; i < N; i++)
    if (a[i])
      a[i] = a[i] * a[i];
  for (int i = 2; i < N; i++)
    if (is_prime[i])
      for (int j = 1; j * i < N; j++)
        a[j] -= a[j * i];

  std::cout << (a[1] - cnt_1) / 2 << std::endl;

  return 0;
}
