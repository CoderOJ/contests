#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <array>
#include <limits>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int64_t inf = std::numeric_limits<int64_t>::max() / 2;

auto pow42 = []() {
  constexpr int LEN = 11;

  std::array<int64_t, LEN> res;
  res[0] = 1;
  for (int i = 0; i + 1 < LEN; i++)
    res[i + 1] = res[i] * 42;
  return res;
}();

auto diff_upgrade(int64_t x)
{
  return x - *std::lower_bound(pow42.begin(), pow42.end(), x);
}

constexpr int N = 100005;

int n, q, a[N];

struct sgt_t
{
  struct node_t
  {
    int64_t val;
    int64_t diff_max;
    int64_t val_add     = 0;
    int64_t val_assign  = -1;
    int64_t diff_assign = -1;

    node_t() = default;
    node_t(int64_t val, int64_t diff) : val(val), diff_max(diff) {}
    node_t(const node_t &lhs, const node_t &rhs) :
        val(lhs.val == rhs.val ? lhs.val : -inf),
        diff_max(std::max(lhs.diff_max, rhs.diff_max))
    {
    }

    void push_assign(int64_t val, int64_t diff)
    {
      this->val         = val;
      this->val_add     = 0;
      this->val_assign  = val;
      this->diff_max    = diff;
      this->diff_assign = diff;
    }
    void push_add(int64_t det)
    {
      this->val      = this->val + det;
      this->val_add  = this->val_add + det;
      this->diff_max = this->diff_max + det;
    }
    void push_down(node_t &lhs, node_t &rhs)
    {
      if (val_assign != -1)
      {
        lhs.push_assign(val_assign, diff_assign);
        rhs.push_assign(val_assign, diff_assign);
        val_assign  = -1;
        diff_assign = -1;
      }
      if (val_add != 0)
      {
        lhs.push_add(val_add);
        rhs.push_add(val_add);
        val_add = 0;
      }
    }
  };

  node_t p[N * 4];

  template <class RandomAccessIterator>
  void init(int u, RandomAccessIterator begin, RandomAccessIterator end)
  {
    if (begin + 1 == end)
    {
      p[u] = node_t(*begin, diff_upgrade(*begin));
    }
    else
    {
      RandomAccessIterator mid = begin + std::distance(begin, end) / 2;
      init(u + u, begin, mid);
      init(u + u + 1, mid, end);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  auto query(int u, int l, int r, int pos)
  {
    if (r - l == 1)
    {
      return p[u];
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int mid = l + (r - l) / 2;
      if (pos < mid)
        return query(u + u, l, mid, pos);
      else
        return query(u + u + 1, mid, r, pos);
    }
  }

  void assign(int u, int l, int r, int ml, int mr, int64_t val, int64_t diff)
  {
    if (ml <= l && r <= mr)
    {
      p[u].push_assign(val, diff);
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int mid = l + (r - l) / 2;
      if (ml < mid)
        assign(u + u, l, mid, ml, mr, val, diff);
      if (mr > mid)
        assign(u + u + 1, mid, r, ml, mr, val, diff);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  void add(int u, int l, int r, int ml, int mr, int64_t val)
  {
    if (ml <= l && r <= mr)
    {
      p[u].push_add(val);
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int mid = l + (r - l) / 2;
      if (ml < mid)
        add(u + u, l, mid, ml, mr, val);
      if (mr > mid)
        add(u + u + 1, mid, r, ml, mr, val);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  void adjust(int u, int l, int r)
  {
    if (p[u].diff_max > 0)
    {
      if (p[u].val >= 0)
        p[u].push_assign(p[u].val, diff_upgrade(p[u].val));
      else
      {
        cm_assert(r - l >= 2);
        p[u].push_down(p[u + u], p[u + u + 1]);
        int mid = l + (r - l) / 2;
        adjust(u + u, l, mid);
        adjust(u + u + 1, mid, r);
        p[u] = node_t(p[u + u], p[u + u + 1]);
      }
    }
  }

} sgt;

int main()
{
  n = sc.next_int();
  q = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  sgt.init(1, a, a + n);

  for (int i = 0; i < q; i++)
  {
    int opt = sc.next_int();
    if (opt == 1)
    {
      int p = sc.next_int() - 1;
      std::cout << sgt.query(1, 0, n, p).val << std::endl;
    }
    else if (opt == 2)
    {
      int l   = sc.next_int() - 1;
      int r   = sc.next_int();
      int val = sc.next_int();
      sgt.assign(1, 0, n, l, r, val, diff_upgrade(val));
    }
    else
    {
      int l   = sc.next_int() - 1;
      int r   = sc.next_int();
      int val = sc.next_int();
      do
      {
        sgt.add(1, 0, n, l, r, val);
        sgt.adjust(1, 0, n);
      } while (sgt.p[1].diff_max == 0);
    }
  }

  return 0;
}
