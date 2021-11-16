#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t
{
  node_t *f = nullptr, *s[2] = {nullptr, nullptr};
  int val = 0, max = 0;
  bool rev = false;

  bool is_root()
  {
    return f == nullptr || (f->s[0] != this && f->s[1] != this);
  }
  bool get_son()
  {
    return f->s[1] == this;
  }
  void push_up()
  {
    max = val;
    if (s[0])
      check_max(max, s[0]->max);
    if (s[1])
      check_max(max, s[1]->max);
  }
  void push_rev()
  {
    rev = !rev;
    std::swap(s[0], s[1]);
  }
  void push_down()
  {
    if (rev)
    {
      if (s[0])
        s[0]->push_rev();
      if (s[1])
        s[1]->push_rev();
      rev = false;
    }
  }
  void push()
  {
    if (!is_root())
      f->push();
    push_down();
  }
  void rotate()
  {
    node_t *uu = this, *ff = uu->f, *aa = ff->f;
    bool ss = get_son();
    if (!ff->is_root())
      aa->s[ff->get_son()] = uu;
    ff->f = uu;
    ff->s[ss] = uu->s[!ss];
    uu->f = aa;
    uu->s[!ss] = ff;
    if (ff->s[ss])
      ff->s[ss]->f = ff;
    ff->push_up();
    uu->push_up();
  }
  void splay()
  {
    push();
    while (!is_root())
    {
      if (f->is_root())
      {
        rotate();
        break;
      }
      else
      {
        (get_son() == f->get_son() ? f : this)->rotate();
        rotate();
      }
    }
  }
  void access()
  {
    node_t *uu = this, *ss = nullptr;
    while (uu != nullptr)
    {
      uu->splay();
      uu->s[1] = ss;
      uu->push_up();
      ss = uu;
      uu = uu->f;
    }
  }
  void make_root()
  {
    access();
    splay();
    push_rev();
  }
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();
  std::vector<node_t> p(n);

  auto link = [&](int u, int v) {
    p[u].make_root();
    p[u].splay();
    p[u].f = &p[v];
  };

  for (int i = 0; i < n; i++)
  {
    p[i].val = p[i].max = sc.next_int();
  }
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    link(u, v);
  }

  for (int i = 0; i < q; i++)
  {
    int op = sc.next_int();
    if (op == 1)
    {
      int u = sc.next_int() - 1;
      int v = sc.next_int();
      p[u].splay();
      p[u].val = p[u].max = v;
    }
    else
    {
      int u = sc.next_int() - 1;
      int v = sc.next_int() - 1;
      p[u].make_root();
      p[v].access();
      p[v].splay();
      std::cout << p[v].max << " ";
    }
  }
  return 0;
}
