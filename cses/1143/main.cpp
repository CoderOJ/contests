#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct sgt_t
{
  struct node_t
  {
    int max = 0;
    node_t() = default;
    node_t(const node_t lhs, const node_t rhs) : max(std::max(lhs.max, rhs.max))
    {
    }
  };

  std::vector<node_t> p;

  template <class RandomIterator>
  sgt_t(int n, RandomIterator it) : p(n * 4) { init(1, 0, n, it); }

  template <class RandomIterator>
  void init(int u, int l, int r, RandomIterator it)
  {
    if (r - l == 1)
    {
      p[u].max = it[l];
    }
    else
    {
      int mid = (l + r) / 2;
      init(u + u, l, mid, it);
      init(u + u + 1, mid, r, it);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  void modify(int u, int l, int r, int mp, int delta)
  {
    if (r - l == 1)
    {
      p[u].max += delta;
    }
    else
    {
      int mid = (l + r) / 2;
      if (mp < mid)
        modify(u + u, l, mid, mp, delta);
      else
        modify(u + u + 1, mid, r, mp, delta);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  int search(int u, int l, int r, int val)
  {
    if (r - l == 1)
    {
      return p[u].max >= val ? l : r;
    }
    else
    {
      int mid = (l + r) / 2;
      if (p[u + u].max >= val)
        return search(u + u, l, mid, val);
      else
        return search(u + u + 1, mid, r, val);
    }
  }
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  sgt_t t(n, a.begin());

  for (int i = 0; i < q; i++)
  {
    int x = sc.next_int();
    int pos = t.search(1, 0, n, x);
    if (pos == n)
    {
      printf("0 ");
    }
    else
    {
      printf("%d ", pos + 1);
      t.modify(1, 0, n, pos, -x);
    }
  }
  return 0;
}
