#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 1000005, 1005)
bool is_prime[N];
int cnt[N];

int main()
{
  std::fill(is_prime + 2, is_prime + N, true);
  for (int i = 2; i < N; i++)
    if (is_prime[i])
      for (int j = i * 2; j < N; j += i)
        is_prime[j] = false;

  int n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int a = sc.next_int();
    cnt[a]++;
  }

  for (int i = 2; i < N; i++)
    if (is_prime[i])
      for (int j = (N-1) / i; j >= 1; j--)
        cnt[j] += cnt[j * i];

  int ans = 0;
  for (int i = 1; i < N; i++)
    if (cnt[i] > 1)
      ans = i;

  std::cout << ans << std::endl;

  return 0;
}
