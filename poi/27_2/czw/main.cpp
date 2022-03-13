#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
using int_t       = cm::intm<MOD>;

CONSTRAINT(N, 1'000'005, 1'005)

struct node_t
{
  enum type_t
  {
    filled,
    subtree,
  };

  type_t  type;
  int     n;
  node_t *s[2][2] = {};
  node_t *p       = nullptr;

  std::basic_string<int> ns;

  node_t() = default;
  node_t(type_t type, int n) : type(type), n(n) {}

  node_t *get_p()
  {
    return p == this ? this : p = p->get_p();
  }

  // clang-format off
  template <int px1, int py1, int px2, int py2, int qx1, int qy1, int qx2, int qy2>
  static void join(node_t *p, node_t *q)
  {
    if (p == nullptr || q == nullptr)
      return;
    else if (p->type == filled && q->type == filled)
    {
      node_t *pp = p->get_p();
      node_t *qq = q->get_p();
      pp->p      = qq;
    }
    else if (p->type == filled)
    {
      join<px1, py1, px2, py2, qx1, qy1, qx2, qy2>(p, q->s[qx1][qy1]);
      join<px1, py1, px2, py2, qx1, qy1, qx2, qy2>(p, q->s[qx2][qy2]);
    }
    else if (q->type == filled)
    {
      join<px1, py1, px2, py2, qx1, qy1, qx2, qy2>(p->s[px1][py1], q);
      join<px1, py1, px2, py2, qx1, qy1, qx2, qy2>(p->s[px2][py2], q);
    }
    else
    {
      join<px1, py1, px2, py2, qx1, qy1, qx2, qy2>(p->s[px1][py1], q->s[qx1][qy1]);
      join<px1, py1, px2, py2, qx1, qy1, qx2, qy2>(p->s[px2][py2], q->s[qx2][qy2]);
    }
  }
  // clang-format on

  void join()
  {
    join<0, 1, 1, 1, 0, 0, 1, 0>(s[0][0], s[0][1]);
    join<0, 1, 1, 1, 0, 0, 1, 0>(s[1][0], s[1][1]);
    join<1, 0, 1, 1, 0, 0, 0, 1>(s[0][0], s[1][0]);
    join<1, 0, 1, 1, 0, 0, 0, 1>(s[0][1], s[1][1]);
  }
};

node_t  ps[N];
node_t *p = ps;
node_t *new_node(node_t v)
{
  *p   = v;
  p->p = p;
  return p++;
}

int   n;
char  a[N];
char *a_id = a;

node_t *build(int depth)
{
  char c = *a_id++;
  if (c == '0')
    return nullptr;
  else if (c == '1')
    return new_node(node_t(node_t::filled, depth * 2));
  else
  {
    node_t *res  = new_node(node_t(node_t::subtree, depth));
    res->s[0][0] = build(depth - 1);
    res->s[0][1] = build(depth - 1);
    res->s[1][0] = build(depth - 1);
    res->s[1][1] = build(depth - 1);
    res->join();
    return res;
  }
}

void carry(std::basic_string<int> &a)
{
  std::sort(a.begin(), a.end(), std::greater<int>());
  std::basic_string<int> b;

  int cur_v = 0, cur_i = 0;
  while (!a.empty())
  {
    if (cur_v == 0)
      cur_i = a.back();
    if (a.back() == cur_i)
    {
      a.pop_back();
      cur_v += 1;
    }
    else
    {
      if (cur_v & 1)
        b.push_back(cur_i);
      cur_i += 1;
      cur_v >>= 1;
    }
  }
  while (cur_v > 0)
  {
    if (cur_v & 1)
      b.push_back(cur_i);
    cur_i += 1;
    cur_v >>= 1;
  }

  std::reverse(b.begin(), b.end());
  a = std::move(b);
}

int main()
{
  n = sc.next_int();
  sc.next_token(a);
  build(n);

  for (node_t *i = ps; i < p; i++)
    i->get_p()->ns.push_back(i->n);

  int                    cnt = 0;
  std::basic_string<int> ans;
  for (node_t *i = ps; i < p; i++)
    if (i->type == node_t::filled && i->p == i)
    {
      cnt += 1;
      carry(i->ns);
      if (ans.empty())
        ans = i->ns;
      else
        ans = std::max(ans, i->ns);
    }

  int_t ans_v = 0;
  for (int x : ans)
    ans_v += int_t(2).pow(x);

  std::cout << cnt << std::endl;
  std::cout << ans_v << std::endl;

  return 0;
}
