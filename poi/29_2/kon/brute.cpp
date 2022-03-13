#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 1'000'005, 1'005)

std::vector<int> e[N];

int n;

int main()
{
  e[1].push_back(2);
  e[2].push_back(1);

  n = sc.next_int();

  int cur_vertex = 3;

  for (int i = 0; i < n; i++)
  {
    char op = sc.next_char();
    if (op == '?')
    {
      int u = sc.next_int();
      std::cout << e[u].size() << std::endl;
    }
    else if (op == 'W')
    {
      int u = sc.next_int();
      int v = cur_vertex++;
      e[u].push_back(v);
      e[v].push_back(u);
    }
    else
    {
      int base = sc.next_int();
      int v    = cur_vertex++;
      for (int u : e[base])
      {
        e[u].push_back(v);
        e[v].push_back(u);
      }
    }
  }

  return 0;
}
