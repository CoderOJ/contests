#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int k = sc.next_int();

    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();

    std::vector<int> mr(n);
    for (int i = 0; i < n; i++)
      mr[i] = i;
    for (int i = 0; i < k; i++)
    {
      int l = sc.next_int() - 1;
      int r = sc.next_int();
      check_max(mr[l], r);
    }
    for (int i = 0; i + 1 < n; i++)
      check_max(mr[i + 1], mr[i]);

    std::vector<int> ord(n);
    for (int i = 0; i < n; i++)
      ord[i] = i;
    std::stable_sort(ord.begin(), ord.end(), [&](int x, int y) {
      return a[x] < a[y];
    });

    int max_al = n;
    std::vector<int> ar(n + 1);
    for (int i = 0; i <= n; i++)
      ar[i] = i;

    for (auto itl = ord.begin(), itr = itl; itl != ord.end(); itl = itr)
    {
      while (itr != ord.end() && a[*itr] == a[*itl])
        itr++;
      for (auto cl = itl, cr = cl; cl != itr; cl++)
      {
        while (cr != itr && *cr < mr[*cl])
          cr++;
        if (cl != cr && cl != std::prev(cr))
        {
          // see(*cl, *std::prev(cr));
          check_min(max_al, *std::next(cl) + 1);
          check_max(ar[0], *std::prev(cr, 2) + 1);
          check_max(ar[*cl + 1], *std::prev(cr) + 1);
        }
      }
    }

    int ans = n;
    for (int ans_l = 0, ans_r = 0; ans_l < max_al; ans_l++)
    {
      check_max(ans_r, ar[ans_l]);
      // see(ans_l, ans_r);
      check_min(ans, ans_r - ans_l);
    }

    std::cout << ans << std::endl;
  }
  return 0;
}
