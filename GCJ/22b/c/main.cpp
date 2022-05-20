#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstring>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 2005, 105)
CONSTRAINT(M, 3000005, 3005)

int cx[N], cy[N];
int px[N], py[N];
int jx, jy;
int n;

int64_t dis[N][N];

int64_t distance(int ax, int ay, int bx, int by)
{
  return (int64_t)(ax - bx) * (ax - bx) + (int64_t)(ay - by) * (ay - by);
}

struct edge_t
{
  struct edge_t *next;
  int            v, w;
};

struct edge_t *e[N], *ef[N];
struct edge_t  e_pool[M], *ep_top = e_pool;

struct edge_t *get_rev_edge(const struct edge_t *const p)
{
  return e_pool + ((long)(p - e_pool) ^ 1);
}

void clear_graph()
{
  memset(e, 0, sizeof(e));
  ep_top = e_pool;
}

void add_edge(int u, int v, int w)
{
  ep_top->v    = v;
  ep_top->w    = w;
  ep_top->next = e[u];
  e[u]         = ep_top++;
  ep_top->v    = u;
  ep_top->w    = 0;
  ep_top->next = e[v];
  e[v]         = ep_top++;
}

int dep[N];

bool bfs(int s, int t)
{
  memset(dep, -1, sizeof(dep));
  dep[s] = 0;
  static int que[N];
  int       *que_front = que, *que_back = que_front;
  *que_back++ = s;
  while (que_front != que_back)
  {
    int u = *que_front++;
    for (struct edge_t *i = e[u]; i; i = i->next)
      if (i->w)
      {
        int v = i->v;
        if (dep[v] == -1)
        {
          dep[v]      = dep[u] + 1;
          *que_back++ = v;
        }
      }
  }
  return dep[t] != -1;
}

int min(int a, int b)
{
  return a < b ? a : b;
}

int dfs(int u, int limit, int t)
{
  if (u == t)
    return limit;
  if (limit == 0)
    return 0;
  int remain = limit;
  for (struct edge_t **i = &ef[u]; *i; *i = (*i)->next)
  {
    int v = (*i)->v, w = (*i)->w;
    if (w == 0 || dep[v] != dep[u] + 1)
      continue;
    int v_limit = min(remain, w);
    int cur     = dfs(v, v_limit, t);
    remain -= cur;
    (*i)->w -= cur;
    get_rev_edge(*i)->w += cur;
    if (remain == 0)
      break;
  }
  return limit - remain;
}

int dinic(int s, int t)
{
  int ans = 0;
  while (bfs(s, t))
  {
    memcpy(ef, e, sizeof(ef));
    int cur = 0;
    while ((cur = dfs(s, 0x3f3f3f3f, t)))
      ans += cur;
  }
  return ans;
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    printf("Case #%d: ", i + 1);

    n = sc.next_int();
    for (int i = 0; i < n; i++)
    {
      cx[i] = sc.next_int();
      cy[i] = sc.next_int();
    }
    jx = sc.next_int();
    jy = sc.next_int();
    for (int i = 0; i < n; i++)
    {
      px[i] = sc.next_int();
      py[i] = sc.next_int();
    }

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        dis[i][j] = distance(cx[i], cy[i], px[j], py[j]);

    const int s = n * 2;
    const int t = n * 2 + 1;
    clear_graph();
    for (int i = 0; i < n; i++)
      add_edge(s, i, 1);
    for (int i = 0; i < n; i++)
      add_edge(n + i, t, 1);
    for (int i = 0; i < n; i++)
    {
      int64_t max_d = distance(cx[i], cy[i], jx, jy);
      for (int j = 0; j < n; j++)
        if (dis[i][j] <= max_d)
          add_edge(i, n + j, 1);
    }

    int match_cnt = dinic(s, t);
    if (match_cnt < n)
    {
      puts("IMPOSSIBLE");
    }
    else
    {
      puts("POSSIBLE");

      static int mt[N];
      for (int i = 0; i < n; i++)
      {
        for (edge_t *p = e[i]; p; p = p->next)
          if (p->w == 0)
            mt[p->v - n] = i;
      }

      static std::vector<int> vd[N];
      for (int i = 0; i < n; i++)
      {
        vd[i].resize(n);
        for (int j = 0; j < n; j++)
          vd[i][j] = j;
        std::sort(vd[i].begin(), vd[i].end(), [&](int x, int y) {
          return dis[i][x] > dis[i][y];
        });
      }

      static bool candy_used[N];
      std::fill(candy_used, candy_used + n, false);
      auto get_nearest = [&](int p) {
        while (candy_used[vd[p].back()])
          vd[p].pop_back();
        return vd[p].back();
      };

      std::set<int> undet;
      for (int i = 0; i < n; i++)
        undet.emplace(i);

      std::vector<std::pair<int, int>> ans;
      while (!undet.empty())
      {
        int s = *undet.begin();
        see(undet, s);

        static bool in_que[N];
        std::fill(in_que, in_que + n, false);
        while (!in_que[s])
        {
          in_que[s] = true;
          s         = mt[get_nearest(s)];
        }

        std::vector<int> cur_us{s};
        for (int t = mt[get_nearest(s)]; t != s; t = mt[get_nearest(t)])
          cur_us.push_back(t);
        see(cur_us);

        for (int u : cur_us)
          ans.emplace_back(u, get_nearest(u));
        for (int u : cur_us)
        {
          undet.erase(u);
          candy_used[get_nearest(u)] = true;
        }
      }

      for (const auto &[x, y] : ans)
        printf("%d %d\n", x + 1, y + 2);
    }
  }
  return 0;
}
