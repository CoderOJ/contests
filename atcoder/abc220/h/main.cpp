#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <unordered_map>

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 40;
long long e[N];
int get_bit(long long x, int v)
{
  return (x >> v) & 1;
}

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();

  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u] |= 1ll << v;
  }

  std::unordered_map<long long, long long> dp[N + 5][2];
  dp[0][0][0] = 1;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < 2; j++)
      for (auto &[x, v] : dp[i][j])
      {
        long long bit = get_bit(x, i);
        dp[i + 1][j ^ bit][x ^ (bit << i) ^ e[i]] += v;
        dp[i + 1][j][x ^ (bit << i)] += v;
      }

  std::cout << dp[n][m & 1][0] << std::endl;

  return 0;
}
