#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 2000005;

struct opt_t
{
  int type = 0;
  int id   = 0;
  int x[2] = {};
  opt_t()  = default;
};

int qid[N];
int ans[N][2];

struct
{
  std::vector<int> eg[N];

  int p[N];
  int w[N];

  std::set<std::pair<int, int>> th;

  void insert(std::pair<int, int> v)
  {
    p[v.first] = v.first;
    w[v.first] = v.second;
    eg[v.first].clear();
    eg[v.first].reserve(0);
    th.insert(std::make_pair(w[v.first], v.first));
  }

  void init()
  {
    th.clear();
  }

  int get(int a)
  {
    if (p[a] == a)
      return a;
    else
      return p[a] = get(p[a]);
  }

  void uni(int u, int v)
  {
    u = get(u);
    v = get(v);
    if (u != v)
    {
      eg[u].push_back(v);
      th.erase(std::make_pair(w[v], v));
      p[v] = p[u];
    }
  }

  void update_w(int x, int _w)
  {
    x = get(x);
    th.erase(std::make_pair(w[x], x));
    w[x] = _w;
    th.insert(std::make_pair(w[x], x));
  }

  int get_w(int x)
  {
    return w[get(x)];
  }

  int cnt = 0;
  int gg[N];

  void dfs(int a)
  {
    gg[cnt++] = a;
    for (auto v : eg[a])
      dfs(v);
  }

  std::vector<int> gt(int a)
  {
    cnt = 0;
    dfs(a);
    std::vector<int> fn(cnt);
    for (int i = 0; i < cnt; i++)
      fn[i] = gg[i];
    return fn;
  }
} dsu[2];

int n;
int state[N];

void solve(int l, int r, std::vector<opt_t> &qs)
{
  if (l > r)
    return;
  if (qs.size() == 0)
    return;

  for (auto &tp : dsu)
    tp.init();

  for (auto v : qs)
    if (v.type == 2)
      state[v.id] = -1;

  int mid  = (l + r) >> 1;
  int u[2] = {mid, n - mid};

  std::vector<opt_t> cu[2];

  for (auto v : qs)
  {
    if (v.type == 2)
    {
      if (v.x[0] > u[0] || v.x[1] > u[1])
      {
        int tp = 1;
        if (v.x[1] > u[1])
          tp = 0;
        cu[tp].push_back(v);
        state[v.id] = tp;
      }
      else
      {
        for (int i = 0; i < 2; i++)
          dsu[i].insert(std::make_pair(v.id, v.x[i]));
      }
    }
    else if (v.type == 3)
    {
      int cpl = v.id, cid = qid[cpl];

      if (state[cid] == -1)
      {
        for (int i = 0; i < 2; i++)
          ans[cpl][i] = dsu[i].get_w(cid);
      }
      else
        cu[state[cid]].push_back(v);
    }
    else
    {
      int tp = v.type;
      int vv = v.x[tp];

      if (v.x[0] < u[0])
        cu[0].push_back(v);
      else if (v.x[0] > u[0])
        cu[1].push_back(v);

      if (vv <= u[tp])
      {
        std::vector<std::pair<int, int>> cur;
        auto                             fr = dsu[tp].th.begin();

        while (fr != dsu[tp].th.end())
        {
          if (fr->first >= vv)
            break;
          cur.push_back(*fr);
          fr++;
        }

        for (size_t i = 1; i < cur.size(); i++)
          dsu[tp].uni(cur[0].second, cur[i].second);

        if (cur.size())
          dsu[tp].update_w(cur[0].second, vv);

        cur.clear();
        cur.reserve(0);
      }
      else
      {
        while (dsu[tp ^ 1].th.size())
        {
          auto g = dsu[tp ^ 1].th.begin();

          if ((*g).first > n - vv)
            break;

          std::vector<int> tt = dsu[tp ^ 1].gt((*g).second);

          for (auto v : tt)
            if (state[v] == -1)
            {
              state[v] = (tp ^ 1);
              opt_t cur;
              cur.type = 2, cur.id = v;
              cur.x[tp] = vv, cur.x[tp ^ 1] = dsu[tp ^ 1].get_w(v);
              cu[tp ^ 1].push_back(cur);
            }

          dsu[tp ^ 1].th.erase(g);
        }
      }
    }
  }

  qs.clear();
  qs.reserve(0);

  solve(l, mid - 1, cu[0]);
  solve(mid + 1, r, cu[1]);

  for (auto &i : cu)
  {
    i.clear();
    i.reserve(0);
  }
}

int main()
{
  n     = sc.next_int();
  int m = sc.next_int();
  int q = sc.next_int();

  int cur_id = 0;
  memset(ans, -1, sizeof(ans));

  std::vector<opt_t> ops;
  for (int i = 1; i <= m; i++)
  {
    opt_t cur;
    cur.x[0] = sc.next_int();
    cur.x[1] = sc.next_int();
    cur.type = 2, cur.id = ++cur_id;
    ops.push_back(cur);
  }

  for (int i = 1; i <= q; i++)
  {
    int   op = sc.next_int() - 1;
    opt_t cur;

    if (op == 0)
    {
      int x    = sc.next_int();
      cur.type = 3;
      qid[i]   = x;
      cur.id   = i;
    }
    else if (op == 1 || op == 2)
    {
      int x = sc.next_int();
      op -= 1;
      cur.type  = op;
      cur.x[op] = n - x, cur.x[op ^ 1] = x;
    }
    else
    {
      cur.type = 2;
      cur.id   = ++cur_id;
      cur.x[0] = sc.next_int();
      cur.x[1] = sc.next_int();
    }

    ops.push_back(cur);
  }

  solve(0, n, ops);

  for (int i = 1; i <= q; i++)
    if (ans[i][0] != -1)
      printf("%d %d\n", ans[i][0], ans[i][1]);

  return 0;
}
