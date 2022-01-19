#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
constexpr int N   = 5005;
using int_t       = cm::intm<MOD>;

std::vector<int> e[N];

int n;

int_t cnt[N];

std::vector<int_t> dfs(int u, int f)
{
  std::vector<int_t> pos{0, 1};
  for (int v : e[u])
    if (v != f)
    {
      auto dpv = dfs(v, u);

      std::vector<int_t> cur(pos.size() + dpv.size() - 1);
      for (size_t i = 0; i < pos.size(); i++)
        for (size_t j = 0; j < dpv.size(); j++)
        {
          cur[i + j] += pos[i] * dpv[j];
          cur[i] -= pos[i] * dpv[j] * cnt[j];
        }

      pos = std::move(cur);
    }
  return pos;
}

int main()
{
  n = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }

  cnt[0] = 1;
  for (int i = 2; i <= n; i++)
    cnt[i] = cnt[i - 2] * (i - 1);

  auto  res = dfs(1, 0);
  int_t ans = 0;
  for (size_t i = 0; i < res.size(); i++)
    ans += res[i] * cnt[i];

  std::cout << ans << std::endl;

  return 0;
}
