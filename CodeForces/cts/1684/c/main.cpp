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
    int m = sc.next_int();

    std::vector<std::vector<int>> a;
    for (int i = 0; i < n; i++)
    {
      std::vector<int> b(m);
      for (int i = 0; i < m; i++)
        b[i] = sc.next_int();
      a.emplace_back(std::move(b));
    }

    auto [ans_i, ans_j] = [&]() -> std::pair<int, int> {
      std::vector<int> nons;
      std::vector<int> cur_pair;

      for (int i = 0; i < n; i++)
      {
        auto b = a[i];
        std::sort(b.begin(), b.end());

        auto diff_pos = [&] {
          std::vector<int> res;
          for (int j = 0; j < m; j++)
            if (a[i][j] != b[j])
              res.push_back(j);
          return res;
        }();

        if (diff_pos.size() == 0)
        {
          nons.push_back(i);
        }
        else if (diff_pos.size() == 2)
        {
          if (cur_pair.empty())
            cur_pair = diff_pos;
          else if (cur_pair != diff_pos)
            return {-1, -1};
        }
        else
        {
          return {-1, -1};
        }
      }

      if (cur_pair.empty())
      {
        return {0, 0};
      }
      else
      {
        int ax = cur_pair[0], ay = cur_pair[1];
        for (int i : nons)
          if (a[i][ax] != a[i][ay])
            return {-1, -1};
        return {ax, ay};
      }
    }();

    if (ans_i == -1)
    {
      puts("-1");
    }
    else
    {
      printf("%d %d\n", ans_i + 1, ans_j + 1);
    }
  }
  return 0;
}
