#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100005;

std::vector<std::pair<int, int>> e_soft, e_hard;
int                              n, q;
long long                        m;

struct dsu_t
{
  int p[N];
  dsu_t()
  {
    for (int i = 0; i < N; i++)
      p[i] = i;
  }

  int get(int u)
  {
    return u == p[u] ? u : p[u] = get(p[u]);
  }
  void link(int u, int v)
  {
    p[get(u)] = get(v);
  }
};

dsu_t dsu_soft;

int main()
{
  n = sc.next_int();
  m = sc.next_long();
  q = sc.next_int();
  for (int i = 0; i < q; i++)
  {
    int u    = sc.next_int();
    int v    = sc.next_int();
    int type = sc.next_int();
    (type ? e_hard : e_soft).emplace_back(u, v);
  }

  for (const auto &[u, v] : e_soft)
    dsu_soft.link(u, v);
  for (const auto &[u, v] : e_hard)
    if (dsu_soft.get(u) == dsu_soft.get(v))
    {
      puts("No");
      return 0;
    }

  int comp_cnt = 0;
  for (int i = 0; i < n; i++)
    comp_cnt += dsu_soft.get(i) == i;

  if ((comp_cnt <= 2 || m == n - 1) && !e_hard.empty())
  {
    puts("No");
    return 0;
  }
  if (1ll * comp_cnt * (comp_cnt - 1) / 2 < (m - (n - comp_cnt)))
  {
    puts("No");
    return 0;
  }

  puts("Yes");
  return 0;
}
