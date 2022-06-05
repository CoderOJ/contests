#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

int main()
{
  std::ios::sync_with_stdio(false);

  int t;
  std::cin >> t;
  int n, k;
  std::cin >> n >> k;

  auto read_list = [](int n) {
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
      std::cin >> a[i];
      a[i] -= 1;
    }
    return a;
  };

  auto make_colour = [](const std::vector<int> &a) {
    std::vector<int> col(a.size(), -1);
    int              cur_col = 0;
    for (int i = 0; i < static_cast<int>(a.size()); i++)
      if (col[i] == -1)
      {
        std::vector<int> ps{i};
        for (int p = a[i]; p != i; p = a[p])
          ps.push_back(p);

        if (ps.size() <= 3)
        {
          int c = cur_col++;
          for (int p : ps)
            col[p] = c;
        }
        else if (ps.size() % 3 == 0)
        {
          for (size_t i = 0; i < ps.size(); i += 3)
          {
            int c          = cur_col++;
            col[ps[i + 0]] = c;
            col[ps[i + 1]] = c;
            col[ps[i + 2]] = c;
          }
        }
        else if (ps.size() % 3 == 1)
        {
          {
            int c      = cur_col++;
            col[ps[0]] = c;
            col[ps[1]] = c;
          }
          {
            int c      = cur_col++;
            col[ps[2]] = c;
            col[ps[3]] = c;
          }
          for (size_t i = 4; i < ps.size(); i += 3)
          {
            int c          = cur_col++;
            col[ps[i + 0]] = c;
            col[ps[i + 1]] = c;
            col[ps[i + 2]] = c;
          }
        }
        else
        {
          {
            int c      = cur_col++;
            col[ps[0]] = c;
            col[ps[1]] = c;
          }
          for (size_t i = 2; i < ps.size(); i += 3)
          {
            int c          = cur_col++;
            col[ps[i + 0]] = c;
            col[ps[i + 1]] = c;
            col[ps[i + 2]] = c;
          }
        }
      }
    return col;
  };

  for (int i = 0; i < t; i++)
  {
    [&] {
      auto a = read_list(n);
      for (int t = 0;; t++)
      {
        // std::cerr << "round[" << t << "]: ";
        // std::cerr << "a = ";
        // for (int v : a)
        //   std::cerr << v << " ";
        // std::cerr << std::endl;

        auto col = make_colour(a);
        // std::cerr << "col = ";
        // for (int c : col)
        //   std::cerr << c << " ";
        // std::cerr << std::endl;

        for (int c : col)
          std::cout << c + 1 << ' ';
        std::cout << std::endl;

        int res;
        std::cin >> res;
        if (res == -1)
          exit(0);
        else if (res == 1)
          return;
        else
          a = read_list(n);
      }
    }();
  }
  return 0;
}
