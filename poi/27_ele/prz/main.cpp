#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstdint>
#include <limits>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 300'005, 3005)

struct relay_t
{
  int64_t x;
  int64_t y;
  int64_t w;
};

struct query_t
{
  int64_t x;
  int64_t y;
  int64_t ans = std::numeric_limits<int64_t>::min() / 2;
};

relay_t r[N];
query_t q[N];

std::vector<int64_t> vals;

int n, m;

void dis()
{
  vals.reserve((n + m) * 2 + 10);
  vals.emplace_back(std::numeric_limits<int64_t>::min() / 2);
  for (int i = 0; i < n; i++)
  {
    vals.emplace_back(r[i].x);
    vals.emplace_back(r[i].y);
  }
  for (int i = 0; i < m; i++)
  {
    vals.emplace_back(q[i].x);
    vals.emplace_back(q[i].y);
  }

  std::sort(vals.begin(), vals.end());

  auto vals = ::vals;

  for (int i = 0; i < n; i++)
  {
    auto x_it = std::lower_bound(vals.begin(), vals.end(), r[i].x);
    r[i].x    = x_it - vals.begin();
    *x_it     = *(x_it - 1);
    auto y_it = std::lower_bound(vals.begin(), vals.end(), r[i].y);
    r[i].y    = y_it - vals.begin();
    *y_it     = *(y_it - 1);
  }
  for (int i = 0; i < m; i++)
  {
    auto x_it = std::lower_bound(vals.begin(), vals.end(), q[i].x);
    q[i].x    = x_it - vals.begin();
    *x_it     = *(x_it - 1);
    auto y_it = std::lower_bound(vals.begin(), vals.end(), q[i].y);
    q[i].y    = y_it - vals.begin();
    *y_it     = *(y_it - 1);
  }

  see(::vals);
}

struct node_t : public cm::segment_tree_node_base<false>
{
  using cm::segment_tree_node_base<false>::segment_tree_node_base;

  int64_t max = std::numeric_limits<int64_t>::min() / 2;

  node_t() = default;
  node_t(int64_t max) : max(max) {}
  node_t(const node_t &lhs, const node_t &rhs) : max(std::max(lhs.max, rhs.max))
  {
  }

  void assign(node_t rhs)
  {
    *this = rhs;
  }
};

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int64_t x = sc.next_long();
    int64_t y = sc.next_long();
    int64_t w = sc.next_long();
    r[i].x    = x + y;
    r[i].y    = x - y;
    r[i].w    = w * 2;
  }
  for (int i = 0; i < m; i++)
  {
    int64_t x = sc.next_long();
    int64_t y = sc.next_long();
    q[i].x    = x + y;
    q[i].y    = x - y;
  }

  dis();

  std::sort(r, r + n, [](const relay_t &lhs, const relay_t &rhs) {
    return lhs.x < rhs.x;
  });

  std::vector<query_t *> qs;
  qs.reserve(m);
  for (int i = 0; i < m; i++)
    qs.emplace_back(&q[i]);
  std::sort(qs.begin(), qs.end(), [](const query_t *lhs, const query_t *rhs) {
    return lhs->x < rhs->x;
  });

  using sgt_t = cm::segment_tree<node_t>;
  sgt_t slu((int)vals.size());
  sgt_t sld((int)vals.size());
  sgt_t sru((int)vals.size());
  sgt_t srd((int)vals.size());

  for (int i = 0; i < n; i++)
  {
    sru.modify(r[i].y,
               r[i].y + 1,
               &node_t::assign,
               node_t(r[i].w - vals[r[i].x] - vals[r[i].y]));
    srd.modify(r[i].y,
               r[i].y + 1,
               &node_t::assign,
               node_t(r[i].w - vals[r[i].x] + vals[r[i].y]));
  }

  auto r_it = 0;
  for (query_t *q : qs)
  {
    while (r_it != n && r[r_it].x < q->x)
    {
      sru.modify(r[r_it].y, r[r_it].y + 1, &node_t::assign, node_t());
      srd.modify(r[r_it].y, r[r_it].y + 1, &node_t::assign, node_t());
      slu.modify(r[r_it].y,
                 r[r_it].y + 1,
                 &node_t::assign,
                 node_t(r[r_it].w + vals[r[r_it].x] - vals[r[r_it].y]));
      sld.modify(r[r_it].y,
                 r[r_it].y + 1,
                 &node_t::assign,
                 node_t(r[r_it].w + vals[r[r_it].x] + vals[r[r_it].y]));
      r_it += 1;
    }

    // clang-format off
    check_max(q->ans, slu.query(q->y, vals.size()).max - vals[q->x] + vals[q->y]);
    check_max(q->ans, sld.query(0, q->y).max - vals[q->x] - vals[q->y]);
    check_max(q->ans, sru.query(q->y, vals.size()).max + vals[q->x] + vals[q->y]);
    check_max(q->ans, srd.query(0, q->y).max + vals[q->x] - vals[q->y]);
    // clang-format on   
  }
  
  for (int i = 0; i < m; i++)
    printf("%lld\n", std::max<long long>(0, q[i].ans / 2));

  return 0;
}