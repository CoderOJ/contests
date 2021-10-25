#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <numeric>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int W = 8192;
std::vector<int> updated[W];
int last_update[W];
bool ans[W];
int n;

int main()
{
  ans[0] = true;
  for (int i = 0; i < W; i++)
  {
    updated[i].push_back(0);
    last_update[i] = W;
  }

  n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int x = sc.next_int();
    for (int key : updated[x])
    {
      int to = key ^ x;
      ans[to] = true;
      for (int j = x + 1; j < last_update[to]; j++)
        updated[j].push_back(to);
      check_min(last_update[to], x);
    }
    updated[x].clear();
  }

  std::cout << std::accumulate(ans, ans + W, 0) << std::endl;
  for (int i = 0; i < W; i++)
    if (ans[i])
      printf("%d ", i);
  return 0;
}

