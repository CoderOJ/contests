#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n);
  for (int &x : a)
    x = sc.next_int();

  auto check = [&](int char_set) -> bool
  {
    see(char_set);
    std::vector<std::pair<int,int>> cur{{0, -1}, {a[0], 0}};
    for (int i = 1; i < n; i++)
    {
      if (a[i] > cur.back().first)
      {
        if (cur.back().second == 0)
          cur.back().first = a[i];
        else
          cur.push_back({a[i], 0});
      }
      else
      {
        while (cur.back().first > a[i])
        {
          auto b = cur.back();
          cur.pop_back();
          if (cur.back().first < a[i])
            cur.emplace_back(a[i], b.second);
        }
        if (cur.back().second == char_set - 1)
          cur.pop_back();
        if (cur.size() == 1)
          return false;

        auto b = cur.back();
        cur.pop_back();

        if (b.first - 1 > cur.back().first)
          cur.emplace_back(b.first - 1, b.second);
        if (cur.back().second == b.second + 1)
          cur.back().first = b.first;
        else
          cur.emplace_back(b.first, b.second + 1);
        
        if (cur.back().first != a[i])
          cur.emplace_back(a[i], 0);
      }
      see(i, cur);
    }
    return true;
  };

  int l = 1, r = n;
  while (l < r)
  {
    int mid = (l + r) / 2;
    if (check(mid)) r = mid;
    else l = mid + 1;
  }

  printf("%d\n", l);
  return 0;
}
