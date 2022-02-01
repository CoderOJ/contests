#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstddef>
#include <map>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

void show_trace()
{
  __asm__ __volatile__("" ::: "memory");
}

struct value_t
{
  int64_t value{};
  int     id{};

  value_t() = default;
  value_t(int64_t v, int i) : value(v), id(i) {}

  value_t shift(int64_t det) const
  {
    return value_t(value - det, id);
  }

  bool operator<(const value_t &rhs) const
  {
    return value != rhs.value ? value < rhs.value : id > rhs.id;
  }
};

std::ostream &operator<<(std::ostream &out, const value_t &v)
{
  return out << "(" << v.value << ", " << v.id << ")";
}

struct node_t
{
  node_t *f    = nullptr;
  node_t *s[2] = {nullptr, nullptr};
  bool    rev  = false;

  bool is_root()
  {
    return this->f == nullptr ||
           (this->f->s[0] != this && this->f->s[1] != this);
  }

  bool get_son()
  {
    return this->f->s[1] == this;
  }

  int64_t det     = 0;
  int64_t det_sum = 0;

  std::set<value_t> vals;
  value_t           val;
  value_t           val_max;
  value_t           val_max_r;

  void push_rev()
  {
    this->rev = !this->rev;
    std::swap(this->s[0], this->s[1]);
    std::swap(this->val_max, this->val_max_r);
  }

  void push_down()
  {
    if (this->rev)
    {
      if (this->s[0] != nullptr)
        this->s[0]->push_rev();
      if (this->s[1] != nullptr)
        this->s[1]->push_rev();
      this->rev = false;
    }
  }

  void push()
  {
    if (!is_root())
      f->push();
    push_down();
  }

  void set_val(value_t v)
  {
    this->vals.erase(this->val);
    this->val = v;
    this->vals.insert(v);
  }

  void push_up()
  {
    this->det_sum   = this->det;
    this->val_max   = this->vals.rbegin()->shift(this->det_sum);
    this->val_max_r = this->vals.rbegin()->shift(this->det_sum);
    if (this->s[0] != nullptr)
    {
      val_max   = std::max(s[0]->val_max, val_max.shift(s[0]->det_sum));
      val_max_r = std::max(val_max_r, s[0]->val_max_r.shift(det_sum));
      det_sum   = det_sum + s[0]->det_sum;
    }
    if (this->s[1] != nullptr)
    {
      val_max   = std::max(val_max, s[1]->val_max.shift(det_sum));
      val_max_r = std::max(s[1]->val_max_r, val_max_r.shift(s[1]->det_sum));
      det_sum   = det_sum + s[1]->det_sum;
    }
  }

  void rotate()
  {
    node_t *uu = this;
    node_t *ff = uu->f;
    node_t *aa = ff->f;
    bool    ss = uu->get_son();

    if (!ff->is_root())
      aa->s[ff->get_son()] = uu;

    ff->f      = uu;
    ff->s[ss]  = uu->s[!ss];
    uu->f      = aa;
    uu->s[!ss] = ff;

    if (ff->s[ss] != nullptr)
      ff->s[ss]->f = ff;

    ff->push_up();
  }

  void splay()
  {
    this->push();
    while (!this->is_root())
    {
      if (this->f->is_root())
      {
        this->rotate();
        break;
      }
      else
      {
        if (this->get_son() == this->f->get_son())
          this->f->rotate();
        else
          this->rotate();
        this->rotate();
      }
    }
    this->push_up();
  }

  void access()
  {
    node_t *uu = this;
    node_t *ss = nullptr;
    while (uu != nullptr)
    {
      uu->splay();
      if (uu->s[1] != nullptr)
      {
        // see(uu->vals, uu->s[1]->val_max);
        // show_trace();
        uu->vals.insert(uu->s[1]->val_max);
      }
      if (ss != nullptr)
      {
        // see(uu, uu->vals, ss->val_max);
        // show_trace();
        uu->vals.erase(ss->val_max);
      }
      uu->s[1] = ss;

      ss = uu;
      uu = uu->f;
    }
  }

  void make_root()
  {
    this->access();
    this->splay();
    this->push_rev();
  }
};

constexpr int N = 100005;

node_t p[N * 2];

void link(node_t *u, node_t *v)
{
  u->make_root();
  v->make_root();
  v->vals.insert(u->val_max);
  v->push_up();
  u->f = v;
}

std::map<std::pair<int, int>, int> es;

int n, q;

int main()
{
  n = sc.next_int();
  q = sc.next_int();
  for (int i = 1; i <= n; i++)
    p[i].set_val(value_t(sc.next_long(), i));

  for (int i = 1; i < n; i++)
  {
    int     u = sc.next_int();
    int     v = sc.next_int();
    int64_t w = sc.next_long();

    if (u > v)
      std::swap(u, v);

    es[{u, v}] = i;

    p[n + i].set_val(value_t(-0x3f3f3f3f, n + i));
    p[n + i].det = w;
    p[n + i].push_up();
    link(&p[u], &p[n + i]);
    link(&p[v], &p[n + i]);
  }

  p[1].make_root();
  p[1].access();
  // see(p[1].vals);

  int pos = 1;
  for (int i = 0; i < q; i++)
  {
    int opt = sc.next_int();
    if (opt == 1)
    {
      int     u = sc.next_int();
      int64_t z = sc.next_long();
      p[u].make_root();
      p[u].set_val(value_t(z, u));
    }
    else
    {
      int     u = sc.next_int();
      int     v = sc.next_int();
      int64_t w = sc.next_long();
      if (u > v)
        std::swap(u, v);
      int id = es[{u, v}];
      p[n + id].make_root();
      p[n + id].det = w;
      p[n + id].push_up();
    }

    p[pos].make_root();
    p[pos].access();
    // see(p[pos].vals);
    if (pos == p[pos].vals.rbegin()->id)
      pos = (++p[pos].vals.rbegin())->id;
    else
      pos = p[pos].vals.rbegin()->id;
    std::cout << pos << " ";
  }

  std::cout << std::endl;

  return 0;
}
