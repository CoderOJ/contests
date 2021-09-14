#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cstring>
#include <queue>
#include <string>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);
constexpr int N = 100005;
constexpr int MOD = 1000000007;
using int_t = cm::intm<MOD>;
std::basic_string<int> v[3][N + 1];

int_t inv[N];
AT_INIT({
  inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++)
    inv[i] = inv[MOD % i] * (MOD - MOD / i); });

int a[N], k, u;

void input(int id)
{
  int n = sc.next_int();
  int m = sc.next_int();

  std::vector<std::basic_string<int>> g(n + 1);
  while (m--)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    g[u] += v, g[v] += u;
  }

  std::basic_string<int> odd(n + 1, N);
  std::basic_string<int> even(n + 1, N);

  std::queue<int> q;
  q.push(1), even[1] = 0;
  while (q.size())
  {
    int u = q.front(); q.pop();
    if (u > n)
    {
      u -= n;
      for (int v : g[u])
        if (even[v] == N)
        {
          even[v] = odd[u] + 1;
          q.push(v);
        }
    }
    else
    {
      for (int v : g[u])
        if (odd[v] == N)
        {
          odd[v] = even[u] + 1;
          q.push(v + n);
        }
    }
  }

  for (int u = 1; u <= n; u++)
  {
    see(u, odd[u], even[u]);
    v[0][odd[u]] += id;
    v[1][even[u]] += id;
    v[2][std::max(odd[u], even[u])] += id;
  }
}

int_t get(std::basic_string<int> *v)
{
  int filled_cnt = 0;
  int_t s = 0, t = 1;
  memset(a, 0, sizeof(a));
  for (int i = 0; i < N; ++i)
    for (int j : v[i])
    { 
      if (a[j]) t *= inv[a[j]];
      else filled_cnt++;

      if (filled_cnt == k) 
        s += t * i;
      t = t * (++a[j]);
    }
  return s;
}

int main()
{
  k = sc.next_int();
  for (int i = 1; i <= k; i++) input(i);
  std::cout << get(v[0]) + get(v[1]) - get(v[2]) << std::endl;
  return 0;
}
