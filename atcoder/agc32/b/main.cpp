#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<std::pair<int,int>> es;
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
    {
      if (n % 2 == 0 && i + j != n + 1)
        es.emplace_back(i, j);
      if (n % 2 == 1 && i + j != n)
        es.emplace_back(i, j);
    }

  std::cout << es.size() << std::endl;
  for (const auto & [u, v] : es)
    std::cout << u << " " << v << std::endl;
  return 0;
}

