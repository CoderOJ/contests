#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
#include <ext/pb_ds/priority_queue.hpp>
#include <limits>
#include <map>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 60'005;

std::vector<std::tuple<int, int, int64_t, int64_t, int64_t>> e[N];
std::map<std::pair<int, int>, int64_t>                       el;
std::vector<std::pair<int, int>>                             lines[N];

int n, m, s, k, t;

int64_t dis[N][105];

using vertex_t = std::tuple<int, int>;

struct que_vert_t
{
  int64_t  dis;
  vertex_t ver;

  bool operator<(const que_vert_t &rhs) const
  {
    return dis > rhs.dis;
  }

  void swap(que_vert_t &rhs)
  {
    std::swap(*this, rhs);
  }
};

using namespace __gnu_pbds;

priority_queue<que_vert_t, std::less<que_vert_t>, pairing_heap_tag> que;

decltype(que)::point_iterator it[N][105];

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  s = sc.next_int();
  k = sc.next_int();
  t = sc.next_int();

  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    int w = sc.next_int();
    el.insert({{u, v}, w});
    el.insert({{v, u}, w});
  }

  int vertex_id = n + 1;
  for (int id = 0; id < s; id++)
  {
    int     nn = sc.next_int();
    int64_t y  = sc.next_int();
    int64_t x  = sc.next_int();

    lines[id].resize(nn);
    for (int i = 0; i < nn; i++)
    {
      int u        = sc.next_int();
      lines[id][i] = {u, vertex_id};
      e[u].push_back({vertex_id, 1, 1, 0, 0});
      e[vertex_id].push_back({u, 0, 1, 0, 0});
      vertex_id += 1;
    }

    for (int i = 1; i < nn; i++)
    {
      int     u  = lines[id][i - 1].second;
      int     v  = lines[id][i].second;
      int64_t el = ::el[{lines[id][i - 1].first, lines[id][i].first}];
      e[u].push_back({v, 0, x, y, el});
      y += el;
    }
  }

  memset(dis, 0x3f, sizeof(dis));

  for (int i = 0; i < s; i++)
    for (const auto &[uu, ui] : lines[i])
      if (uu == 1)
      {
        dis[ui][0] = t;
        que.push({t, {ui, 0}});
      }

  while (!que.empty())
  {
    // printf("%zu\n", que.size());
    const auto [ud, _u] = que.top();
    const auto [ui, ut] = _u;
    // see(u, ui, ul, ut, ud);
    que.pop();

    if (ui == n)
      break;

    if (ud > dis[ui][ut])
      continue;

    for (const auto &[vi, et, ex, ey, el] : e[ui])
    {
      int vt = ut + et;
      if (vt > k)
        continue;
      int64_t vd = std::max((ud - ey + ex - 1) / ex * ex + ey, ey) + el;
      if (vd < dis[vi][vt])
      {
        if (dis[vi][vt] == 0x3f3f3f3f3f3f3f3f)
          it[vi][vt] = que.push({vd, {vi, vt}});
        else
          que.modify(it[vi][vt], {vd, {vi, vt}});
        dis[vi][vt] = vd;
      }
    }
  }

  int64_t ans = 0x3f3f3f3f3f3f3f3f;

  for (int i = 0; i < s; i++)
    for (const auto &[uu, ui] : lines[i])
      if (uu == n)
        for (int t = 0; t <= k; t++)
          check_min(ans, dis[ui][t]);

  if (ans >= 0x3f3f3f3f3f3f3f3f)
    std::cout << "NIE" << std::endl;
  else
    std::cout << ans << std::endl;

  return 0;
}
