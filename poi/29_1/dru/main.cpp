#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstring>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 2005;

char map[N][N];
int  cnt[128];
int  n, m;

char pat[N];
bool filled[N][N];

bool greedy_fill(int pat_len)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (!filled[i][j])
      {
        if (std::equal(pat, pat + pat_len, map[i] + j) &&
            std::none_of(
                &filled[i][j], &filled[i][j] + pat_len, [](bool x) { return x; }))
        {
          for (int k = j; k < j + pat_len; k++)
            filled[i][k] = true;
        }
        else
        {
          for (int k = i; k < i + pat_len; k++)
            if (filled[k][j] || map[k][j] != pat[k - i])
              return false;
            else
              filled[k][j] = true;
        }
      }
  return true;
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < n; i++)
    sc.next_token(map[i]);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cnt[(int)map[i][j]] += 1;

  std::set<int> ans;

  if (std::any_of(
          std::begin(cnt), std::end(cnt), [](int x) { return x == n * m; }))
  {
    for (int i = 1; i <= std::max(n, m); i++)
      if (n % i == 0 || m % i == 0)
        ans.emplace(i);
  }
  else
  {
    for (int i = 1; i <= m; i++)
      if (n % i == 0 || m % i == 0)
      {
        memset(filled, false, sizeof(filled));
        for (int k = 0; k < i; k++)
        {
          pat[k]       = map[0][k];
          filled[0][k] = true;
        }
        if (greedy_fill(i))
          ans.emplace(i);
      }
    for (int i = 1; i <= n; i++)
      if (n % i == 0 || m % i == 0)
      {
        memset(filled, false, sizeof(filled));
        for (int k = 0; k < i; k++)
        {
          pat[k]       = map[k][0];
          filled[k][0] = true;
        }
        if (greedy_fill(i))
          ans.emplace(i);
      }
  }

  std::cout << ans.size() << std::endl;
  for (int x : ans)
    std::cout << x << " ";
  std::cout << std::endl;

  return 0;
}
