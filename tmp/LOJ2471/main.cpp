#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <map>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 10;

int a[N][N], b[N][N];
int n, m;

int solve(std::vector<int> v, int a[][N], int b[][N], int sum = 0)
{
  static std::map<std::vector<int>, int> mem;

  if (sum == n * m)
  {
    return 0;
  }
  else
  {
    auto it = mem.find(v);
    if (it != mem.end())
      return it->second;
    int ans = -0x3f3f3f3f;
    for (int i = 0; i < n; i++)
      if (v[i] != m && (i == 0 || v[i] + 1 <= v[i - 1]))
      {
        v[i] += 1;
        check_max(ans, a[i][v[i] - 1] - solve(v, b, a, sum + 1));
        v[i] -= 1;
      }
    mem.emplace(v, ans);
    return ans;
  }
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      a[i][j] = sc.next_int();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      b[i][j] = sc.next_int();

  std::vector<int> v(n, 0);
  std::cout << solve(v, a, b) << std::endl;

  return 0;
}
