#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 300005;
std::vector<std::pair<int,int>> e[N];
int n, m;

bool vis[N];
std::vector<int> ans;
void dfs(int u)
{
  static std::vector<std::pair<int,int>>::iterator e_cur[N];
  static cm::once_t e_init;
  if (e_init())
  {
    for (int i = 1; i <= n; i++)
      e_cur[i] = e[i].begin();
  }

  for (; e_cur[u] != e[u].end(); )
  {
    const auto [v, id] = *e_cur[u];
    e_cur[u]++;
    if (!vis[id])
    {
      vis[id] = true;
      dfs(v);
    }
  }
  ans.push_back(u);
}

int main()
{
  n = sc.next_int(); m = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int(), v = sc.next_int();
    e[u].emplace_back(v, i); e[v].emplace_back(u, i);
  }

  std::vector<int> odd_id;
  for (int i = 1; i <= n; i++)
    if (e[i].size() % 2 == 1)
      odd_id.push_back(i);


  int eid = m;
  for (size_t i = 0; i < odd_id.size(); i += 2)
  {
    int u = odd_id[i], v = odd_id[i + 1];
    e[u].emplace_back(v, eid); e[v].emplace_back(u, eid); eid++;
  }

  if (eid % 2 == 1)
  {
    e[1].emplace_back(1, eid); e[1].emplace_back(1, eid); eid++;
  } 

  dfs(1);

  std::cout << ans.size() - 1 << std::endl;    
  for (size_t i = 0; i + 1 < ans.size(); i++)
  {
    if (i % 2 == 0) std::cout << ans[i] << " " << ans[i + 1] << std::endl;
    else std::cout << ans[i + 1] << " " << ans[i] << std::endl;
  }
  return 0;
}

