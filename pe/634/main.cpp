#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cmath>
#include <cstring>

cm::scanner<cm::optimal_reader> sc(stdin);

#define int unsigned long long

int get_sqrt3(int x)
{
  for (int i = 1; ; i++)
    if (i * i * i > x)
      return i - 1;
}

constexpr size_t N = 3000005;
constexpr int M = 3003;
char *phi;
bool isprime[M];

AT_INIT({
  phi = new char[N];
  memset(phi, 0, N);
  phi[1] = 1;
  for (int i = 1; i < N; i++)
    for (int j = i + i; j < N; j += i)
      phi[j] -= phi[i];
  
  memset(isprime, 1, sizeof(isprime));
  isprime[1] = false;
  for (int i = 2; i < M; i++) if (isprime[i])
    for (int j = i * i; j < M; j += i)
      isprime[j] = false;
});
AT_EXIT({ delete[] phi; });

int count_without_sf(int n)
{
  int result = 0;
  for (int i = 2; i * i * i <= n; i++)
    if (phi[i] != 0)
      result++;
  return result;
}

int count_without_sf2(int n)
{
  int result = 0;
  for (int i = 2; i * i * i * i * i * i <= n; i++)
    result -= phi[i];
  return result;
}

int solve(int n)
{
  int result = 0;
  for (int i = 2; i * i <= n; i++)
  {
    if ((i & (i - 1)) == 0)
      printf("%llu\n", i);
    result += count_without_sf(n / (i * i));
  }
  for (int i = 1; i * i <= n; i++)
  {
    if ((i & (i - 1)) == 0)
      printf("%llu\n", i);
    result += count_without_sf2(n / (i * i));
  }
  for (int i = 2; i * i * i * i * i * i <= n; i++)
  {
    if ((i & (i - 1)) == 0)
      printf("%llu\n", i);
    result -= isprime[i];
  }
  return result;
}

signed main()
{
  int n = sc.next_long();

  printf("%llu %llu\n", n, solve(n));

  return 0;
}

