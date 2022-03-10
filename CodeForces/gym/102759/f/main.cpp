#include "/home/jack/cm/debug"
#include "/home/jack/cm/proof"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 500'005, 10)

using namespace cm::proof;

using vert = int_index<0, N>;

struct edge_t
{
  vert    v;
  int64_t w;
  int64_t c;
} __attribute__((aligned(32)));

index_array<vert, std::vector<edge_t *>> e;

__attribute__((aligned(64))) edge_t es[N * 4];

edge_t *get_rev_edge(edge_t *p)
{
  auto v = reinterpret_cast<uintptr_t>(p);
  v      = v ^ sizeof(edge_t);
  return reinterpret_cast<edge_t *>(v);
}

void add_edge(vert u, vert v, int64_t w, int64_t c)
{
  static edge_t *es_cur = es;

  es_cur->v = v;
  es_cur->w = w;
  es_cur->c = c;
  e[u].push_back(es_cur);
  es_cur++;

  es_cur->v = u;
  es_cur->w = -w;
  es_cur->c = 0;
  e[v].push_back(es_cur);
  es_cur++;
}

index_array<vert, int64_t> h;

const vert s(0);
const vert t(N - 1);

void init_h()
{
  for (int i = 0; i < N; i++)
  {
    vert u(i);
    for (edge_t *p : e[u])
      if (p->c > 0)
        check_min(h[p->v], h[u] + p->w);
  }
}

index_array<vert, int64_t>  dis;
index_array<vert, int64_t>  cap;
index_array<vert, edge_t *> pre;

void dijkstra()
{
  std::fill(dis.begin(), dis.end(), 0x3f3f3f3f3f3f3f3f);
  std::fill(cap.begin(), cap.end(), 0);
  std::fill(pre.begin(), pre.end(), nullptr);

  struct que_t
  {
    int64_t dis;
    vert    ver;

    que_t() = default;
    que_t(int64_t dis, vert ver) : dis(dis), ver(ver) {}

    bool operator<(const que_t rhs) const
    {
      return dis > rhs.dis;
    }
  };

  std::priority_queue<que_t> que;

  dis[s] = 0;
  cap[s] = 2;
  pre[s] = nullptr;
  que.emplace(0, vert(s));

  while (!que.empty())
  {
    const auto [du, u] = que.top();
    see(du, u);
    que.pop();
    if (du != dis[u])
      continue;
    for (edge_t *p : e[u])
      if (p->c > 0)
      {
        see(p->v, p->w);
        int64_t ew = p->w + h[u] - h[p->v];
        if (check_min(dis[p->v], du + ew))
        {
          pre[p->v] = p;
          cap[p->v] = std::min(cap[u], p->c);
          que.emplace(dis[p->v], p->v);
        }
      }
  }
}

int main()
{
  for (int i = 0; i + 1 < N; i++)
    add_edge(vert(i), vert(i + 1), 0, 2);

  int n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    vert    l(sc.next_int() - 1);
    vert    r(sc.next_int());
    int64_t w = sc.next_long();
    add_edge(l, r, -w, 1);
  }

  int64_t ans = 0;
  int64_t cnt = 0;

  init_h();
  while (cnt < 2)
  {
    dijkstra();
    if (cap[t] == 0)
      break;
    for (auto u : vert::all())
      h[u] += dis[u];

    int64_t cur_cap = std::min(2 - cnt, cap[t]);
    ans += cur_cap * h[t];
    cnt += cur_cap;

    vert u = t;
    while (u != s)
    {
      edge_t *pa = pre[u];
      edge_t *pb = get_rev_edge(pa);
      pa->c -= cur_cap;
      pb->c += cur_cap;
      u = pb->v;
    }
  }

  std::cout << -ans << std::endl;

  return 0;
}
