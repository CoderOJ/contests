#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t
{
  int x, l, r;
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();

  std::vector<node_t> t;

  int lb = 0, rb = 0, num = 1;

  for (int i = 1; i <= n; ++i)
  {
    int x = sc.next_int();

    if (x <= num)
      rb = i;
    else
    {
      t.push_back({num, lb, rb});
      num *= (x - 1) / num + 1;
      lb = rb = i;
    }
  }

  t.push_back({num, lb, rb});

  for (int i = 0; i < q; i++)
  {
    int x = sc.next_int();
    int l = sc.next_int();
    int r = sc.next_int();

    int ans = 0;
    for (auto &p : t)
    {
      int y  = x / p.x * p.x;
      int tl = std::max(l, y - p.r);
      int tr = std::min(r, y - p.l);

      if (tl <= tr)
        ans += tr - tl + 1;
    }

    printf("%d\n", ans);
  }

  return 0;
}