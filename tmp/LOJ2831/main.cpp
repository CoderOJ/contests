#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cinttypes>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int64_t calc_inverse(std::vector<std::pair<int, int>>::iterator begin,
                     std::vector<std::pair<int, int>>::iterator end)
{
  if (std::next(begin) == end)
    return 0;
  else
  {
    auto    mid = begin + std::distance(begin, end) / 2;
    int64_t res = calc_inverse(begin, mid) + calc_inverse(mid, end);

    auto r_it  = mid;
    int  r_sum = 0;
    for (auto i = begin; i != mid; i++)
    {
      while (r_it != end && r_it->first < i->first)
      {
        r_sum += r_it->second;
        r_it++;
      }
      res += (int64_t)r_sum * i->second;
    }

    std::inplace_merge(begin, mid, end);
    return res;
  }
}

struct node_t
{
  node_t *f{};
  node_t *s[2]{};
  int     len = 1;
  int     val;

  bool is_root() const
  {
    return f == nullptr || (f->s[0] != this && f->s[1] != this);
  }

  bool get_son() const
  {
    return f->s[1] == this;
  }

  void push_up()
  {
    len = 1 + (s[0] ? s[0]->len : 0) + (s[1] ? s[1]->len : 0);
  }

  void push_down()
  {
    if (s[0])
      s[0]->val = val;
    if (s[1])
      s[1]->val = val;
  }

  void push_chain()
  {
    if (!is_root())
      f->push_chain();
    push_down();
  }

  void rotate()
  {
    bool    ss = get_son();
    node_t *uu = this, *ff = uu->f, *aa = ff->f;
    if (!ff->is_root())
      aa->s[ff->get_son()] = uu;
    ff->f      = uu;
    ff->s[ss]  = uu->s[!ss];
    uu->f      = aa;
    uu->s[!ss] = ff;
    if (ff->s[ss])
      ff->s[ss]->f = ff;
    ff->push_up();
    uu->push_up();
  }

  void splay()
  {
    push_chain();
    while (!is_root())
    {
      if (f->is_root())
      {
        rotate();
        break;
      }
      else
      {
        if (is_root() == f->is_root())
          f->rotate();
        else
          rotate();
        rotate();
      }
    }
  }

  std::vector<std::pair<int, int>> access(int val)
  {
    std::vector<std::pair<int, int>> res;

    node_t *uu = this, *ss = nullptr;
    while (uu)
    {
      uu->splay();
      uu->s[1] = nullptr;
      uu->push_up();
      res.emplace_back(uu->val, uu->len);
      uu->s[1] = ss;
      uu->push_up();
      uu->val = val;
      ss = uu;
      uu = uu->f;
    }

    std::reverse(res.begin(), res.end());
    return res;
  }
};

CONSTRAINT(N, 100005, 105)

node_t p[N];

int main()
{
  int n = sc.next_int();
  for (int i = 1; i <= n; i++)
    p[i].val = sc.next_int();
  for (int i = 0; i < n - 1; i++)
  {
    int  u = sc.next_int();
    int  v = sc.next_int();
    auto r = p[u].access(p[v].val);
    printf("%" SCNi64 "\n", calc_inverse(r.begin(), r.end()));
    p[v].f = &p[u];
  }
  return 0;
}
