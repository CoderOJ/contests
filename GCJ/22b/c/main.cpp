#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 15;

std::vector<int> ps[N];
int cx[N], cy[N];
int px[N], py[N];
int jx, jy;
int n;

int64_t distance(int ax, int ay, int bx, int by)
{
  return (int64_t)(ax - bx) * (ax - bx) + (int64_t)(ay - by) * (ay - by);
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    printf("Case #%d: ", i + 1);

    n = sc.next_int();
    for (int i = 0; i < n; i++)
    {
      cx[i] = sc.next_int();
      cy[i] = sc.next_int();
    }
    jx = sc.next_int();
    jy = sc.next_int();
    for (int i = 0; i < n; i++)
    {
      px[i] = sc.next_int();
      py[i] = sc.next_int();
    }

    for (int i = 0; i < n; i++)
    {
      ps[i].clear();
      int64_t max_dis = distance(cx[i], cy[i], jx, jy);
      for (int j = 0; j < n; j++)
        if (distance(cx[i], cy[i], px[j], py[j]) <= max_dis)
          ps[i].push_back(j);
      std::sort(ps[i].begin(), ps[i].end(), [&](int x, int y) { 
        return distance(cx[i], cy[i], px[x], py[x]) < distance(cx[i], cy[i], px[y], py[y]);
      });
    }

    std::vector<int> ord(n);
    for (int i = 0; i < n; i++)
      ord[i] = i;

    std::vector<int> ans;

    static bool vis[N];
    do
    {
      // see(ord);
      std::fill(vis, vis + n, false);
      bool ok = [&]{
        for (int x : ord)
        {
          bool filled = false;
          for (int y : ps[x])
            if (!vis[y])
            {
              vis[y] = true;
              filled = true;
              break;
            }
          if (!filled)
            return false;
        }
        return true;
      }();

      // see(ok);
      if (ok)
      {
        ans = ord;
        break;
      }
    }
    while (std::next_permutation(ord.begin(), ord.end()));

    if (ans.empty())
    {
      puts("IMPOSSIBLE");
    }
    else
    {
      puts("POSSIBLE");
      std::fill(vis, vis + n, false);
      for (int x : ans)
      {
        for (int y : ps[x])
          if (!vis[y])
          {
            vis[y] = true;
            printf("%d %d\n", x + 1, y + 2);
            break;
          }
      }
    }
  }

  return 0;
}
