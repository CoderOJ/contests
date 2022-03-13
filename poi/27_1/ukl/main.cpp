#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  int k = sc.next_int();

  if (n == 1 || m == 1)
  {
    if (k != n + m - 2)
    {
      puts("NIE");
    }
    else
    {
      puts("TAK");
      if (n == 1)
      {
        for (int i = 1; i < m; i++)
          printf("%d %d %d %d\n", 1, i, 1, i + 1);
      }
      else
      {
        for (int i = 1; i < n; i++)
          printf("%d %d %d %d\n", i, 1, i + 1, 1);
      }
    }
  }
  else
  {
    if (k < n + m - 2 || k > n * m - 1)
    {
      puts("NIE");
    }
    else if (k == n + m - 2)
    {
      if (n % 2 == 1)
      {
        puts("TAK");
        int c = n / 2 + 1;
        for (int j = 1; j < m; j++)
          printf("%d %d %d %d\n", c, j, c, j + 1);
        for (int j = 1; j <= m; j++)
          for (int i = 1; i < n; i++)
            printf("%d %d %d %d\n", i, j, i + 1, j);
      }
      else if (m % 2 == 1)
      {
        puts("TAK");
        int c = m / 2 + 1;
        for (int i = 1; i < n; i++)
          printf("%d %d %d %d\n", i, c, i + 1, c);
        for (int i = 1; i <= n; i++)
          for (int j = 1; j < m; j++)
            printf("%d %d %d %d\n", i, j, i, j + 1);
      }
      else
      {
        puts("NIE");
      }
    }
    else
    {
      puts("TAK");
      int c = (n + 1) / 2;
      for (int j = 1; j < m; j++)
        printf("%d %d %d %d\n", c, j, c, j + 1);
      k -= n + m - 2;

      if (k == 1 && n % 2 == 0)
        k = 0;

      {
        for (int i = 1; i < c; i++)
          printf("%d %d %d %d\n", i, 1, i + 1, 1);

        std::vector<std::pair<int, int>> ord;
        for (int i = 1; i < c; i++)
        {
          if (i % 2 == 1)
          {
            for (int j = 2; j <= m; j++)
              ord.emplace_back(i, j);
          }
          else
          {
            for (int j = m; j >= 2; j--)
              ord.emplace_back(i, j);
          }
        }
        std::pair<int, int> last{1, 1};
        for (const auto &[x, y] : ord)
        {
          if (k > 0)
          {
            k -= 1;
            printf("%d %d %d %d\n", last.first, last.second, x, y);
            last = {x, y};
          }
          else
          {
            printf("%d %d %d %d\n", x + 1, y, x, y);
          }
        }
      }

      {
        if (c == 1)
          k -= 1;

        for (int i = n; i > c; i--)
          printf("%d %d %d %d\n", i - 1, m, i, m);

        std::vector<std::pair<int, int>> ord;
        for (int i = n; i > c; i--)
        {
          if ((n - i) % 2 == 0)
          {
            for (int j = m - 1; j >= 1; j--)
              ord.emplace_back(i, j);
          }
          else
          {
            for (int j = 1; j <= m - 1; j++)
              ord.emplace_back(i, j);
          }
        }
        std::pair<int, int> last{n, m};
        for (const auto &[x, y] : ord)
        {
          if (k > 0)
          {
            k -= 1;
            printf("%d %d %d %d\n", last.first, last.second, x, y);
            last = {x, y};
          }
          else
          {
            printf("%d %d %d %d\n", x - 1, y, x, y);
          }
        }
      }
    }
  }

  return 0;
}
